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

/* The classic_caps keymap ID hook (CLASSIC_ID_MESSAGE_HOOK = ASDF_HOOK_USER_10)
 * is fired by ACTION_FN_10, which lives in classic_ctrl_matrix[6][5] — the same
 * coordinate as the classic keymap (both variants share the same ctrl matrix).
 * The id message function is classic_caps_id_message(), which prints
 * "[Keymap: classic]\n" — identical to the classic keymap's id message.
 * asdf_putc() expands \n to \r\n, so the emitted sequence is 19 bytes. */
static const sim_identity_test_t classic_caps_identity_test = {
    .dip_value             = 1,
    .boot_scan_ticks       = 200,
    .trigger_key           = { .row = 6, .col = 5 },
    .trigger_modifier      = SIM_MOD_CTRL,
    .modifier_shift        = { .row = 0, .col = 2 },
    .modifier_caps_toggle  = { .row = 5, .col = 2 },
    .modifier_ctrl         = { .row = 0, .col = 6 },
    .capture_ticks         = 1000,
    .expected              = "[Keymap: classic]\r\n",
    .expected_len          = sizeof("[Keymap: classic]\r\n") - 1,
};


/* Typed-string test for classic_caps (DIP 1).
 *
 * Script: <shift>T</shift>HIS IS A <caps>TEST<caps> OF THE CLASSIC CAPS KEYMAP.<ctrl>m</ctrl>
 * Expected output: THIS IS A TEST OF THE CLASSIC CAPS KEYMAP.\r
 *
 * classic_caps maps CLASSIC_CAPS_MAP to both MOD_PLAIN_MAP and MOD_CAPS_MAP, and
 * CLASSIC_SHIFT_MAP to MOD_SHIFT_MAP.  Both plain and caps states use the same
 * uppercase matrix, so the caps-toggle taps have no visible effect on letter case.
 * Every letter keystroke produces uppercase output regardless of the caps state.
 *
 * Key coordinates (from classic_caps_matrix / classic_shift_matrix):
 *   space (1,4)   T (4,4)   H (3,3)   I (4,1)   S (3,7)
 *   A     (1,6)   E (4,6)   O (5,5)   F (3,5)   C (2,6)
 *   L     (5,6)   K (3,1)   Y (4,3)   M (2,2)   P (1,1)
 *   .     (5,7)
 *
 * CTRL+m (row 2, col 2 with CTRL) maps to ASCII_CTRL_M = '\r' via
 * classic_ctrl_matrix[2][2].
 */
static const sim_string_step_t classic_caps_string_steps[] = {
    /* <shift>T */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_SHIFT },
    /* HIS IS A  */
    { .type = SIM_STEP_KEY,  .row = 3, .col = 3, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    /* <caps>TEST<caps> — both caps states use classic_caps_matrix, so no case change */
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    /*  OF THE CLASSIC CAPS KEYMAP. */
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 5, .expected = 'O' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 5, .expected = 'F' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 4, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 3, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 4, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 6, .expected = 'C' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 6, .expected = 'L' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 7, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 6, .expected = 'C' },
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

static const sim_string_test_t classic_caps_string_test = {
    .dip_value             = 1,
    .boot_scan_ticks       = 1000,
    .modifier_shift        = { .row = 0, .col = 2 },
    .modifier_caps_toggle  = { .row = 5, .col = 2 },
    .modifier_ctrl         = { .row = 0, .col = 6 },
    .steps                 = classic_caps_string_steps,
    .num_steps             = sizeof(classic_caps_string_steps) / sizeof(classic_caps_string_steps[0]),
};

#endif
