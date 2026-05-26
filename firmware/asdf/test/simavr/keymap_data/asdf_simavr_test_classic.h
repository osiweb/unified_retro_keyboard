#ifndef ASDF_SIMAVR_TEST_CLASSIC_H
#define ASDF_SIMAVR_TEST_CLASSIC_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_classic.c.
 *
 * classic_plain_matrix[1][6] = 'a'   (row 1, col 6)
 * classic_shift_matrix[1][6] = 'A'   (row 1, col 6 with SHIFT held)
 * classic_plain_matrix[0][2] = ACTION_SHIFT  (L-Shift)
 * classic_plain_matrix[0][6] = ACTION_CTRL
 * classic_plain_matrix[5][3] = ASCII_CR = '\r'
 */
static const sim_event_t classic_events[] = {
    /* hold_cycles = 400000 = 25 ms at 16 MHz.
     * Debounce is 10 ms (10 scan ticks); 15 ms margin covers worst-case
     * scan-tick alignment.  Modifier events get an additional 15 ms
     * pre-settle in the runner before the main key is pressed, so the
     * hold_cycles budget here only needs to cover one debounce window. */
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'a',  .with_modifier = SIM_MOD_NONE  },
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = 5, .col = 3, .hold_cycles = 400000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t classic_test = {
    .name            = "classic",
    .dip_value       = 0,
    /* Boot wait must outlast the ID-message print train.
     * "[Keymap: classic]\n" = 18 chars at 40 ms/char = 720 ms.
     * Use 1000 ms to settle completely before asserting on output. */
    .boot_scan_ticks = 1000,
    .modifier_shift  = { .row = 0, .col = 2 },
    .modifier_ctrl   = { .row = 0, .col = 6 },
    .events          = classic_events,
    .num_events      = sizeof(classic_events) / sizeof(classic_events[0]),
};

#endif
