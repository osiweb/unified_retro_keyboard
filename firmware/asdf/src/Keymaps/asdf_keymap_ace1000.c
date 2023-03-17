// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_classic.c
//
// Implements the Franklin ACE 1000 keymaps
//
// Copyright 2023 Chris RYU
// Copyright 2019 David Fenyes
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.
//

#include "asdf.h"
#include "asdf_keymaps.h"
#include "asdf_virtual.h"
#include "asdf_modifiers.h"
#include "asdf_print.h"
#include "asdf_keymap_ace1000.h"
#include "asdf_keymap_ace1000_add_map.h"
#include "asdf_keymap_apple2_add_map.h"

void ace1000_id_message(void) {
  asdf_print("[Keymap: ace1000]\n");
}

// PROCEDURE:
// INPUTS:
// OUTPUTS:
//
// DESCRIPTION:
//
// SIDE EFFECTS:
//
// NOTES:
//
// SCOPE:
//
// COMPLEXITY:
//

void setup_ace1000_keymap(void)
{
  asdf_set_print_delay(ASDF_ACE1000_PRINT_SPEED); //msec

  ace1000_add_map(ACE1000_PLAIN_MAP, MOD_PLAIN_MAP);
  ace1000_add_map(ACE1000_CAPS_MAP, MOD_CAPS_MAP);
  ace1000_add_map(ACE1000_SHIFT_MAP, MOD_SHIFT_MAP);
  ace1000_add_map(ACE1000_CTRL_MAP, MOD_CTRL_MAP);

  asdf_hook_assign(ACE1000_ID_MESSAGE_HOOK, ace1000_id_message);
  asdf_hook_assign(APPLESOFT_KEYBOARD_TEST_HOOK, ace1000_keyboard_test);

  // Assign power LED to virtual power LED, and initialize to ON
  asdf_virtual_assign(ACE1000_VIRTUAL_POWER_LED, ACE1000_POWER_LED, V_NOFUNC, ACE1000_POWER_LED_INIT_VALUE);

  // Assign CAPS LED to virtual CAPS LED, and initialize to the INIT value, to
  // match the initial CAPSLOCK state. The capslock state code will alter the
  // virtual LED according to the state.

  asdf_virtual_assign(VCAPS_LED, ACE1000_CAPS_LED, V_NOFUNC, ACE1000_CAPS_LED_INIT_VALUE);

  // assign RESET output to the virtual RESET output, configure to produce a short pulse when activated
  asdf_virtual_assign(ACE1000_VIRTUAL_RESET, ACE1000_RESET_OUTPUT, V_PULSE_SHORT, !ACE1000_RESET_ACTIVE_VALUE);

  // assign the CLRSCR output to the virtual CLRSCR output, configure to produce a long pulse when activated
  asdf_virtual_assign(ACE1000_VIRTUAL_CLR_SCR, ACE1000_CLR_SCR_OUT, V_PULSE_LONG, !ACE1000_CLR_SCR_ACTIVE_VALUE);
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
