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


/* Typed-string test for apple2_caps (DIP 3).
 *
 * Script: <shift>T</shift>HIS IS A <caps>TEST<caps> OF THE APPLE 2 CAPS KEYMAP.<ctrl>m</ctrl>
 * Expected output: THIS IS A TEST OF THE APPLE 2 CAPS KEYMAP.\r
 *
 * setup_apple2_caps_keymap() maps APPLE_CAPS_MAP to both MOD_PLAIN_MAP and
 * MOD_CAPS_MAP, and APPLE_CAPS_SHIFT_MAP to MOD_SHIFT_MAP.  No caps activate
 * is called at boot; the caps state starts OFF, but the plain map is
 * apple_caps_matrix (uppercase).  Tapping caps toggles caps state but both
 * plain and caps use the same matrix, so the output is always uppercase.
 *
 * Key coordinates (from apple_caps_matrix / apple_caps_shift_matrix;
 * all share the same physical positions as the apple2 layout):
 *   space (1,4)   T (4,4)   H (3,3)   I (4,1)   S (3,7)
 *   A     (1,6)   E (4,6)   O (5,5)   F (3,5)   C (2,6)
 *   L     (5,6)   K (3,1)   Y (4,3)   M (2,2)   P (1,1)
 *   .     (5,7)   2 (7,6)
 *
 * CTRL+m (row 2, col 2 with CTRL) maps to ASCII_CTRL_M = '\r' via
 * apple_ctrl_matrix[2][2].
 */
static const sim_string_step_t apple2_caps_string_steps[] = {
    /* <shift>T: apple_caps_shift_matrix[4][4] = 'T' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_SHIFT },
    /* HIS IS A  (apple_caps_matrix -> uppercase throughout) */
    { .type = SIM_STEP_KEY,  .row = 3, .col = 3, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    /* <caps>TEST<caps> — both plain and caps use apple_caps_matrix: no case change */
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    /*  OF THE APPLE 2 CAPS KEYMAP. */
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
    { .type = SIM_STEP_KEY,  .row = 2, .col = 6, .expected = 'C' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 1, .expected = 'P' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
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

static const sim_string_test_t apple2_caps_string_test = {
    .dip_value             = 3,
    .boot_scan_ticks       = 1000,
    .modifier_shift        = { .row = 0, .col = 2 },
    .modifier_caps_toggle  = { .row = 0, .col = 0 },
    .modifier_ctrl         = { .row = 0, .col = 6 },
    .steps                 = apple2_caps_string_steps,
    .num_steps             = sizeof(apple2_caps_string_steps) / sizeof(apple2_caps_string_steps[0]),
};

#endif
