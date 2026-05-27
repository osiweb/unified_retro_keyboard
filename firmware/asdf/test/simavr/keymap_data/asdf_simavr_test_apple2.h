#ifndef ASDF_SIMAVR_TEST_APPLE2_H
#define ASDF_SIMAVR_TEST_APPLE2_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_apple2_add_map.c (DIP value 2).
 *
 * setup_apple2_keymap() calls asdf_modifier_capslock_activate(), so CAPS is
 * always active on boot.  The CAPS map is therefore the default:
 * apple_caps_matrix[1][6] = 'A'   (row 1, col 6 — always-on CAPS)
 * apple_caps_shift_matrix[1][6] = 'A'   (row 1, col 6 with SHIFT held)
 * apple2_plain_matrix[0][2] = ACTION_SHIFT  (L-Shift)
 * apple2_plain_matrix[0][6] = ACTION_CTRL
 * apple2_plain_matrix[5][3] = ASCII_CR = '\r'
 */
static const sim_event_t apple2_events[] = {
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_NONE  },
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = 5, .col = 3, .hold_cycles = 400000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t apple2_test = {
    .name            = "apple2",
    .dip_value       = 2,
    .boot_scan_ticks = 1000,
    .modifier_shift  = { .row = 0, .col = 2 },
    .modifier_ctrl   = { .row = 0, .col = 6 },
    .events          = apple2_events,
    .num_events      = sizeof(apple2_events) / sizeof(apple2_events[0]),
};

#endif
