#include <stdio.h>
#include <simavr/avr_ioport.h>
#include <simavr/sim_vcd_file.h>

#include "vcd.h"

static avr_vcd_t g_vcd;
static int g_vcd_active = 0;

int vcd_begin(avr_t *cpu, const asdf_io_map_t *io, const char *path)
{
    if (avr_vcd_init(cpu, path, &g_vcd, 100 /* sample every 100us */) != 0) {
        fprintf(stderr, "WARN: could not init VCD %s\n", path);
        return 1;
    }

    /* Data port: 8 bits */
    avr_irq_t *port_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->data_port), IOPORT_IRQ_REG_PORT);
    avr_vcd_add_signal(&g_vcd, port_irq, 8, "data");

    /* Strobe: 1 bit */
    avr_irq_t *strobe_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->strobe_port), io->strobe_bit);
    avr_vcd_add_signal(&g_vcd, strobe_irq, 1, "strobe");

    /* LEDs */
    for (int i = 0; i < io->led_count; i++) {
        avr_irq_t *led = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->leds[i].port), io->leds[i].bit);
        char name[8]; snprintf(name, sizeof name, "led%d", i + 1);
        avr_vcd_add_signal(&g_vcd, led, 1, name);
    }

    /* Row port (lo for family B, the only row port for family A) */
    avr_irq_t *row_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->row_port), IOPORT_IRQ_REG_PORT);
    avr_vcd_add_signal(&g_vcd, row_irq, 8, "row_lo");

    avr_vcd_start(&g_vcd);
    g_vcd_active = 1;
    return 0;
}

void vcd_end(void)
{
    if (g_vcd_active) {
        avr_vcd_stop(&g_vcd);
        g_vcd_active = 0;
    }
}
