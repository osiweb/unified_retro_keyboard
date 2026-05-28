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

/* SOL identity test: not provided.
 *
 * sol_id_message() is bound to SOL_ID_MESSAGE_HOOK (ASDF_HOOK_USER_10) in
 * setup_sol_keymap(), so the hook IS assigned.  However, neither sol_ctrl_map
 * (in asdf_keymap_sol.c) nor ASDF_SOL_CTRL_MAP (in asdf_keymap_defs_sol.h)
 * contains ACTION_FN_10, which is the only way to fire ASDF_HOOK_USER_10 via
 * a keypress.  There is therefore no reachable key sequence that triggers the
 * ID hook, and no identity test is possible until a trigger key is added to
 * the ctrl matrix. */

#endif
