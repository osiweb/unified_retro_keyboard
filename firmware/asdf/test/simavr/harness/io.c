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
static int g_active_row = -1;             /* row currently being strobed, or -1 */

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
     * unpressed before Task 7 installs a proper column-injection notifier. */
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
    }
    /* Family A serial-column injection is intentionally deferred.
     * io_wire_output already pre-drives the serial column pin high, so
     * the firmware sees all keys unpressed and the boot smoke test passes. */
}
