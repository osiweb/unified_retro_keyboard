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

/* ACE1000 identity test.
 *
 * ace1000_id_message() prints "[Keymap: ace1000]\n"; asdf_putc() expands \n
 * to \r\n, so the emitted sequence is 20 bytes.
 * ACTION_FN_10 is at ace1000_ctrl_matrix[6][0] (the 0 key), so CTRL+0 triggers
 * the hook.
 * ACE1000 activates capslock on boot.
 * ace1000_plain_matrix[0][5] = ACTION_CAPS (caps toggle).
 * Modifier coords from ace1000_test above.
 */
static const sim_identity_test_t ace1000_identity_test = {
    .dip_value             = 5,
    .boot_scan_ticks       = 200,
    .trigger_key           = { .row = 6, .col = 0 },
    .trigger_modifier      = SIM_MOD_CTRL,
    .modifier_shift        = { .row = 0, .col = 6 },
    .modifier_caps_toggle  = { .row = 0, .col = 5 },
    .modifier_ctrl         = { .row = 0, .col = 3 },
    .capture_ticks         = 1500,
    .expected              = "[Keymap: ace1000]\r\n",
    .expected_len          = sizeof("[Keymap: ace1000]\r\n") - 1,
};


/* Typed-string test for ace1000 (DIP 5).
 *
 * Script: <shift>T</shift>HIS IS A <caps>test<caps> OF THE ACE1000 KEYMAP.<ctrl>m</ctrl>
 * Expected output: THIS IS A test OF THE ACE1000 KEYMAP.\r
 *
 * setup_ace1000_keymap() calls asdf_modifier_capslock_activate(), so caps is ON
 * at boot and the ACE 1000 starts in all-caps mode (ace1000_caps_matrix).
 *
 * State trace:
 *   boot: caps ON  → ace1000_caps_matrix active (uppercase output)
 *   <shift>T: CAPS+SHIFT (0x03) → MOD_SHIFT_MAP = ace1000_shift_matrix[3][1] = 'T'
 *   HIS IS A  : caps ON → ace1000_caps_matrix → uppercase
 *   <caps tap>: caps OFF → ace1000_plain_matrix active (lowercase output)
 *   test      : lowercase 't','e','s','t'
 *   <caps tap>: caps ON  → ace1000_caps_matrix active (uppercase output)
 *    OF THE ACE1000 KEYMAP. : uppercase
 *
 * ACE 1000 key coordinates (from ace1000_plain_matrix / ace1000_caps_matrix):
 *   space (0,7)   T (3,1)   H (3,6)   I (4,5)   S (1,6)
 *   A     (1,2)   E (2,1)   O (5,1)   F (2,6)   C (2,3)
 *   L     (5,2)   K (4,6)   Y (3,5)   M (4,3)   P (6,1)
 *   .     (5,3)   1 (1,0)   0 (6,0)
 *
 * CTRL+m (row 4, col 3 with CTRL) maps to ACE_KEY_CTRL_M = '\r' = 0x0d via
 * ace1000_ctrl_matrix[4][3].
 */
static const sim_string_step_t ace1000_string_steps[] = {
    /* <shift>T: CAPS+SHIFT => ace1000_shift_matrix => 'T' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 1, .expected = 'T' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_SHIFT },
    /* HIS IS A  (caps ON -> ace1000_caps_matrix -> uppercase) */
    { .type = SIM_STEP_KEY,  .row = 3, .col = 6, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 5, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 5, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 2, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = ' ' },
    /* <caps tap>: caps OFF -> ace1000_plain_matrix -> lowercase */
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 1, .expected = 't' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 1, .expected = 'e' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 6, .expected = 's' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 1, .expected = 't' },
    /* <caps tap>: caps ON -> ace1000_caps_matrix -> uppercase */
    { .type = SIM_STEP_MOD_TAP,  .modifier = SIM_MOD_CAPS },
    /*  OF THE ACE1000 KEYMAP. */
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 1, .expected = 'O' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 6, .expected = 'F' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 1, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 6, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 1, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 2, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 3, .expected = 'C' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 1, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 0, .expected = '1' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 0, .expected = '0' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 0, .expected = '0' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 0, .expected = '0' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = ' ' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 6, .expected = 'K' },
    { .type = SIM_STEP_KEY,  .row = 2, .col = 1, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 5, .expected = 'Y' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 3, .expected = 'M' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 2, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 1, .expected = 'P' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 3, .expected = '.' },
    /* <ctrl>m</ctrl> => '\r' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_CTRL },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 3, .expected = '\r' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_CTRL },
};

static const sim_string_test_t ace1000_string_test = {
    .dip_value             = 5,
    .boot_scan_ticks       = 1000,
    .modifier_shift        = { .row = 0, .col = 6 },
    .modifier_caps_toggle  = { .row = 0, .col = 5 },
    .modifier_ctrl         = { .row = 0, .col = 3 },
    .steps                 = ace1000_string_steps,
    .num_steps             = sizeof(ace1000_string_steps) / sizeof(ace1000_string_steps[0]),
};

#endif
