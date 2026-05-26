#ifndef ASDF_SIMAVR_IO_FAMILYB_H
#define ASDF_SIMAVR_IO_FAMILYB_H

/* Pin map for atmega640 / atmega1280 / atmega2560.
 * Source of truth: src/Arch/asdf_arch_atmega2560.h. */

#include "asdf_simavr_io_select.h"

static const asdf_io_map_t asdf_io_familyB = {
    .family_name      = "B",
    .cpu_frequency_hz = 16000000U,

    /* 16 rows split across two ports, active-LOW strobe. */
    .row_port  = 'J',             /* PORTJ[7:0] = rows 0..7 (LOROW) */
    .row_mask  = 0xFF,
    .row_shift = 0,
    .row_port_hi = 'A',           /* PORTA[7:0] = rows 8..15 (HIROW) */
    .row_active_low = 1,

    /* Parallel column read on PINC, active-LOW (firmware inverts). */
    .col_port  = 'C',
    .col_parallel = 1,
    .col_mask  = 0xFF,
    .col_active_low = 1,

    .data_port = 'H',
    .data_mask = 0xFF,

    .strobe_port = 'B',
    .strobe_bit  = 4,
    .strobe_active_high = 1,

    .led_count = 3,
    .leds = {
        { .port = 'D', .bit = 5, .active_low = 0 },
        { .port = 'D', .bit = 6, .active_low = 0 },
        { .port = 'D', .bit = 7, .active_low = 0 },
    },

    .dip_row = 8,
    .dip_col_count = 8,

    .scan_tick_hz = 1000,
};

#endif
