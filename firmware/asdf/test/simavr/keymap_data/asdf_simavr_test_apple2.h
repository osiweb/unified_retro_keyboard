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


/* Typed-string test for apple2 (DIP 2).
 *
 * Script: <shift>T</shift>his is a <caps>test<caps> of the Apple 2 keymap.<ctrl>m</ctrl>
 * Expected output: THIS IS A test OF THE APPLE 2 KEYMAP.\r
 *
 * setup_apple2_keymap() calls asdf_modifier_capslock_activate(), so caps is ON
 * at boot and the keymap starts in all-caps mode (apple_caps_matrix).
 *
 * State trace:
 *   boot: caps ON  → apple_caps_matrix active (uppercase output)
 *   <shift>T: CAPS+SHIFT (modifier 0x03) → MOD_SHIFT_MAP = apple_shift_matrix[4][4] = 'T'
 *   HIS IS A  : no modifier, caps ON → apple_caps_matrix → uppercase
 *   <caps tap>: caps OFF → apple_plain_matrix active (lowercase output)
 *   test      : lowercase 't','e','s','t'
 *   <caps tap>: caps ON  → apple_caps_matrix active (uppercase output)
 *    OF THE APPLE 2 KEYMAP. : uppercase
 *
 * Key coordinates (from apple_caps_matrix / apple_plain_matrix / apple_shift_matrix;
 * all share the same physical positions):
 *   space (1,4)   T (4,4)   H (3,3)   I (4,1)   S (3,7)
 *   A     (1,6)   E (4,6)   O (5,5)   F (3,5)   C (2,6)
 *   L     (5,6)   K (3,1)   Y (4,3)   M (2,2)   P (1,1)
 *   .     (5,7)   2 (7,6)
 *
 * CTRL+m (row 2, col 2 with CTRL) maps to ASCII_CTRL_M = '\r' via
 * apple_ctrl_matrix[2][2].
 */
static const sim_string_step_t apple2_string_steps[] = {
    /* <shift>T: CAPS+SHIFT => apple_shift_matrix => 'T' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_SHIFT },
    /* HIS IS A  (caps ON -> apple_caps_matrix -> uppercase) */
    { .type = SIM_STEP_KEY,  .row = 3, .col = 3, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    /* <caps tap>: caps OFF -> apple_plain_matrix -> lowercase */
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 't' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'e' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 's' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 't' },
    /* <caps tap>: caps ON -> apple_caps_matrix -> uppercase */
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    /*  OF THE APPLE 2 KEYMAP. */
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 5, .expected = 'O' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 5, .expected = 'F' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 3, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 1, .expected = 'P' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 1, .expected = 'P' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 6, .expected = 'L' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 7, .col = 6, .expected = '2' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 1, .expected = 'K' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 3, .expected = 'Y' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 2, .expected = 'M' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 1, .expected = 'P' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 7, .expected = '.' },
    /* <ctrl>m</ctrl> => '\r' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_CTRL },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 2, .expected = '\r' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_CTRL },
};

static const sim_string_test_t apple2_string_test = {
    .dip_value             = 2,
    .boot_scan_ticks       = 1000,
    .modifier_shift        = { .row = 0, .col = 2 },
    .modifier_caps_toggle  = { .row = 0, .col = 0 },
    .modifier_ctrl         = { .row = 0, .col = 6 },
    .steps                 = apple2_string_steps,
    .num_steps             = sizeof(apple2_string_steps) / sizeof(apple2_string_steps[0]),
};

#endif
