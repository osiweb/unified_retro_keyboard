// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_classic.c
//
// Implements the "classic" ADM 3A style keymaps
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

#include "asdf_keymaps.h"
#include "asdf_virtual.h"
#include "asdf_keymap_classic.h"
#include "asdf_keymap_classic_add_map.h"

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

void setup_classic_caps_keymap(void)
{
  // for the ALL CAPS keymap, the "plain" mode is the same as "all caps" mode:
  classic_add_map(CLASSIC_CAPS_MAP, MOD_PLAIN_MAP);
  classic_add_map(CLASSIC_CAPS_MAP, MOD_CAPS_MAP);
  classic_add_map(CLASSIC_SHIFT_MAP, MOD_SHIFT_MAP);
  classic_add_map(CLASSIC_CTRL_MAP, MOD_CTRL_MAP);

  asdf_virtual_init();

  // Assign power LED to virtual power LED, and initialize to ON
  asdf_virtual_assign(CLASSIC_VIRTUAL_POWER_LED, CLASSIC_POWER_LED, V_NOFUNC, CLASSIC_POWER_LED_INIT_VALUE);

  // Because the virtual power LED never changes, also assign the CAPSLOCK
  // physical LED to the virtual Power LED, and intialize to OFF (or can change
  // to ON depending on preference)
  asdf_virtual_assign(CLASSIC_VIRTUAL_POWER_LED, CLASSIC_CAPS_LED, V_NOFUNC, CLASSIC_CAPS_LED_INIT_VALUE);

  // assign RESET output to the virtual RESET output, configure to produce a short pulse when activated
  asdf_virtual_assign(CLASSIC_VIRTUAL_RESET, CLASSIC_RESET_OUTPUT, V_PULSE_SHORT, !CLASSIC_RESET_ACTIVE_VALUE);

  // assign the CLRSCR output to the virtual CLRSCR output, configure to produce a long pulse when activated
  asdf_virtual_assign(CLASSIC_VIRTUAL_CLR_SCR, CLASSIC_CLR_SCR_OUT, V_PULSE_LONG, !CLASSIC_CLR_SCR_ACTIVE_VALUE);
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
