// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*- 
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_apple2.c
//
// set up keymaps for Apple II keyboards
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
#include "asdf_keymap_apple2.h"

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

void apple2_id_message(void) {
  asdf_print("[Keymap: Apple 2 (u/l case)]");
}

void setup_apple2_keymap(void)
{
  asdf_set_print_delay(APPLE2_PRINT_DELAY);


  apple_add_map(APPLE_PLAIN_MAP, MOD_PLAIN_MAP);
  apple_add_map(APPLE_CAPS_MAP, MOD_CAPS_MAP);
  apple_add_map(APPLE_SHIFT_MAP, MOD_SHIFT_MAP);
  apple_add_map(APPLE_CTRL_MAP, MOD_CTRL_MAP);

  asdf_hook_assign(APPLESOFT_KEYBOARD_TEST, applesoft_keyboard_test);
  asdf_hook_assign(APPLE2_ID_MESSAGE, apple2_id_message);

  // Attach the physical POWER LED as the CAPS LED. Assign no triggered
  // function, and initialize to initial state of the CAPS logic. The CAPS LED
  // will be controlled by the state of the CAPSLOCK logic.

  asdf_virtual_assign(VCAPS_LED, APPLE_POWER_LED, V_NOFUNC, APPLE_POWER_LED_INIT_VALUE);

  // Assign CAPS LED to off (disabled)
  asdf_virtual_assign(APPLE_VIRTUAL_DISABLED_LED, APPLE_DISABLED_LED, V_NOFUNC, APPLE_DISABLED_INIT_VALUE);

  // assign RESET output to the virtual RESET output, configure to produce a short pulse when activated
  asdf_virtual_assign(APPLE_VIRTUAL_RESET, APPLE_RESET_OUTPUT, V_PULSE_SHORT, !APPLE_RESET_ACTIVE_VALUE);

  // assign the CLRSCR output to the virtual CLRSCR output, configure to produce a long pulse when activated
  asdf_virtual_assign(APPLE_VIRTUAL_CLR_SCR, APPLE_CLR_SCR_OUTPUT, V_PULSE_LONG, !APPLE_CLR_SCR_ACTIVE_VALUE);

  asdf_modifier_capslock_activate(); // For Apple 2, start with CAPS active
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

