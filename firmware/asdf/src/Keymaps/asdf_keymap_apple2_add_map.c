// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_classic.c
//
// defines the keymap matrices used by the "classic" ADM 3A style keymap variants
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

#include "asdf_arch.h"
#include "asdf.h"
#include "asdf_print.h"
#include "asdf_ascii.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_apple2_add_map.h"

// Key Matrix for combination of ASCII controller and Apple ASCII matrix
//
// Col->   0          1          2          3          4          5          6          7
// Row 0   POWER      R-Shift    L-Shift    (no key)   ESC        TAB        CTRL       \(backslash)
// Row 1   Rubout     P          ;          /          SPACEBAR   Z          A          Q
// Row 2   Break      ,(comma)   M          N          B          V          C          X
// Row 3   Spare      K          J          H          G          F          D          A
// Row 4   Rt arrow   I          U          Y          T          R          E          W
// Row 5   LT arrow   Repeat     CapsLock   Return     LineFeed   O(alpha)   L          .(period)
// Row 6   ~(tilde)   ]          [          -(dash)    :(colon)   0(numeral) 9          8
// Row 7   @(at)      7          6          5          4          3          2          1
//
// Row 15 DIP switches 0-7
//
// Notes:
//
// 1) The keys above correspond to the silk screen on the PCB. For the OSI and
//    Apple layouts, the keys may not all match the silk screen. When creating a
//    layout different from the silk screen, look up the row and column for the
//    silk screen label at the desired position, and then place the desired
//    function in the keymap definition at the desired row and column. For
//    example, the Apple 2 keymap places the "RESET" key at the "[" silk-screen
//    position, Row 6, Col 2. The keymap places ACTION_RESET at Row 6, Col 2 in
//    the "ASDF_APPLE2_CTRL_MAP" to map the RESET function to the CTRL-RESET key
//    combination.
//
// 2) To ensure consistent DIP switch operation within the keymap, a
//    ASDF_ASCII_DIP_SWITCHES macro is defined. Keeping the ACTION_MAPSEL0-3
//    definitions in positions 0-3 ensures consistent map selection among all
//    keymaps.

#define ASDF_APPLE2_DIP_SWITCHES ASDF_KEYMAP_DIP_SWITCHES

typedef asdf_keycode_t apple_keycode_matrix_t[ASDF_APPLE2_NUM_ROWS][ASDF_APPLE2_NUM_COLS];


const FLASH apple_keycode_matrix_t apple_plain_matrix = {
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,
           ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW },
   [1] = { ASCII_DEL, 'p', ';', '/', ASCII_SPACE, 'z', 'a', 'q' },
   [2] = { ACTION_NOTHING, ASCII_COMMA, 'm', 'n', 'b', 'v', 'c', 'x' },
   [3] = { ACTION_NOTHING, 'k', 'j', 'h', 'g', 'f', 'd', 's' },
   [4] = { ACTION_NOTHING, 'i', 'u', 'y', 't', 'r', 'e', 'w' },
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, '^', 'o', 'l', ASCII_PERIOD },
   [6] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, '-', ':', ASCII_ZERO, '9', '8' },
   [7] = { APPLE_LEFT_ARROW, '7', '6', '5', '4', '3', '2', '1' },
   ASDF_APPLE2_DIP_SWITCHES
};

const FLASH apple_keycode_matrix_t apple_shift_matrix = {
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,
     ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW },
   [1] = { ACTION_NOTHING, 'P', '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },
   [2] = { ACTION_NOTHING, '<', 'M', 'N', 'B', 'V', 'C', 'X' },
   [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },
   [4] = { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, ASCII_AT, 'O', 'L', '>' },
   [6] = { ACTION_NOTHING, ACTION_NOTHING, APPLE_ACTION_CLEAR, '=',
           '*',         ASCII_ZERO,           ASCII_RT_PAREN,       ASCII_LT_PAREN },
   [7] = { APPLE_LEFT_ARROW, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' },
   ASDF_APPLE2_DIP_SWITCHES
};

const FLASH apple_keycode_matrix_t apple_caps_shift_matrix = {
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,
     ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW },
   [1] = { ACTION_NOTHING, ASCII_AT, '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },
   [2] = { ACTION_NOTHING, '<', 'M', '^', 'B', 'V', 'C', 'X' },
   [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },
   [4] = { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, ACTION_REPEAT, 'O', 'L', '>' },
   [6] = { ACTION_NOTHING, ACTION_NOTHING, APPLE_ACTION_CLEAR, '=',
           '*', ASCII_ZERO, ASCII_RT_PAREN, ASCII_LT_PAREN },
   [7] = { APPLE_LEFT_ARROW, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' },
   ASDF_APPLE2_DIP_SWITCHES
};

const FLASH apple_keycode_matrix_t apple_caps_matrix = {
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,
            ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW },
    [1] = { ACTION_NOTHING, 'P', ';', '/', ASCII_SPACE, 'Z', 'A', 'Q' },
    [2] = { ACTION_NOTHING, ASCII_COMMA, 'M', 'N', 'B', 'V', 'C', 'X' },
    [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },
    [4] = { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },
    [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, ACTION_REPEAT, 'O', 'L', ASCII_PERIOD },
    [6] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, '-', ':', ASCII_ZERO, '9', '8' },
    [7] = { APPLE_LEFT_ARROW, '7', '6', '5', '4', '3', '2', '1' },
    ASDF_APPLE2_DIP_SWITCHES
};

const FLASH apple_keycode_matrix_t apple_ctrl_matrix = {
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,
           ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW },
   [1] = { ACTION_NOTHING, ASCII_CTRL_P, ACTION_NOTHING, ACTION_NOTHING,
           ASCII_SPACE,    ASCII_CTRL_Z, ASCII_CTRL_A,   ASCII_CTRL_Q },
   [2] = { ACTION_NOTHING, ASCII_COMMA, ASCII_CTRL_M, ASCII_CTRL_N,
           ASCII_CTRL_B, ASCII_CTRL_V, ASCII_CTRL_C, ASCII_CTRL_X },
   [3] = { ACTION_NOTHING, ASCII_CTRL_K, ASCII_CTRL_J, ASCII_CTRL_H,
           ASCII_CTRL_G, ASCII_CTRL_F, ASCII_CTRL_D, ASCII_CTRL_S },
   [4] = { ACTION_NOTHING, ASCII_CTRL_I, ASCII_CTRL_U, ASCII_CTRL_Y,
           ASCII_CTRL_T, ASCII_CTRL_R, ASCII_CTRL_E, ASCII_CTRL_W },
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING,  ASCII_CR,
           ACTION_REPEAT,      ASCII_CTRL_O,   ASCII_CTRL_L, ACTION_NOTHING },
   [6] = { ACTION_NOTHING, ACTION_NOTHING, APPLE_ACTION_RESET,   ACTION_NOTHING,
           ACTION_NOTHING, ACTION_FN_10, ACTION_FN_9, ACTION_FN_8 },
   [7] = { APPLE_LEFT_ARROW, ACTION_FN_7, ACTION_FN_6, ACTION_FN_5,
            ACTION_FN_4, ACTION_FN_3, ACTION_FN_2, ACTION_FN_1 },
   ASDF_APPLE2_DIP_SWITCHES
};



static const apple_keycode_matrix_t *apple_maps[] = {
  [APPLE_CAPS_MAP] = &apple_caps_matrix,
  [APPLE_PLAIN_MAP] = &apple_plain_matrix,
  [APPLE_SHIFT_MAP] = &apple_shift_matrix,
  [APPLE_CTRL_MAP] = &apple_ctrl_matrix,
  [APPLE_CAPS_SHIFT_MAP] = &apple_caps_shift_matrix
};

void applesoft_keyboard_test(void)
{
    asdf_print("10 GET A$\r");
    asdf_print("20 A = ASC(A$)\r");
    asdf_print("30 IF A < 32 THEN A$=\"CTL+\"+CHR$(A + 64)\r");
    asdf_print("40 ?\"'\";A$;\"' = \";A:\r");
    asdf_print("50 IF A <> 3 GOTO 10\r");
    asdf_print("60 END\rRUN\r");

}

void apple_add_map(const apple_map_index_t map_index,
                       modifier_index_t modifier_index)
{

  asdf_keycode_t (*matrix)[ASDF_APPLE2_NUM_COLS] =
    (asdf_keycode_t (*)[ASDF_APPLE2_NUM_COLS]) apple_maps[map_index];

    asdf_keymaps_add_map(&matrix[0][0], modifier_index, (uint8_t) ASDF_APPLE2_NUM_ROWS,
                       (uint8_t) ASDF_APPLE2_NUM_COLS);
}



//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
