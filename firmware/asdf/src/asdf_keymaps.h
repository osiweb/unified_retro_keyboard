// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
//  Unfified Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_keymaps.h
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

// While there is nothing preventing a standard keyboard from having both a
// "Shift Lock" key and a "Caps Lock" key, usually only one will be present. For
// testing, both must be present to test their functionality.

#if !defined(ASDF_KEYMAPS_H)
#define ASDF_KEYMAPS_H

#include "asdf.h"
#include "asdf_hook.h"
#include "asdf_virtual.h"
#include "asdf_physical.h"
#include "asdf_modifiers.h"

// Define the bit position of each keymap DIP switch. The DIP switch values at
// each bit position can be used to select the current keymap. This requires the
// DIP switches to be mapped to the asdf_keymaps_select_X_set() and
// asdf_keymaps_select_X_clear() functions in each keymap.
#define ASDF_KEYMAP_BIT_0 1
#define ASDF_KEYMAP_BIT_1 2
#define ASDF_KEYMAP_BIT_2 4
#define ASDF_KEYMAP_BIT_3 8

#define ASDF_MAX_ROWS 16
#define ASDF_MAX_COLS 8

// define the keycode matrices to be used by the keymaps. Each matrix is a
// mapping of row,column to keycode.
typedef asdf_keycode_t **asdf_keycode_matrix_t;

// define the type for a keymap setup function. Keymaps are registerd by storing
// a keymap setup function in the keymap setup array.
typedef void (*asdf_keymap_setup_function_t)(void);

// define the struct for each keymap matrix in the keymap array. One per
// modifier state. Each keymap can have it's own row and column count.
typedef struct {
  asdf_keycode_matrix_t matrix_ptr;
  uint8_t rows;
  uint8_t cols;
} asdf_keycode_map_t;


// PROCEDURE: asdf_keymaps_register
// INPUTS: (uint8_t) keymap_index - index of the keymap to be modified
//         (asdf_keymap_setup_function_t) keymap setup function - called on
//         keymap change to setup up the keymap
// OUTPUTS: none
// DESCRIPTION: Called by keymap building modules. This routine adds a keymap
// setup function into the keymap setup array.
// NOTES: If the keymap modifier index is not a valid keymap index then no
// action is performed.
void asdf_keymaps_register(uint8_t keymap_index, asdf_keymap_setup_function_t keymap_setup_function);

// PROCEDURE: asdf_keymaps_add_map
// INPUTS: (asdf_keycode_matrix_t *) matrix - pointer to the keycode matrix to add in to map
//         (uint8_t) modifier_index - the modifier value for the keycode matrix being added
//         (uint8_t) rows - number of rows in the keymap
//         (uint8_t) cols - number of columns in the keymap
// OUTPUTS: none
// DESCRIPTION: Called by keymap building modules. This routine adds a keymap to the current
// setup function into the keymap setup array.
// NOTES: If the keymap modifier index, num_rows, or num_cols are not valid then no
// action is performed.
void asdf_keymaps_add_map(asdf_keycode_matrix_t matrix, 
                          modifier_index_t modifier_index,
                          uint8_t num_rows, uint8_t num_cols);

// PROCEDURE: asdf_keymaps_num_rows
// INPUTS: none
// OUTPUTS: uint8_t - returns number of rows in keymap for current modifier state
// DESCRIPTION: See OUTPUTS
uint8_t asdf_keymaps_num_rows(void);

// PROCEDURE: asdf_keymaps_num_cols
// INPUTS: none
// OUTPUTS: uint8_t - returns number of columns in keymap for current modifier state
// DESCRIPTION: See OUTPUTS
uint8_t asdf_keymaps_num_cols(void);

// PROCEDURE: asdf_keymaps_select_keymap
// INPUTS: (uint8_t) index - index of the keymap number to select
// OUTPUTS: none
// DESCRIPTION: accepts a index value. If the requested keymap index is valid,
// then assign the value to the global (to the module) keymap_index variable. If
// requested index is not valid then do nothing.
void asdf_keymaps_select_keymap(uint8_t index);

// PROCEDURE: asdf_keymaps_map_select_0_clear
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 0 switch is open. Clears the 0 bit in the
// keymap index.
void asdf_keymaps_map_select_0_clear(void);

// PROCEDURE: asdf_keymaps_map_select_0_set
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 0 switch is closed. Sets the 0 bit in the
// keymap index, if the resulting keymap index is valid.  Otherwise do nothing.
void asdf_keymaps_map_select_0_set(void);

// PROCEDURE: asdf_keymaps_map_select_1_clear
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 1 switch is open. Clears the 1 bit in the
// keymap index.
void asdf_keymaps_map_select_1_clear(void);

// PROCEDURE: asdf_keymaps_map_select_1_set
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 1 switch is closed. Sets the 0 bit in the
// keymap index, if the resulting keymap index is valid.  Otherwise do nothing.
void asdf_keymaps_map_select_1_set(void);

// PROCEDURE: asdf_keymaps_map_select_2_clear
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 2 switch is open. Clears the 2 bit in the
// keymap index.
void asdf_keymaps_map_select_2_clear(void);

// PROCEDURE: asdf_keymaps_map_select_2_set
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 2 switch is closed. Sets the 0 bit in the
// keymap index, if the resulting keymap index is valid.  Otherwise do nothing.
void asdf_keymaps_map_select_2_set(void);

// PROCEDURE: asdf_keymaps_map_select_3_clear
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 3 switch is open. Clears the 3 bit in the
// keymap index.
void asdf_keymaps_map_select_3_clear(void);

// PROCEDURE: asdf_keymaps_map_select_3_set
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: called when map select 3 switch is closed. Sets the 0 bit in the
// keymap index, if the resulting keymap index is valid.  Otherwise do nothing.
void asdf_keymaps_map_select_3_set(void);

// PROCEDURE: asdf_keymaps_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Assigns the keymaps to the indices specified by the modifier
// index, to avoid hard-coding constant index values.
void asdf_keymaps_init(void);

// PROCEDURE: asdf_keymap_add_virtual_device
// INPUTS: (asdf_virtual_dev_t) virtual_dev: The virtual device being assigned
//         (asdf_physical_dev_t) physical_dev: The physical device attached to the virtual device
//         (asdf_virtual_function_t) function: the function associated with the virtual device
//         (uint8_t) initial_value: The initial state of the virtual device
// OUTPUTS: none
// DESCRIPTION: Builds the virtual device initializer structure. Uses the
// arguments to build an entry in the virtual device initializer structure for
// the current keymap.
void asdf_keymap_add_virtual_device(asdf_virtual_dev_t virtual_dev,
                                    asdf_physical_dev_t physical_dev,
                                    asdf_virtual_function_t function, uint8_t initial_value);

// PROCEDURE: asdf_keymap_add_hook
// INPUTS: (asdf_hook_id_t) hook_id: type ID for the provided hook function
//         (asdf_hook_function_t) function: the function associated with the hook.
// OUTPUTS: none
// DESCRIPTION: Builds the hook initializer table for the current keymap
void asdf_keymap_add_hook(asdf_hook_id_t hook_id, asdf_hook_function_t function);


// PROCEDURE: asdf_keymaps_get_code
// INPUTS: row, col: row and column of key that has been pressed
//         modifiers_index: index into the keymap array, based on modifier state
// OUTPUTS: returns a key code.
// DESCRIPTION: Given a key row and column, and an index based on modifier
// state, return the appropriate keycode.
asdf_keycode_t asdf_keymaps_get_code(uint8_t row, uint8_t col, uint8_t modifier_index);


#endif /* !defined (ASDF_KEYMAPS_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
