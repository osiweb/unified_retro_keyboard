// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Universal Keyboard Project
// ASDF keyboard firmware
//
// asdf.h
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

#if !defined(ASDF_H)
#define ASDF_H

#define ASDF_NUM_ROWS 8
#define ASDF_NUM_COLS 8
#define ASDF_ACTION 0x80
#define ASDF_INVALID_CODE 0x80
// an action code is not a valid keycode.

// for efficiency on 8-bit machines, use 8 columns per row. For 16 columns per
// row, change cols_t to uint16_t and increase ASDF_NUM_COLS.
typedef uint8_t asdf_cols_t;

// ASCII keycodes are 7 bits. An 8-bit datatype encodes ASCII, plus a flag for a
// key function. For longer codes, such as extended ASCII or unicode, change
// keycode_t appropriately, and also change ASDF_ACTION so that the action key
// codes (enumerated in action_t) do not conflict with the encoding scheme.
typedef uint8_t asdf_keycode_t;

typedef enum {
  ACTION_NOTHING = ASDF_ACTION,
  ACTION_SHIFT = ASDF_ACTION + 0x01,
  ACTION_SHIFT_LOCK = ASDF_ACTION + 0x02,
  ACTION_CAPS = ASDF_ACTION + 0x03,
  ACTION_CTRL = ASDF_ACTION + 0x04,
  ACTION_REPEAT = ASDF_ACTION + 0x05,
  ACTION_LOCAL = ASDF_ACTION + 0x06,
  ACTION_BREAK = ASDF_ACTION + 0x07,
  ACTION_HERE_IS = ASDF_ACTION + 0x08,
  ACTION_CLEAR = ASDF_ACTION + 0x09,
  ACTION_FN_1 = ASDF_ACTION + 0x11,
  ACTION_FN_2 = ASDF_ACTION + 0x12,
  ACTION_FN_3 = ASDF_ACTION + 0x13,
  ACTION_FN_4 = ASDF_ACTION + 0x14,
  ACTION_FN_5 = ASDF_ACTION + 0x15,
  ACTION_FN_6 = ASDF_ACTION + 0x16,
  ACTION_FN_7 = ASDF_ACTION + 0x17,
  ACTION_FN_8 = ASDF_ACTION + 0x18,
  ACTION_FN_9 = ASDF_ACTION + 0x19,
  ACTION_FN_10 = ASDF_ACTION + 0x1a
} action_t;


// PROCEDURE: asdf_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: initialize the keyboard state and debounce counters
void asdf_init(void);

// PROCEDURE: asdf_keyscan
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Scans the key matrix. For each row, read the columns and compare
// with last stable state. For each changed key, call a key-change handler
// function. For each stable pressed key, call a "continued press" handler
// function.
void asdf_keyscan(void);

// PROCEDURE: asdf_put_code
// INPUTS: (asdf_keycode_t) code: code to be buffered for output
// OUTPUTS: none
// DESCRIPTION: Takes a keycode argument and buffers for output.
// NOTES: If buffer is full, silently drop the code.
void asdf_put_code(asdf_keycode_t code);

// PROCEDURE: asdf_get_code
// INPUTS: none
// OUTPUTS: (asdf_keycode_t) returns next value in buffer.
// DESCRIPTION: Takes a keycode argument and buffers for output.
asdf_keycode_t asdf_get_code(void);

#endif // !defined (ASDF_H)


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

