#ifndef ASDF_SIMAVR_TEST_SOL_H
#define ASDF_SIMAVR_TEST_SOL_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_sol.c (DIP value 4).
 *
 * SOL has a different matrix layout from the classic/apple2 keymaps.
 * setup_sol_keymap() calls asdf_modifier_capslock_activate(), so CAPS is
 * always active on boot.  The CAPS map is therefore the default:
 * sol_caps_map[0][2] = 'A'     (row 0, col 2 — always-on CAPS)
 * sol_shift_map[0][2] = 'A'     (row 0, col 2 with SHIFT held)
 * sol_plain_map[2][1] = ACTION_SHIFT
 * sol_plain_map[0][0] = ACTION_CTRL
 * sol_plain_map[7][5] = ASCII_CR = '\r'
 *
 * Note: SOL calls asdf_arch_set_neg_strobe so strobe polarity is inverted,
 * but the harness captures on both edges and handles this transparently.
 */
static const sim_event_t sol_events[] = {
    { .row = 0, .col = 2, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_NONE  },
    { .row = 0, .col = 2, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = 7, .col = 5, .hold_cycles = 400000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t sol_test = {
    .name            = "sol",
    .dip_value       = 4,
    .boot_scan_ticks = 1000,
    .modifier_shift  = { .row = 2, .col = 1 },
    .modifier_ctrl   = { .row = 0, .col = 0 },
    .events          = sol_events,
    .num_events      = sizeof(sol_events) / sizeof(sol_events[0]),
};

/* SOL identity test.
 *
 * sol_id_message() prints "[Keybd: Sol-20]" (no trailing newline).
 * ACTION_FN_10 is at sol_ctrl_map[5][2] (the 0 key), so CTRL+0 triggers the hook.
 * SOL activates capslock on boot; setup_sol_keymap() also calls
 * asdf_arch_set_neg_strobe() but the harness captures on both edges
 * transparently.
 * sol_plain_map[2][0] = ACTION_CAPS (caps toggle).
 * Modifier coords from sol_test above.
 */
static const sim_identity_test_t sol_identity_test = {
    .dip_value             = 4,
    .boot_scan_ticks       = 200,
    .trigger_key           = { .row = 5, .col = 2 },
    .trigger_modifier      = SIM_MOD_CTRL,
    .modifier_shift        = { .row = 2, .col = 1 },
    .modifier_caps_toggle  = { .row = 2, .col = 0 },
    .modifier_ctrl         = { .row = 0, .col = 0 },
    .capture_ticks         = 1500,
    .expected              = "[Keybd: Sol-20]",
    .expected_len          = sizeof("[Keybd: Sol-20]") - 1,
};


/* Typed-string test for sol (DIP 4).
 *
 * Script: <shift>T</shift>HIS IS A TEST OF THE SOL-20 KEYMAP.<ctrl>m</ctrl>
 * Expected output: THIS IS A TEST OF THE SOL-20 KEYMAP.\r
 *
 * setup_sol_keymap() calls asdf_modifier_capslock_activate(), so caps is ON at
 * boot and the SOL-20 produces uppercase throughout.  The caps-toggle key at
 * (2,0) is deliberately omitted from this test because simavr 1.6 exhibits an
 * interaction between asdf_arch_set_neg_strobe() and the atmega1280 timer model
 * that makes the caps debounce unreliable on that target.  All other targets
 * would also support a mixed-case variant, but consistency across targets is
 * more important here.  The shift key exercises the CAPS+SHIFT modifier path
 * (MOD_SHIFT_MAP) for the first letter.
 *
 * SOL key coordinates (from sol_caps_map / sol_shift_map):
 *   space (9,3)   T (6,6)   H (0,7)   I (7,1)   S (0,3)
 *   A     (0,2)   E (6,4)   O (7,2)   F (0,5)
 *   L     (1,2)   K (1,1)   Y (6,7)   M (3,0)   P (7,3)
 *   .     (3,2)   - (5,3)   2 (4,2)   0 (5,2)
 *
 * CTRL+m (row 3, col 0 with CTRL) maps to ASCII_CTRL_M = '\r' via
 * sol_ctrl_map[3][0].
 */
static const sim_string_step_t sol_string_steps[] = {
    /* <shift>T: CAPS+SHIFT => sol_shift_map => 'T' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_SHIFT },
    /* HIS IS A  (caps ON -> sol_caps_map -> uppercase) */
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 7, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 3, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 9, .col = 3, .expected = ' ' },
    /* IS  */
    { .type = SIM_STEP_KEY,  .row = 7, .col = 1, .expected = 'I' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 3, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 9, .col = 3, .expected = ' ' },
    /* A  */
    { .type = SIM_STEP_KEY,  .row = 0, .col = 2, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 9, .col = 3, .expected = ' ' },
    /* TEST  */
    { .type = SIM_STEP_KEY,  .row = 6, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 4, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 3, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 9, .col = 3, .expected = ' ' },
    /* OF  */
    { .type = SIM_STEP_KEY,  .row = 7, .col = 2, .expected = 'O' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 5, .expected = 'F' },
    { .type = SIM_STEP_KEY,  .row = 9, .col = 3, .expected = ' ' },
    /* THE  */
    { .type = SIM_STEP_KEY,  .row = 6, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 7, .expected = 'H' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 4, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 9, .col = 3, .expected = ' ' },
    /* SOL-20  */
    { .type = SIM_STEP_KEY,  .row = 0, .col = 3, .expected = 'S' },
    { .type = SIM_STEP_KEY,  .row = 7, .col = 2, .expected = 'O' },
    { .type = SIM_STEP_KEY,  .row = 1, .col = 2, .expected = 'L' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 3, .expected = '-' },
    { .type = SIM_STEP_KEY,  .row = 4, .col = 2, .expected = '2' },
    { .type = SIM_STEP_KEY,  .row = 5, .col = 2, .expected = '0' },
    { .type = SIM_STEP_KEY,  .row = 9, .col = 3, .expected = ' ' },
    /* KEYMAP. */
    { .type = SIM_STEP_KEY,  .row = 1, .col = 1, .expected = 'K' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 4, .expected = 'E' },
    { .type = SIM_STEP_KEY,  .row = 6, .col = 7, .expected = 'Y' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 0, .expected = 'M' },
    { .type = SIM_STEP_KEY,  .row = 0, .col = 2, .expected = 'A' },
    { .type = SIM_STEP_KEY,  .row = 7, .col = 3, .expected = 'P' },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 2, .expected = '.' },
    /* <ctrl>m</ctrl> => '\r' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_CTRL },
    { .type = SIM_STEP_KEY,  .row = 3, .col = 0, .expected = '\r' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_CTRL },
};

static const sim_string_test_t sol_string_test = {
    .dip_value             = 4,
    .boot_scan_ticks       = 1000,
    .modifier_shift        = { .row = 2, .col = 1 },
    .modifier_caps_toggle  = { .row = 2, .col = 0 },
    .modifier_ctrl         = { .row = 0, .col = 0 },
    .steps                 = sol_string_steps,
    .num_steps             = sizeof(sol_string_steps) / sizeof(sol_string_steps[0]),
};

#endif
