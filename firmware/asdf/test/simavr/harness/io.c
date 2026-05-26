#include <simavr/avr_ioport.h>

#include "io.h"
#include "capture.h"

static avr_t *g_cpu;
static const asdf_io_map_t *g_io;
static uint8_t g_data_port_value;    /* latched on every write to data port */

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
    static uint8_t last_strobe = 0;
    uint8_t v = (uint8_t)(value & 1);
    if (v != last_strobe) {
        cap_push(g_cpu->cycle, g_data_port_value);
        last_strobe = v;
    }
}

void io_wire_output(avr_t *cpu, const asdf_io_map_t *io)
{
    g_cpu = cpu;
    g_io  = io;
    g_data_port_value = 0;

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
