// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*- 
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_table.c
//
// initialize keymap setup function table
//
// *** This is configured for testing.
// *** NOT auto-generated
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

#define ASDF_NUM_KEYMAPS 11

// define the type for a keymap setup function. Keymaps are registerd by storing
// a keymap setup function in the keymap setup array.

// PROCEDURE: asdf_keymap_setup
// INPUTS: (uint8_t) index - index of the keymap setup function to call
// OUTPUTS: none
// DESCRIPTION: This function calls the keymap setup function specified
//              by the index.
// SIDE EFFECTS: See Description
void asdf_keymap_setup(uint8_t index);

// PROCEDURE: asdf_keymap_valid
// INPUTS: (uint8_t) index - index of the keymap setup function to check
// OUTPUTS: (uintu_t) returns TRUE (nonzero) if valid, FALSE (0) otherwise
// DESCRIPTION: This function returns TRUE if the index corresponds to
//              a valid keymap.
uint8_t asdf_keymap_valid(uint8_t index);

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

