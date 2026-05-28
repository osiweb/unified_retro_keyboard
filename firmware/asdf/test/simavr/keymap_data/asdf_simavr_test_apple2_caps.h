#ifndef ASDF_SIMAVR_TEST_APPLE2_CAPS_H
#define ASDF_SIMAVR_TEST_APPLE2_CAPS_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_apple2_add_map.c (DIP value 3).
 *
 * CAPS is active, so plain state emits capitals.
 * apple2_caps_plain_matrix[1][6] = 'A'   (row 1, col 6 — caps-lock active)
 * apple2_caps_shift_matrix[1][6] = 'A'   (row 1, col 6 with SHIFT held)
 * apple2_caps_plain_matrix[0][2] = ACTION_SHIFT  (L-Shift)
 * apple2_caps_plain_matrix[0][6] = ACTION_CTRL
 * apple2_caps_plain_matrix[5][3] = ASCII_CR = '\r'
 */
static const sim_event_t apple2_caps_events[] = {
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_NONE  },
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = 5, .col = 3, .hold_cycles = 400000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t apple2_caps_test = {
    .name            = "apple2_caps",
    .dip_value       = 3,
    .boot_scan_ticks = 1000,
    .modifier_shift  = { .row = 0, .col = 2 },
    .modifier_ctrl   = { .row = 0, .col = 6 },
    .events          = apple2_caps_events,
    .num_events      = sizeof(apple2_caps_events) / sizeof(apple2_caps_events[0]),
};

/* The apple2_caps keymap ID hook (APPLE2_CAPS_ID_MESSAGE = ASDF_HOOK_USER_10)
 * is fired by ACTION_FN_10, which lives in apple_ctrl_matrix[6][5] — the same
 * ctrl matrix shared by apple2 and apple2_caps.  So pressing CTRL + key(6,5)
 * triggers apple2_caps_id_message(), which prints "[Keymap: Apple 2 CAPS]"
 * with no trailing newline.  The emitted sequence is 22 bytes.
 * The caps toggle key is ACTION_CAPS at apple_plain_matrix[0][0]. */
static const sim_identity_test_t apple2_caps_identity_test = {
    .dip_value             = 3,
    .boot_scan_ticks       = 200,
    .trigger_key           = { .row = 6, .col = 5 },
    .trigger_modifier      = SIM_MOD_CTRL,
    .modifier_shift        = { .row = 0, .col = 2 },
    .modifier_caps_toggle  = { .row = 0, .col = 0 },
    .modifier_ctrl         = { .row = 0, .col = 6 },
    .capture_ticks         = 1000,
    .expected              = "[Keymap: Apple 2 CAPS]",
    .expected_len          = sizeof("[Keymap: Apple 2 CAPS]") - 1,
};

#endif
