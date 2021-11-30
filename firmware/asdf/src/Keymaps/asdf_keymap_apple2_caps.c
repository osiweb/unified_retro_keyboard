// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_apple2_caps.c
//
// set up keymaps for ALL CAPS Apple II keyboards
//
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


#include "asdf_print.h"
#include "asdf_keymaps.h"
#include "asdf_virtual.h"
#include "asdf_modifiers.h"
#include "asdf_keymap_apple2_add_map.h"

// PROCEDURE: setup_apple2_caps_keymap
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Set up keymaps for ALL CAPS apple 2 keyboard
//
// SIDE EFFECTS: See DESCRIPTION
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void setup_apple2_caps_keymap(void)
{

  asdf_print("[Keymap: Apple 2 CAPS]");

  apple_add_map(APPLE_CAPS_MAP, MOD_PLAIN_MAP);
  apple_add_map(APPLE_CAPS_MAP, MOD_CAPS_MAP);
  apple_add_map(APPLE_CAPS_SHIFT_MAP, MOD_SHIFT_MAP);
  apple_add_map(APPLE_CTRL_MAP, MOD_CTRL_MAP);

  asdf_virtual_init();


  // Turn the POWER LED on and don't assign to any function

  asdf_virtual_assign(APPLE_VIRTUAL_POWER_LED, APPLE_POWER_LED, V_NOFUNC, APPLE_POWER_LED_INIT_VALUE);

  // Assign CAPS LED to off (disabled)
  asdf_virtual_assign(APPLE_VIRTUAL_DISABLED_LED, APPLE_DISABLED_LED, V_NOFUNC, APPLE_DISABLED_INIT_VALUE);

  // assign RESET output to the virtual RESET output, configure to produce a short pulse when activated
  asdf_virtual_assign(APPLE_VIRTUAL_RESET, APPLE_RESET_OUTPUT, V_PULSE_SHORT, !APPLE_RESET_ACTIVE_VALUE);

  // assign the CLRSCR output to the virtual CLRSCR output, configure to produce a long pulse when activated
  asdf_virtual_assign(APPLE_VIRTUAL_CLR_SCR, APPLE_CLR_SCR_OUTPUT, V_PULSE_LONG, !APPLE_CLR_SCR_ACTIVE_VALUE);
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
