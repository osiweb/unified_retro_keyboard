#ifndef ASDF_SIMAVR_TEST_ACE1000_H
#define ASDF_SIMAVR_TEST_ACE1000_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_ace1000_add_map.c (DIP value 5).
 *
 * ACE_KEY_A = 0x61, ACE_KEY_SHIFT_A = 0x41, ACE_KEY_RETURN = 0x0d.
 * setup_ace1000_keymap() calls asdf_modifier_capslock_activate(), so CAPS is
 * always active on boot.  The CAPS map is therefore the default:
 * ace1000_caps_matrix[1][2] = ACE_KEY_SHIFT_A = 'A'  (row 1, col 2 — always-on CAPS)
 * ace1000_shift_matrix[1][2] = ACE_KEY_SHIFT_A = 'A'  (row 1, col 2 with SHIFT held)
 * ace1000_plain_matrix[0][6] = ACTION_SHIFT
 * ace1000_plain_matrix[0][3] = ACTION_CTRL
 * ace1000_caps_matrix[9][2] = ACE_KEY_RETURN = '\r'
 */
static const sim_event_t ace1000_events[] = {
    { .row = 1, .col = 2, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_NONE  },
    { .row = 1, .col = 2, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = 9, .col = 2, .hold_cycles = 400000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t ace1000_test = {
    .name            = "ace1000",
    .dip_value       = 5,
    .boot_scan_ticks = 1000,
    .modifier_shift  = { .row = 0, .col = 6 },
    .modifier_ctrl   = { .row = 0, .col = 3 },
    .events          = ace1000_events,
    .num_events      = sizeof(ace1000_events) / sizeof(ace1000_events[0]),
};

#endif
