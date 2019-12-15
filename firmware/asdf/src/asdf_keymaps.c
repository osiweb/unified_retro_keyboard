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
#include "asdf_keymaps.h"

typedef asdf_keycode_t keycode_matrix_t[ASDF_NUM_ROWS][ASDF_NUM_COLS];

static const FLASH keycode_matrix_t plain_matrix = ASCII_PLAIN_MAP;
static const FLASH keycode_matrix_t shift_matrix = ASCII_SHIFT_MAP;
static const FLASH keycode_matrix_t caps_matrix = ASCII_CAPS_MAP;
static const FLASH keycode_matrix_t ctrl_matrix = ASCII_CTRL_MAP;

static keycode_matrix_t const *modifier_matrix[MOD_NUM_MAPS];


// PROCEDURE: asdf_keymaps_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Assigns the keymaps to the indices specified by the modifier
// index, to avoid hard-coding constant index values.
//
// SIDE EFFECTS: builds up the private map table.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymaps_init(void)
{
  modifier_matrix[MOD_PLAIN_MAP] = &plain_matrix;
  modifier_matrix[MOD_SHIFT_MAP] = &shift_matrix;
  modifier_matrix[MOD_CAPS_MAP] = &caps_matrix;
  modifier_matrix[MOD_CTRL_MAP] = &ctrl_matrix;
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
// COMPLEXITY: 1
//
asdf_keycode_t asdf_keymaps_get_code(const uint8_t row, const uint8_t col,
                                     const uint8_t modifier_index)
{
  const keycode_matrix_t *matrix = modifier_matrix[modifier_index];

  return FLASH_READ_MATRIX_ELEMENT(*matrix, row, col);
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
