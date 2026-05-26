#include <string.h>
#include <stdint.h>
#include <simavr/avr_ioport.h>

#include "io.h"
#include "capture.h"

static avr_t *g_cpu;
static const asdf_io_map_t *g_io;
static uint8_t g_data_port_value;    /* latched on every write to data port */
static uint8_t g_last_strobe;        /* reset by io_wire_output */

#define MATRIX_MAX_ROWS 16
#define MATRIX_MAX_COLS 8
static uint8_t matrix[MATRIX_MAX_ROWS];   /* matrix[row] = bitmap of pressed cols */
static int g_active_row = -1;             /* row currently being strobed, or -1 (family B) */

/* ── family-A shift-register state ──────────────────────────────────────── */
static int     g_active_row_familyA  = -1;  /* 4-bit row index from PORTC, or -1 */
static uint8_t g_familyA_col_shift   = 0;   /* shift register contents */
static int     g_familyA_in_load_phase = 0; /* 1 when COLMODE is LOW (load mode) */
static int     g_familyA_last_clock  = 0;   /* for rising-edge detection */

static void on_data_port(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq; (void)param;
    g_data_port_value = (uint8_t)(value & g_io->data_mask);
}

static void on_strobe(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq; (void)param;
    /* Capture on every strobe transition (either edge) because keymaps
     * can flip strobe polarity at runtime via asdf_arch_set_neg_strobe.
     * The IOPORT-bit IRQ only fires on actual changes, so one pulse =
     * two notifies; the test code drains between events. */
    uint8_t v = (uint8_t)(value & 1);
    if (v != g_last_strobe) {
        cap_push(g_cpu->cycle, g_data_port_value);
        g_last_strobe = v;
    }
}

/* ── family-A serial column injection helpers ────────────────────────────── */

/* Drive PINB[col_bit_serial] to the value the firmware will read.
 * The firmware inverts on read (~ASDF_COL_PIN >> bit & 1), so a pressed key
 * (matrix bit = 1) must appear as LOW on the pin; unpressed = HIGH. */
static void drive_familyA_serial(int bit_value)
{
    avr_irq_t *pin_irq = avr_io_getirq(g_cpu,
        AVR_IOCTL_IOPORT_GETIRQ(g_io->col_port), g_io->col_bit_serial);
    avr_raise_irq(pin_irq, bit_value ? 0 : 1);
}

static void on_row_port_familyA(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq; (void)param;
    g_active_row_familyA = (int)((value >> g_io->row_shift) & g_io->row_mask);
}

static void on_col_mode_familyA(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq; (void)param;
    g_familyA_in_load_phase = ((value & 1) == 0);   /* LOW = load mode */
}

static void on_col_clock_familyA(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq; (void)param;
    int now = (int)(value & 1);
    if (now && !g_familyA_last_clock) {                /* rising edge */
        if (g_familyA_in_load_phase) {
            /* Load phase: snapshot the matrix row into the shift register,
             * then immediately present bit 0 on the pin.  The firmware reads
             * the pin before issuing the first shift clock, so bit 0 must be
             * valid as soon as the load pulse completes. */
            if (g_active_row_familyA >= 0 &&
                g_active_row_familyA < MATRIX_MAX_ROWS) {
                g_familyA_col_shift = matrix[g_active_row_familyA];
            } else {
                g_familyA_col_shift = 0;
            }
        } else {
            /* Shift phase: advance one position right; the next bit becomes
             * the new LSB that the firmware will read. */
            g_familyA_col_shift >>= 1;
        }
        drive_familyA_serial(g_familyA_col_shift & 1);
    }
    g_familyA_last_clock = now;
}

void io_wire_output(avr_t *cpu, const asdf_io_map_t *io)
{
    g_cpu = cpu;
    g_io  = io;
    g_data_port_value = 0;
    g_last_strobe = 0;

    /* Hook every bit of the data port so any write updates our latch.
     * AVR_IOCTL_IOPORT_GETIRQ + IOPORT_IRQ_REG_PORT fires on PORTx writes. */
    avr_irq_t *port_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->data_port), IOPORT_IRQ_REG_PORT);
    avr_irq_register_notify(port_irq, on_data_port, 0);

    /* Hook the strobe bit; AVR_IOCTL_IOPORT_GETIRQ + bit number fires on
     * any change to that bit. */
    avr_irq_t *strobe_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->strobe_port), io->strobe_bit);
    avr_irq_register_notify(strobe_irq, on_strobe, 0);

    /* For family A, the column data arrives on a single serial bit.  simavr
     * leaves undriven input pins at 0, which the firmware inverts to 1 (key
     * pressed).  Pre-drive the serial column pin high so all columns read as
     * unpressed for the very first read cycle, before the active column-
     * injection notifiers installed by io_wire_input take over. */
    if (!io->col_parallel) {
        avr_irq_t *col_irq = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->col_port), io->col_bit_serial);
        avr_raise_irq(col_irq, 1);
    }
}

/* ── matrix mutation helpers ─────────────────────────────────────────────── */

void matrix_press(int row, int col)
{
    if (row < 0 || row >= MATRIX_MAX_ROWS) return;
    if (col < 0 || col >= MATRIX_MAX_COLS) return;
    matrix[row] |= (uint8_t)(1u << col);
}

void matrix_release(int row, int col)
{
    if (row < 0 || row >= MATRIX_MAX_ROWS) return;
    if (col < 0 || col >= MATRIX_MAX_COLS) return;
    matrix[row] &= (uint8_t)~(1u << col);
}

void matrix_clear(void) { memset(matrix, 0, sizeof matrix); }

void set_dip(uint8_t value) { matrix[8] = value; }

/* ── family-B parallel column injection ──────────────────────────────────── */

static void present_columns_familyB(void)
{
    if (!g_io->col_parallel) return;
    if (g_active_row < 0) return;

    uint8_t cols = matrix[g_active_row];
    uint8_t pin_value = g_io->col_active_low ? (uint8_t)~cols : cols;

    /* avr_raise_irq(IOPORT_IRQ_PIN_ALL) does not reliably propagate to what
     * the firmware reads from PINx in simavr 1.6.  Direct write to the
     * cpu->data[] slot for the PIN register is the only reliable method. */
    if (g_io->col_pin_addr)
        g_cpu->data[g_io->col_pin_addr] = pin_value;
}

static void on_row_port_familyB(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq;
    int hi_port = (int)(intptr_t)param;   /* 1 if PORTA (hi rows), 0 if PORTJ (lo rows) */
    uint8_t v = (uint8_t)value;
    if (g_io->row_active_low) v = (uint8_t)~v;
    if (v == 0) { g_active_row = -1; return; }

    /* one-hot: pick the lowest set bit */
    int bit = 0;
    while ((v & 1) == 0) { v >>= 1; bit++; }
    g_active_row = hi_port ? (8 + bit) : bit;
    present_columns_familyB();
}

/* ── io_wire_input ───────────────────────────────────────────────────────── */

void io_wire_input(avr_t *cpu, const asdf_io_map_t *io)
{
    g_cpu = cpu;
    g_io  = io;
    matrix_clear();
    g_active_row = -1;

    if (io->col_parallel) {
        /* Family B: hook PORTJ (lo rows 0-7) and PORTA (hi rows 8-15). */
        avr_irq_t *lo = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->row_port), IOPORT_IRQ_REG_PORT);
        avr_irq_register_notify(lo, on_row_port_familyB, (void *)(intptr_t)0);

        if (io->row_port_hi) {
            avr_irq_t *hi = avr_io_getirq(cpu,
                AVR_IOCTL_IOPORT_GETIRQ(io->row_port_hi), IOPORT_IRQ_REG_PORT);
            avr_irq_register_notify(hi, on_row_port_familyB, (void *)(intptr_t)1);
        }
    } else {
        /* Family A: parallel-in / serial-out shift register on PORTB.
         * Three notifiers cooperate to replay the 74xx165-style protocol:
         *   row port   → tracks the 4-bit row index from PORTC[3:0]
         *   COLMODE    → distinguishes load phase (LOW) from shift phase (HIGH)
         *   COLCLK     → on rising edge, loads or shifts and drives PINB[0] */
        g_active_row_familyA  = -1;
        g_familyA_col_shift   = 0;
        g_familyA_in_load_phase = 0;
        g_familyA_last_clock  = 0;

        /* Row notifier on PORTC (full-byte IRQ) to track the 4-bit row index. */
        avr_irq_t *row = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->row_port), IOPORT_IRQ_REG_PORT);
        avr_irq_register_notify(row, on_row_port_familyA, 0);

        /* COLMODE on PORTB[col_mode_bit]: bit-level notifier. */
        avr_irq_t *mode = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->col_mode_port), io->col_mode_bit);
        avr_irq_register_notify(mode, on_col_mode_familyA, 0);

        /* COLCLK on PORTB[col_load_clock_bit]: bit-level notifier. */
        avr_irq_t *clk = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->col_load_clock_port),
            io->col_load_clock_bit);
        avr_irq_register_notify(clk, on_col_clock_familyA, 0);
    }
}
