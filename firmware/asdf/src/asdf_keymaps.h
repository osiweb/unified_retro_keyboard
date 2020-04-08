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


// Define the bit position of each keymap DIP switch. The DIP switch values at
// each bit position can be used to select the current keymap. This requires the
// DIP switches to be mapped to the asdf_keymaps_select_X_set() and
// asdf_keymaps_select_X_clear() functions in each keymap.
#define ASDF_KEYMAP_BIT_0 1
#define ASDF_KEYMAP_BIT_1 2
#define ASDF_KEYMAP_BIT_2 4
#define ASDF_KEYMAP_BIT_3 8

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

// PROCEDURE: asdf_keymaps_get_`code
// INPUTS: row, col: row and column of key that has been pressed
//         modifiers_index: index into the keymap array, based on modifier state
// OUTPUTS: returns a key code.
// DESCRIPTION: Given a key row and column, and an index based on modifier
// state, return the appropriate keycode.
asdf_keycode_t asdf_keymaps_get_code(uint8_t row, uint8_t col, uint8_t modifier_index);


#endif /* !defined (ASDF_KEYMAPS_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
