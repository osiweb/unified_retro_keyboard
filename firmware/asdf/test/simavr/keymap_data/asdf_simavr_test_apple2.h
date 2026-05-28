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

/* The apple2 keymap ID hook (APPLE2_ID_MESSAGE = ASDF_HOOK_USER_10) is fired
 * by ACTION_FN_10, which lives in apple_ctrl_matrix[6][5].  So pressing
 * CTRL + key(6,5) triggers apple2_id_message(), which prints
 * "[Keymap: Apple 2 (u/l case)]" with no trailing newline.
 * No \n means no \r\n expansion; the emitted sequence is 28 bytes.
 * The apple2 keymap activates capslock on boot so the caps toggle key is
 * ACTION_CAPS at apple_plain_matrix[0][0]. */
static const sim_identity_test_t apple2_identity_test = {
    .dip_value             = 2,
    .boot_scan_ticks       = 200,
    .trigger_key           = { .row = 6, .col = 5 },
    .trigger_modifier      = SIM_MOD_CTRL,
    .modifier_shift        = { .row = 0, .col = 2 },
    .modifier_caps_toggle  = { .row = 0, .col = 0 },
    .modifier_ctrl         = { .row = 0, .col = 6 },
    .capture_ticks         = 1500,
    .expected              = "[Keymap: Apple 2 (u/l case)]",
    .expected_len          = sizeof("[Keymap: Apple 2 (u/l case)]") - 1,
};

#endif
