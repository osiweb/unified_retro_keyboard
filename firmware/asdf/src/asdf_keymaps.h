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



#define ASDF_KEYMAP_BIT_0 1
#define ASDF_KEYMAP_BIT_1 2
#define ASDF_KEYMAP_BIT_2 4
#define ASDF_KEYMAP_BIT_3 8

typdef enum {
             CLEAR_OUT1,
             SET_OUT1,
             CLEAR_OUT2,
             SET_OUT2,
             CLEAR_OUT3,
             SET_OUT3,
             CLEAR_OC1,
             SET_OC1,
             CLEAR_OC3,
             SET_OC3,
             PULSE_OUT1,
             PULSE_OUT2,
             PULSE_OUT3,
             TOGGLE_OUT1,
             TOGGLE_OUT2,
             TOGGLE_OUT3,
             ON_VLED1,
             OFF_VLED1,
             ON_VLED2,
             OFF_VLED2,
             ON_VLED3,
             OFF_VLED3,
             SET_CAPS_LED1,
             SET_CAPS_LED2,
             SET_CAPS_LED3,
             SET_SHIFTLOCK_LED1,
             SET_SHIFTLOCK_LED2,
             SET_SHIFTLOCK_LED3,
             SET_VLED1_LED1,
             SET_VLED2_LED1,
             SET_VLED3_LED1,
             SET_VLED1_LED2,
             SET_VLED2_LED2,
             SET_VLED3_LED2,
             SET_VLED1_LED3,
             SET_VLED2_LED3,
             SET_VLED3_LED3,

} keymap_init_t



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
