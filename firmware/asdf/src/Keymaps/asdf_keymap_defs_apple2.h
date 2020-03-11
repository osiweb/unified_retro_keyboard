// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymaps_apple2.h 
//
// Apple 2 keymaps
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


// This file supplies the Apple 2 ASCII keyboard keymap.  Two variants are provided:
//
// 1) An Upper/Lowercase variant. This variant moves the @ and ^ symbols from
//    the P and N keys to the REPEAT key, since the P and N keys need to reserve
//    the shifted value for the uppercase characters. Also, the "Power" key
//    doubles as a caps-lock key.
//
// 2) A CAPS only keyboard, following the standard Apple II conventions and
//    layout, with ^ above the N key and @ above the P key, and a functioning
//    REPEAT key.
//
// For both variants, CTRL+RESET is required for a system reset.

#if !defined(ASDF_KEYMAP_DEFS_APPLE2_H)
#define ASDF_KEYMAP_DEFS_APPLE2_H

#include "../asdf_modifiers.h"

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#define ASDF_APPLE2_NUM_ROWS 16 // DIP switches are row 15.
#define ASDF_APPLE2_NUM_COLS 8

#define ASDF_ASCII_NUM_ROWS 16 // DIP switches are row 15.
#define ASDF_ASCII_NUM_COLS 8

#define ACTION_RESET ACTION_VOUT1
#define VIRTUAL_RESET VOUT1
#define RESET_OUTPUT VMAP_OUT3_OC
#define RESET_ACTIVE_VALUE 0

#define ACTION_CLEAR ACTION_VOUT2
#define VIRTUAL_CLR_SCR VOUT2
#define CLR_SCR_OUTPUT VMAP_OUT1
#define CLR_SCR_ACTIVE_VALUE 1

#define VIRTUAL_POWER_LED VLED1
#define POWER_LED VMAP_LED1
#define POWER_LED_INIT_VALUE 1

#define VIRTUAL_DISABLED_LED VLED2
#define DISABLED_LED VMAP_LED3
#define DISABLED_INIT_VALUE 0

#define ASDF_APPLE2_KEYMAP_INITIALIZER_LENGTH 4


// The PLAIN map uses the "power" button as a caps-lock, so map the CAPS LED to
// the power button LED.
#define ASDF_APPLE2_PLAIN_KEYMAP_INITIALIZER                            \
  {                                                                     \
   { .virtual_device = VCAPS_LED,                                       \
     .real_device = POWER_LED,                                          \
     .initial_value = 0 },                                              \
   { .virtual_device = VIRTUAL_DISABLED_LED,                            \
     .real_device = DISABLED_LED,                                       \
     .initial_value = 0 },                                              \
   { .virtual_device = VIRTUAL_RESET,                                   \
     .real_device = RESET_OUTPUT,                                       \
     .function = V_PULSE,                                               \
     .initial_value = !RESET_ACTIVE_VALUE },                            \
   { .virtual_device = VIRTUAL_CLR_SCR,                                 \
     .real_device = CLR_SCR_OUTPUT,                                     \
     .function = V_PULSE,                                               \
     .initial_value = !CLR_SCR_ACTIVE_VALUE }                           \
  }

// The ALL CAPS map is the classic Apple II/II+ map.
#define ASDF_APPLE2_CAPS_KEYMAP_INITIALIZER                             \
  {                                                                     \
   { .virtual_device = VIRTUAL_POWER_LED,                               \
     .real_device = POWER_LED,                                          \
     .initial_value = POWER_LED_INIT_VALUE },                           \
   { .virtual_device = VIRTUAL_DISABLED_LED,                            \
     .real_device = DISABLED_LED,                                       \
     .initial_value = 0 },                                              \
   { .virtual_device = VIRTUAL_RESET,                                   \
     .real_device = RESET_OUTPUT,                                       \
     .function = V_PULSE,                                               \
     .initial_value = !RESET_ACTIVE_VALUE },                            \
   { .virtual_device = VIRTUAL_CLR_SCR,                                 \
     .real_device = CLR_SCR_OUTPUT,                                     \
     .function = V_PULSE,                                               \
     .initial_value = !CLR_SCR_ACTIVE_VALUE }                           \
  }


#define ASDF_APPLE2_KEYMAP_INITIALIZER ASDF_APPLE2_PLAIN_KEYMAP_INITIALIZER, ASDF_APPLE2_CAPS_KEYMAP_INITIALIZER 


// TO ensure consistent DIP switch operation within the keymap, a
// ASDF_APPLE2_DIP_SWITCHES macro is defined. Keeping the ACTION_MAPSEL0-3
// definitions in positions 0-3 ensures consistent map selection among all
// keymaps.


#define ASDF_APPLE2_DIP_SWITCHES [ASDF_NUM_ROWS - 1] = { ACTION_MAPSEL_0, ACTION_MAPSEL_1, ACTION_MAPSEL_2, ACTION_MAPSEL_3 }

#define APPLE_LEFT_ARROW ASCII_CTRL_H
#define APPLE_RIGHT_ARROW ASCII_CTRL_U

#define ASDF_APPLE2_PLAIN_MAP                                                                       \
  {                                                                     \
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,  \
           ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW }, \
   [1] = { ASCII_DEL, 'p', ';', '/', ASCII_SPACE, 'z', 'a', 'q' },      \
   [2] = { ACTION_NOTHING, ASCII_COMMA, 'm', 'n', 'b', 'v', 'c', 'x' },   \
   [3] = { ACTION_NOTHING, 'k', 'j', 'h', 'g', 'f', 'd', 's' },         \
   [4] = { ACTION_NOTHING, 'i', 'u', 'y', 't', 'r', 'e', 'w' },           \
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, '^', 'o', 'l', ASCII_PERIOD }, \
   [6] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, '-', ':', ASCII_ZERO, '9', '8' }, \
   [7] = { APPLE_LEFT_ARROW, '7', '6', '5', '4', '3', '2', '1' }, \
   ASDF_APPLE2_DIP_SWITCHES                   \
  }

#define ASDF_APPLE2_SHIFT_MAP                                                                       \
  {                                                                     \
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,        \
     ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW },      \
   [1] = { ACTION_NOTHING, 'P', '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },            \
   [2] = { ACTION_NOTHING, '<', 'M', 'N', 'B', 'V', 'C', 'X' },                                         \
   [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },               \
   [4] = { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },                                         \
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, ASCII_AT, 'O', 'L', '>' },           \
   [6] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, '=', \
           '*',         ASCII_ZERO,           ASCII_RT_PAREN,       ASCII_LT_PAREN }, \
   [7] = { APPLE_LEFT_ARROW, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' }, \
   ASDF_APPLE2_DIP_SWITCHES                                           \
  }

#define ASDF_APPLE2_CAPS_MAP                                            \
  {                                                                     \
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,     \
            ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW }, \
    [1] = { ACTION_NOTHING, 'P', ';', '/', ASCII_SPACE, 'Z', 'A', 'Q' },     \
    [2] = { ACTION_NOTHING, ASCII_COMMA, 'M', 'N', 'B', 'V', 'C', 'X' },  \
    [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },        \
    [4] = { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },          \
    [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, ACTION_REPEAT, 'O', 'L', ASCII_PERIOD }, \
    [6] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, '-', ':', ASCII_ZERO, '9', '8' }, \
    [7] = { APPLE_LEFT_ARROW, '7', '6', '5', '4', '3', '2', '1' },              \
    ASDF_APPLE2_DIP_SWITCHES                                          \
  }


#define ASDF_APPLE2_SHIFT_CAPS_MAP                                                                       \
  {                                                                     \
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,        \
     ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW },      \
   [1] = { ACTION_NOTHING, ASCII_AT, '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },            \
   [2] = { ACTION_NOTHING, '<', 'M', '^', 'B', 'V', 'C', 'X' },                                         \
   [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },               \
   [4] = { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },                                         \
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ASCII_CR, ACTION_REPEAT, 'O', 'L', '>' },           \
   [6] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, '=', \
           '*',         ASCII_ZERO,           ASCII_RT_PAREN,       ASCII_LT_PAREN }, \
   [7] = { APPLE_LEFT_ARROW, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' }, \
   ASDF_APPLE2_DIP_SWITCHES                                           \
  }

#define ASDF_APPLE2_CTRL_MAP                                                                        \
  {                                                                     \
   [0] = { ACTION_CAPS, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,                                  \
           ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  APPLE_RIGHT_ARROW }, \
   [1] = { ACTION_NOTHING, ASCII_CTRL_P, ACTION_NOTHING, ACTION_NOTHING,      \
           ASCII_SPACE,    ASCII_CTRL_Z, ASCII_CTRL_A,   ASCII_CTRL_Q }, \
   [2] = { ACTION_NOTHING, ASCII_COMMA, ASCII_CTRL_M, ASCII_CTRL_N,       \
           ASCII_CTRL_B, ASCII_CTRL_V, ASCII_CTRL_C, ASCII_CTRL_X },    \
   [3] = { ACTION_NOTHING, ASCII_CTRL_K, ASCII_CTRL_J, ASCII_CTRL_H, \
           ASCII_CTRL_G, ASCII_CTRL_F, ASCII_CTRL_D, ASCII_CTRL_S }, \
   [4] = { ACTION_NOTHING, ASCII_CTRL_I, ASCII_CTRL_U, ASCII_CTRL_Y,      \
           ASCII_CTRL_T, ASCII_CTRL_R, ASCII_CTRL_E, ASCII_CTRL_W },    \
   [5] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING,  ASCII_CR,       \
           ACTION_REPEAT,      ASCII_CTRL_O,   ASCII_CTRL_L, ACTION_NOTHING }, \
   [6] = { ACTION_NOTHING, ACTION_NOTHING, ACTION_RESET,   ACTION_NOTHING,   \
           ACTION_NOTHING, ACTION_FN_10, ACTION_FN_9, ACTION_FN_8 },    \
   [7] = { APPLE_LEFT_ARROW, ACTION_FN_7, ACTION_FN_6, ACTION_FN_5, \
            ACTION_FN_4, ACTION_FN_3, ACTION_FN_2, ACTION_FN_1 }, \
   ASDF_APPLE2_DIP_SWITCHES                                        \
  }

#define ASDF_APPLE2_MAP_DECLARATIONS                                                                \
  static const FLASH keycode_matrix_t apple2_plain_matrix = ASDF_APPLE2_PLAIN_MAP;                        \
  static const FLASH keycode_matrix_t apple2_shift_matrix = ASDF_APPLE2_SHIFT_MAP;                        \
  static const FLASH keycode_matrix_t apple2_caps_matrix = ASDF_APPLE2_CAPS_MAP; \
  static const FLASH keycode_matrix_t apple2_caps_shift_matrix = ASDF_APPLE2_SHIFT_CAPS_MAP; \
  static const FLASH keycode_matrix_t apple2_ctrl_matrix = ASDF_APPLE2_CTRL_MAP;


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

#define ASDF_APPLE2_PLAIN_MAP_DEFS                                    \
  {                                                                     \
   [MOD_PLAIN_MAP] = &apple2_plain_matrix,                                        \
   [MOD_SHIFT_MAP] = &apple2_shift_matrix,                                        \
   [MOD_CAPS_MAP] = &apple2_caps_matrix,                                         \
   [MOD_CTRL_MAP] = &apple2_ctrl_matrix                                          \
  }

#define ASDF_APPLE2_CAPS_MAP_DEFS            \
  {                                             \
   [MOD_PLAIN_MAP] = &apple2_caps_matrix,    \
   [MOD_SHIFT_MAP] = &apple2_caps_shift_matrix,    \
   [MOD_CAPS_MAP] = &apple2_caps_matrix,      \
   [MOD_CTRL_MAP] = &apple2_ctrl_matrix       \
  }

#define ASDF_APPLE2_ALL_MAPS ASDF_APPLE2_PLAIN_MAP_DEFS, ASDF_APPLE2_CAPS_MAP_DEFS

#define ASDF_APPLE2_ALL_MAPS_COUNT 2

#if !defined(ASDF_NUM_ROWS) || (ASDF_NUM_ROWS < ASDF_APPLE2_NUM_ROWS)
#undef ASDF_NUM_ROWS
#define ASDF_NUM_ROWS ASDF_APPLE2_NUM_ROWS
#endif

#if !defined(ASDF_NUM_COLS) || (ASDF_NUM_COLS < ASDF_APPLE2_NUM_COLS)
#undef ASDF_NUM_COLS
#define ASDF_NUM_COLS ASDF_APPLE2_NUM_COLS
#endif

#if !defined(ASDF_KEYMAP_INITIALIZER_LENGTH) || (ASDF_KEYMAP_INITIALIZER_LENGTH < ASDF_APPLE2_KEYMAP_INITIALIZER_LENGTH)
#undef ASDF_KEYMAP_INITIALIZER_LENGTH
#define ASDF_KEYMAP_INITIALIZER_LENGTH ASDF_APPLE2_KEYMAP_INITIALIZER_LENGTH
#endif

#endif /* !defined (ASDF_KEYMAP_DEFS_APPLE2_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

