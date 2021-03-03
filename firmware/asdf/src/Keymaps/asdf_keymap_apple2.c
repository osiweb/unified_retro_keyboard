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


#include "asdf_keymap_apple2.h"
#include "asdf_keymap_defs_dipswitch.h"

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



// PROCEDURE: apple_add_map

// INPUTS: asdf_keycode_t (*matrix) - a SOL_NUM_ROWS x SOL_NUM_COLS matrix of
//           keycodes for each physical row/column pair
//         modifier_index_t modifier index - the modifier state corresponding to
//           the keycode matrix
//
// OUTPUTS: none
// DESCRIPTION: Passes the keycode matrix and modifier state through to
// asdf_keymaps_add_map(), along with the row/column dimensions.
//
// SIDE EFFECTS: the matrix is added to the keymap
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void apple_add_map(const asdf_keycode_t (*matrix)[APPLE_NUM_COLS],
                            modifier_index_t modifier_index)
{
  asdf_keymaps_add_map(&matrix[0][0], modifier_index, (uint8_t) APPLE_NUM_ROWS,
                       (uint8_t) APPLE_NUM_COLS);
}

void setup_classic_keymap(void)
{
  apple_add_map(apple_plain_map, MOD_PLAIN_MAP);
  apple_add_map(apple_caps_map, MOD_CAPS_MAP);
  apple_add_map(apple_shift_map, MOD_SHIFT_MAP);
  apple_add_map(apple_ctrl_map, MOD_CTRL_MAP);

  asdf_virtual_init();


  // Attach the physical POWER LED as the CAPS LED. Assign no triggered
  // function, and initialize to initial state of the CAPS logic. The CAPS LED
  // will be controlled by the state of the CAPSLOCK logic.
        { .virtual_device = VCAPS_LED, .physical_device = APPLE_POWER_LED, .initial_value = 0 },       \
          asdf_virtual_assign(VCAPS_LED, APPLE_POWER_LED, V_NOFUNC, APPLE_POWER_LED_INIT_VALUE);

  // Assign CAPS LED to virtual CAPS LED, and initialize to the INIT value, to
  // match the initial CAPSLOCK state. The capslock state code will alter the
  // virtual LED according to the state.
  asdf_virtual_assign(VCAPS_LED, APPLE_CAPS_LED, V_NOFUNC, APPLE_CAPS_LED_INIT_VALUE);
  { .virtual_device = APPLE_VIRTUAL_DISABLED_LED,                                              \
      .physical_device = APPLE_DISABLED_LED,                                                     \
      .initial_value = 0 },                                                                      \

  // assign RESET output to the virtual RESET output, configure to produce a short pulse when activated
  asdf_virtual_assign(APPLE_VIRTUAL_RESET, APPLE_RESET_OUTPUT, V_PULSE_SHORT, !APPLE_RESET_ACTIVE_VALUE);

  // assign the CLRSCR output to the virtual CLRSCR output, configure to produce a long pulse when activated
  asdf_virtual_assign(APPLE_VIRTUAL_CLR_SCR, APPLE_CLR_SCR_OUTPUT, V_PULSE_LONG, !APPLE_CLR_SCR_ACTIVE_VALUE);
}



//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

