#ifndef ASDF_SIMAVR_IO_FAMILYA_H
#define ASDF_SIMAVR_IO_FAMILYA_H

/* Pin map for atmega328p / atmega168p / atmega88p.
 * Source of truth: src/Arch/asdf_arch_atmega328p.h.
 * Duplicated here so the harness stays decoupled from ASDF source. */

#include "asdf_simavr_io_select.h"

static const asdf_io_map_t asdf_io_familyA = {
    .family_name      = "A",
    .cpu_frequency_hz = 8000000U,

    .row_port  = 'C',
    .row_mask  = 0x0F,            /* PORTC[3:0]: 4-bit row index */
    .row_shift = 0,
    .row_active_low = 0,

    /* Family A reads one column at a time via shift register on PINB[0]. */
    .col_port  = 'B',
    .col_bit_serial = 0,          /* PINB[0] */
    .col_load_clock_port = 'B',
    .col_load_clock_bit  = 2,     /* PORTB[2]: load-then-shift clock */
    .col_mode_port = 'B',
    .col_mode_bit  = 1,           /* PORTB[1]: HIGH=shift, LOW=load */
    .col_parallel = 0,            /* serial */

    .data_port = 'D',
    .data_mask = 0xFF,

    .strobe_port = 'B',
    .strobe_bit  = 6,
    /* Default polarity; a keymap can flip this via asdf_arch_set_neg_strobe.
     * Harness strobe-edge capture observes both edges; see harness/io.c. */
    .strobe_active_high = 1,

    .led_count = 3,
    .leds = {
        { .port = 'C', .bit = 4, .active_low = 1 },
        { .port = 'B', .bit = 5, .active_low = 0 },
        { .port = 'B', .bit = 4, .active_low = 0 },
    },

    .dip_row = 8,                 /* DIPs read as matrix row 8 */
    .dip_col_count = 8,

    .scan_tick_hz = 1000,
};

#endif
