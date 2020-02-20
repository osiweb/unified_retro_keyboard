// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymaps_template.h 
//
// Template file for adding new keymaps.
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


// To use this template for a new keymap, edit the keymaps definitions as
// desired. The keymaps are organized from row 0, counting upward, and each row
// includes the columns from 0-NUM_COLS.
//

#if !defined(ASDF_KEYMAP_DEFS_TEMPLATE_H)
#define ASDF_KEYMAP_DEFS_TEMPLATE_H

#include "asdf_modifier.h"

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#define ASDF_TEMPLATE_NUM_ROWS 16 // DIP switches are row 15.
#define ASDF_TEMPLATE_NUM_COLS 8

#if !defined(ASDF_NUM_ROWS) || (ASDF_NUM_ROWS < ASDF_TEMPLATE_NUM_ROWS)
#undef ASDF_NUM_ROWS
#define ASDF_NUM_ROWS ASDF_TEMPLATE_NUM_ROWS
#endif

#if !defined(ASDF_NUM_COLS) || (ASDF_NUM_COLS < ASDF_ASCII_NUM_COLS)
#undef ASDF_NUM_COLS
#define ASDF_NUM_COLS ASDF_TEMPLATE_NUM_COLS
#endif

// TO ensure consistent DIP switch operation within the keymap, a
// ASDF_TEMPLATE_DIP_SWITCHES macro is defined. Keeping the ACTION_MAPSEL0-3
// definitions in positions 0-3 ensures consistent map selection among all
// keymaps.

#define ASDF_TEMPLATE_DIP_SWITCHES                                      \
  [ASDF_LAST_ROW] = { ACTION_MAPSEL_0, ACTION_MAPSEL_1, ACTION_MAPSEL_2, ACTION_MAPSEL_3 }

#define ASDF_TEMPLATE_PLAIN_MAP                                                                       \
  {                                                                     \
   [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,  \
           ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  ASCII_BACKSLASH }, \
   [1] = { ASCII_DEL, 'p', ';', '/', ASCII_SPACE, 'z', 'a', 'q' },      \
   [2] = { ACTION_BREAK, ASCII_COMMA, 'm', 'n', 'b', 'v', 'c', 'x' },   \
   [3] = { ACTION_NOTHING, 'k', 'j', 'h', 'g', 'f', 'd', 's' },         \
   [4] = { ACTION_CLEAR, 'i', 'u', 'y', 't', 'r', 'e', 'w' },           \
   [5] = { ACTION_REPEAT, ACTION_HERE_IS, ACTION_CAPS, ASCII_CR, ASCII_LF, 'o', 'l', ASCII_PERIOD }, \
   [6] = { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', ASCII_ZERO, '9', '8' }, \
   [7] = { ASCII_AT, '7', '6', '5', '4', '3', '2', '1' },
   ASDF_TEMPLATE_DIP_SWITCHES                   \
  }

#define ASDF_TEMPLATE_CAPS_MAP                                                                          \
  {                                                                     \
    [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING, \
            ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  ASCII_BACKSLASH }, \
    [1] = { ASCII_DEL, 'P', ';', '/', ASCII_SPACE, 'Z', 'A', 'Q' },     \
    [2] = { ACTION_BREAK, ASCII_COMMA, 'M', 'N', 'B', 'V', 'C', 'X' },  \
    [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },        \
    [4] = { ACTION_CLEAR, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },          \
    [5] = { ACTION_REPEAT, ACTION_HERE_IS, ACTION_CAPS, ASCII_CR, ASCII_LF, 'O', 'L', ASCII_PERIOD }, \
    [6] = { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', ASCII_ZERO, '9', '8' }, \
    [7] = { ASCII_AT, '7', '6', '5', '4', '3', '2', '1' },              \
    ASDF_TEMPLATE_DIP_SWITCHES                                          \
  }

#define ASDF_TEMPLATE_SHIFT_MAP                                                                       \
  {                                                                     \
   [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,        \
     ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  ASCII_VERT_BAR },      \
   [1] = { ASCII_DEL, 'P', '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },            \
   [2] = { ACTION_BREAK, '<', 'M', 'N', 'B', 'V', 'C', 'X' },                                         \
   [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },               \
   [4] = { ACTION_CLEAR, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },                                         \
   [5] = { ACTION_REPEAT, ACTION_HERE_IS, ACTION_CAPS, ASCII_CR, ASCII_LF, 'O', 'L', '>' },           \
   [6] = { ASCII_TILDE, ASCII_RT_CURLY_BRACE, ASCII_LT_CURLY_BRACE, '=', \
           '*',         ASCII_ZERO,           ASCII_RT_PAREN,       ASCII_LT_PAREN }, \
   [7] = { ASCII_GRAVE_ACCENT, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' }, \
   ASDF_TEMPLATE_DIP_SWITCHES                                           \
  }

#define ASDF_TEMPLATE_CTRL_MAP                                                                        \
  {                                                                     \
   [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,                                  \
      ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  0x1c },                                          \
   [1] = { ACTION_NOTHING, ASCII_CTRL_P, ACTION_NOTHING, ACTION_NOTHING,      \
        ASCII_SPACE,    ASCII_CTRL_Z, ASCII_CTRL_A,   ASCII_CTRL_Q },                              \
   [2] = { ACTION_RESET, ASCII_COMMA, ASCII_CTRL_M, ASCII_CTRL_N,       \
           ASCII_CTRL_B, ASCII_CTRL_V, ASCII_CTRL_C, ASCII_CTRL_X },    \
   [3] = { ACTION_NOTHING, ASCII_CTRL_K, ASCII_CTRL_J, ASCII_CTRL_H, \
           ASCII_CTRL_G, ASCII_CTRL_F, ASCII_CTRL_D, ASCII_CTRL_S },
   [4] = { ACTION_CLEAR, ASCII_CTRL_I, ASCII_CTRL_U, ASCII_CTRL_Y,      \
        ASCII_CTRL_T, ASCII_CTRL_R, ASCII_CTRL_E, ASCII_CTRL_W },                                  \
   [5] = { ACTION_REPEAT, ACTION_HERE_IS, ACTION_CAPS,  ASCII_CR,       \
        ASCII_LF,      ASCII_CTRL_O,   ASCII_CTRL_L, ACTION_NOTHING },                             \
   [6] = { ACTION_NOTHING, 0x1d,         ASCII_ESC,   ACTION_NOTHING,   \
        ACTION_NOTHING, ACTION_FN_10, ACTION_FN_9, ACTION_FN_8 },                                  \
    [7] = { ACTION_NOTHING, ACTION_FN_7, ACTION_FN_6, ACTION_FN_5, \
            ACTION_FN_4, ACTION_FN_3, ACTION_FN_2, ACTION_FN_2 }, \
    }, ASDF_TEMPLATE_DIP_SWITCHES                                          \
  }

#define ASDF_TEMPLATE_MAP_DECLARATIONS                                                                \
  static const FLASH keycode_matrix_t template_plain_matrix = ASDF_TEMPLATE_PLAIN_MAP;                        \
  static const FLASH keycode_matrix_t template_shift_matrix = ASDF_TEMPLATE_SHIFT_MAP;                        \
  static const FLASH keycode_matrix_t template_caps_matrix = ASDF_TEMPLATE_CAPS_MAP;                          \
  static const FLASH keycode_matrix_t template_ctrl_matrix = ASDF_TEMPLATE_CTRL_MAP;


// Here, you can specify which maps are associated with which modifier keys.
// There can be multiple definitions. For example, as shown here, an ALL CAPS
// keymap can be made by assigning the caps map to the "no modifier" position.
// Or, more additional keymaps can be defined above, and keymap sets can be
// defined below that pick and choose between them.  The modifiers are assigned as follows:
//
// [0]: plain (no modifiers)
// [1]: shift (shift key or shift lock active)
// [2]: caps (caps lock active)
// [3]: ctrl: (control key active)

#define ASDF_TEMPLATE_PLAIN_MAP_DEFS                                    \
  {                                                                     \
   [MOD_PLAIN_MAP] = &template_plain_matrix,                                        \
   [MOD_SHIFT_MAP] = &template_shift_matrix,                                        \
   [MOD_CAPS_MAP] = &template_caps_matrix,                                         \
   [MOD_CTRL_MAP] = &template_ctrl_matrix                                          \
  }

#define ASDF_TEMPLATE_CAPS_MAP_DEFS            \
  {                                             \
   [MOD_PLAIN_MAP] = &template_caps_matrix,    \
   [MOD_SHIFT_MAP] = &template_shift_matrix,    \
   [MOD_CAPS_MAP] = &template_caps_matrix,      \
   [MOD_CTRL_MAP] = &template_ctrl_matrix       \
  }

#define ASDF_TEMPLATE_ALL_MAPS ASDF_TEMPLATE_PLAIN_MAP_DEFS, ASDF_TEMPLATE_CAPS_MAP_DEFS

#define ASDF_TEMPLATE_ALL_MAPS_COUNT 2

#endif /* !defined (ASDF_KEYMAP_DEFS_TEMPLATE_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
 P
