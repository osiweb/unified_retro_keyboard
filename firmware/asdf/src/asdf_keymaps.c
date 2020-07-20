// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymaps.c
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

#include <stdint.h>
#include "asdf.h"
#include "asdf_arch.h"
#include "asdf_physical.h"
#include "asdf_virtual.h"
#include "asdf_hook.h"
#include "asdf_repeat.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"

// ASDF_KEYMAP_DECLARATIONS is defined in asdf_keymap_defs.h, aggregated from
// all the included keymap definition files.
//
// This is a terrible practice, but defining the declarations as a macro permits
// the keymap definitions to be incorporated in a fairly modular fashion, using
// the limited capabilities of the C preprocessor. One alternative is to use a
// program (in C or at the expense of additional build dependencies, in python
// or bash) to generate the keymap definitions and declarations from a
// definition file. But then the keymap declarations would not be private.
// constexpr in C++ may be an alternative option as well.
ASDF_KEYMAP_DECLARATIONS;

// The keymap arrays organized as follows:
// * Each keymap matrix is a NUM_ROWS x NUM_COLS mapping of key to code for a given modifier.
// * Each keymap contains a set of keymap matrices, one for each unique
//   combination of modifier keys.
// * All the keymaps (NUM_KEYMAPS) are gathered in the keymap_matrixp[] array.
static keycode_matrix_t const *keymap_matrix[ASDF_NUM_KEYMAPS][ASDF_MOD_NUM_MODIFIERS] =
  ASDF_KEYMAP_DEFS;


// Each keymap (representing a keyboard configuration) has an associated set of
// virtual device initializers that set up the I/O and LED lines for the
// keyboard, unique to each keymap. This builds the virtual device initializer
// array from the initializer definitions in the keymap definition files.
static const asdf_virtual_initializer_t keymap_initializer_list[ASDF_NUM_KEYMAPS]
                                                               [ASDF_KEYMAP_INITIALIZER_LENGTH] =
                                                                 ASDF_KEYMAP_INITIALIZERS;

// Each keymap (representing a keyboard configuration) has an associated set of
// function hooks unique to the keyboard defined by the map. This builds the
// function hook initializer array from the definitions in the keymap definition
// files.
static const asdf_hook_initializer_t
  keymap_hook_initializer_list[ASDF_NUM_KEYMAPS][ASDF_KEYMAP_HOOK_INITIALIZER_LENGTH] =
    ASDF_KEYMAP_HOOK_INITIALIZERS;

// Index of the currently active keymap, initialized to zero in the init
// routine.
static uint8_t keymap_index;


// PROCEDURE: asdf_keymaps_select_keymap
// INPUTS: (uint8_t) index - index of the keymap number to select
// OUTPUTS: none
//
// DESCRIPTION: accepts a index value. If the requested keymap index is valid,
// then:
// 1) assign the value to the global (to the module) keymap_index variable
// 2) execute the architecture-dependent init routine, to undo any settings
//    from the previous keymap
// 3) initialize the virtual outputs for the selected keymap.
// 4) initialize the modifier key states.
//
// SIDE EFFECTS:
// - May change the module-global keymap_index variable.
// - Architecture is initialized to default configuration.
//
// NOTES: 1) If the requested index is not valid, then no action is performed.
//
//        2) Hooks are initialized after repeat apparratus and modifiers states
//        are initialized, so that hooks can be used to modify default modifier
//        states for a map.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_keymaps_select_keymap(uint8_t index)
{
  if (index < ASDF_NUM_KEYMAPS) {
    keymap_index = index;

    asdf_arch_init();

    asdf_virtual_init((asdf_virtual_initializer_t *const) keymap_initializer_list[keymap_index]);

    asdf_modifiers_init();

    asdf_repeat_init();

    asdf_hook_init((asdf_hook_initializer_t *const) keymap_hook_initializer_list[keymap_index]);
  }
}

// PROCEDURE: asdf_keymaps_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Selects the base keymap.
//
// SIDE EFFECTS: builds up the private map table.
//
// SCOPE: public
//
// NOTES: Note that the DIP switches are keys in the key matrix, which is
// initialized to the all unpressed state at startup. Since the keymap is
// initialized to 0, the keymap is consistent with the presumed initial state of
// the DIP switches. If the DIP switches are not set to Keymap 0, then their
// position will be detected as keypresses, and the correct keymap will be set.

// COMPLEXITY: 1
//
void asdf_keymaps_init(void)
{
  asdf_keymaps_select_keymap(0);
}

// PROCEDURE: asdf_keymaps_map_select_0_clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 0 switch is open. Clears the 0 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_0_clear(void)
{
  asdf_keymaps_select_keymap(keymap_index & (~ASDF_KEYMAP_BIT_0));
}

// PROCEDURE: asdf_keymaps_map_select_0_set
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 0 switch is closed. Sets the 0 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_0_set(void)
{
  asdf_keymaps_select_keymap(keymap_index | ASDF_KEYMAP_BIT_0);
}

// PROCEDURE: asdf_keymaps_map_select_1_clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 1 switch is open. Clears the 1 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_1_clear(void)
{
  asdf_keymaps_select_keymap(keymap_index & (~ASDF_KEYMAP_BIT_1));
}

// PROCEDURE: asdf_keymaps_map_select_1_set
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 1 switch is closed. Sets the 1 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_1_set(void)
{
  asdf_keymaps_select_keymap(keymap_index | ASDF_KEYMAP_BIT_1);
}

// PROCEDURE: asdf_keymaps_map_select_2_clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 2 switch is open. Clears the 2 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_2_clear(void)
{
  asdf_keymaps_select_keymap(keymap_index & (~ASDF_KEYMAP_BIT_2));
}

// PROCEDURE: asdf_keymaps_map_select_2_set
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 2 switch is closed. Sets the 2 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_2_set(void)
{
  asdf_keymaps_select_keymap(keymap_index | ASDF_KEYMAP_BIT_2);
}

// PROCEDURE: asdf_keymaps_map_select_3_clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 3 switch is open. Clears the 3 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_3_clear(void)
{
  asdf_keymaps_select_keymap(keymap_index & (~ASDF_KEYMAP_BIT_3));
}

// PROCEDURE: asdf_keymaps_map_select_3_set
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: called when map select 3 switch is closed. Sets the 3 bit in the
// keymap index.
//
// SIDE EFFECTS: changes selected keymap
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_map_select_3_set(void)
{
  asdf_keymaps_select_keymap(keymap_index | ASDF_KEYMAP_BIT_3);
}

// PROCEDURE: asdf_keymaps_get_code
// INPUTS: row, col: row and column of key that has been pressed
//         modifiers_index: index into the keymap array, based on modifier state
// OUTPUTS: returns a key code.
//
// DESCRIPTION: Given a key row and column, and an index based on modifier
// state, return the appropriate keycode.
//
// SIDE EFFECTS: none
//
// SCOPE: public
//
// NOTES: Since the first value in each row is the physical row number, we add 1
// to the column number to read the code for a given row and column number.
//
// COMPLEXITY: 1
//
asdf_keycode_t asdf_keymaps_get_code(const uint8_t row, const uint8_t col,
                                     const uint8_t modifier_index)
{
  const keycode_matrix_t *matrix = keymap_matrix[keymap_index][modifier_index];

  return FLASH_READ_MATRIX_ELEMENT(*matrix, row, col);
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
