#ifndef ASDF_SIMAVR_TEST_CLASSIC_H
#define ASDF_SIMAVR_TEST_CLASSIC_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_classic.c.
 *
 * classic_plain_matrix[1][6] = 'a'   (row 1, col 6)
 * classic_shift_matrix[1][6] = 'A'   (row 1, col 6 with SHIFT held)
 * classic_plain_matrix[0][2] = ACTION_SHIFT  (L-Shift)
 * classic_plain_matrix[0][6] = ACTION_CTRL
 * classic_plain_matrix[5][3] = ASCII_CR = '\r'
 */
static const sim_event_t classic_events[] = {
    /* hold_cycles = 400000 = 25 ms at 16 MHz.
     * Debounce is 10 ms (10 scan ticks); 15 ms margin covers worst-case
     * scan-tick alignment.  Modifier events get an additional 15 ms
     * pre-settle in the runner before the main key is pressed, so the
     * hold_cycles budget here only needs to cover one debounce window. */
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'a',  .with_modifier = SIM_MOD_NONE  },
    { .row = 1, .col = 6, .hold_cycles = 400000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = 5, .col = 3, .hold_cycles = 400000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t classic_test = {
    .name            = "classic",
    .dip_value       = 0,
    /* Boot settle wait.  No identity message is printed at boot (the
     * ID hook fires only when the user-function key is pressed —
     * see classic_identity_test below), so this is just enough
     * time for the scan loop to start running cleanly. */
    .boot_scan_ticks = 1000,
    .modifier_shift  = { .row = 0, .col = 2 },
    .modifier_ctrl   = { .row = 0, .col = 6 },
    .events          = classic_events,
    .num_events      = sizeof(classic_events) / sizeof(classic_events[0]),
};

/* The classic keymap ID hook (ASDF_HOOK_USER_10) is fired by ACTION_FN_10,
 * which lives in classic_ctrl_matrix[6][5].  So pressing CTRL + key(6,5)
 * triggers the hook, which prints "[Keymap: classic]\n" to the output ring.
 * asdf_putc() expands \n to \r\n, so the actual emitted sequence is 19 bytes.
 * The print train is ~40 ms/char × 19 chars ≈ 760 ms, so 1000 ms capture
 * window after release leaves margin. */
static const sim_identity_test_t classic_identity_test = {
    .dip_value             = 0,
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

#endif
