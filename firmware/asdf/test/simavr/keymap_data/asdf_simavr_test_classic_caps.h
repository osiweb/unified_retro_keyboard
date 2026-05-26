#ifndef ASDF_SIMAVR_TEST_CLASSIC_CAPS_H
#define ASDF_SIMAVR_TEST_CLASSIC_CAPS_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_classic.c (DIP value 1).
 *
 * CAPS is active, so plain state emits capitals.
 * classic_caps_plain_matrix[1][6] = 'A'   (row 1, col 6 — caps-lock active)
 * classic_caps_shift_matrix[1][6] = 'A'   (row 1, col 6 with SHIFT held)
 * classic_plain_matrix[0][2] = ACTION_SHIFT  (L-Shift)
 * classic_plain_matrix[0][6] = ACTION_CTRL
 * classic_plain_matrix[5][3] = ASCII_CR = '\r'
 */
static const sim_event_t classic_caps_events[] = {
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_NONE  },
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = 5, .col = 3, .hold_cycles = 400000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t classic_caps_test = {
    .name            = "classic_caps",
    .dip_value       = 1,
    .boot_scan_ticks = 1000,
    .modifier_shift  = { .row = 0, .col = 2 },
    .modifier_ctrl   = { .row = 0, .col = 6 },
    .events          = classic_caps_events,
    .num_events      = sizeof(classic_caps_events) / sizeof(classic_caps_events[0]),
};

#endif
