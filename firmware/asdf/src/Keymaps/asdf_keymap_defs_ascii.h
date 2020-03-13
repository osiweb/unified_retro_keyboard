// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymaps_ascii.h 
//
// Ascii keymaps
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


// To use this ascii for a new keymap, edit the keymaps definitions as
// desired. The keymaps are organized from row 0, counting upward, and each row
// includes the columns from 0-NUM_COLS.
//

#if !defined(ASDF_KEYMAP_DEFS_ASCII_H)
#define ASDF_KEYMAP_DEFS_ASCII_H

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#define ASDF_ASCII_NUM_ROWS 16 // DIP switches are row 15.
#define ASDF_ASCII_NUM_COLS 8

#define ACTION_BREAK ACTION_NOTHING

#define VIRTUAL_RESET VOUT1
#define RESET_OUTPUT PHYSICAL_OUT3_OC
#define RESET_ACTIVE_VALUE 0

#define VIRTUAL_CLR_SCR VOUT2
#define CLR_SCR_OUT PHYSICAL_OUT1
#define CLR_SCR_ACTIVE_VALUE 1

#define VIRTUAL_POWER_LED VLED1
#define POWER_LED PHYSICAL_LED1
#define POWER_LED_INIT_VALUE 1

#define CAPS_LED PHYSICAL_LED3
#define CAPS_LED_INIT_VALUE 0



#define ASDF_ASCII_KEYMAP_INITIALIZER_LENGTH 4

#define ASDF_ASCII_PLAIN_KEYMAP_INITIALIZER                             \
  {                                                                     \
   { .virtual_device = VIRTUAL_POWER_LED,                               \
       .physical_device = POWER_LED,                                        \
     .initial_value = POWER_LED_INIT_VALUE },                           \
   { .virtual_device = VCAPS_LED,                                       \
     .physical_device = CAPS_LED,                                           \
     .initial_value = CAPS_LED_INIT_VALUE },                            \
   { .virtual_device = VIRTUAL_RESET,                                   \
       .physical_device = RESET_OUTPUT,                                     \
     .function = V_PULSE,                                               \
     .initial_value = !RESET_ACTIVE_VALUE },                            \
   { .virtual_device = VIRTUAL_CLR_SCR,                                 \
    .physical_device = CLR_SCR_OUT,                                         \
    .function = V_PULSE,                                                \
       .initial_value = !CLR_SCR_ACTIVE_VALUE },                        \
  }

// For the CAPS map, no LED is mapped to the CapsLock virtual LED, since
// Capslock has no observable effect. The LED on the CAPSLOCK key is mapped to
// an unused LED output, initialized to OFF, to ensure the LED is dark.
#define ASDF_ASCII_CAPS_KEYMAP_INITIALIZER                              \
  {                                                                     \
   { .virtual_device = VIRTUAL_POWER_LED,                               \
     .physical_device = POWER_LED,                                          \
     .initial_value = POWER_LED_INIT_VALUE },                           \
   { .virtual_device = VLED1,                                       \
     .physical_device = CAPS_LED,                                       \
     .initial_value = CAPS_LED_INIT_VALUE },                            \
   { .virtual_device = VIRTUAL_RESET,                                   \
     .physical_device = RESET_OUTPUT,                                       \
     .function = V_PULSE,                                               \
     .initial_value = !RESET_ACTIVE_VALUE },                            \
   { .virtual_device = VIRTUAL_CLR_SCR,                                 \
    .physical_device = CLR_SCR_OUT,                                         \
    .function = V_PULSE,                                                \
     .initial_value = !CLR_SCR_ACTIVE_VALUE },                          \
  }


#define ASDF_ASCII_KEYMAP_INITIALIZER ASDF_ASCII_PLAIN_KEYMAP_INITIALIZER, ASDF_ASCII_CAPS_KEYMAP_INITIALIZER


// Key Matrix for combination of ASCII controller (ATMega328P version) and Classic ASCII matrix
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


#define ASDF_ASCII_DIP_SWITCHES [ASDF_NUM_ROWS - 1] = { ACTION_MAPSEL_0, ACTION_MAPSEL_1, ACTION_MAPSEL_2, ACTION_MAPSEL_3 }

#define ASDF_ASCII_PLAIN_MAP                                                                       \
  {                                                                     \
   [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,  \
           ASCII_ESC, ASCII_TAB,    ACTION_CTRL,  ASCII_BACKSLASH }, \
   [1] = { ASCII_DEL, 'p', ';', '/', ASCII_SPACE, 'z', 'a', 'q' },      \
   [2] = { ACTION_BREAK, ASCII_COMMA, 'm', 'n', 'b', 'v', 'c', 'x' },   \
   [3] = { ACTION_NOTHING, 'k', 'j', 'h', 'g', 'f', 'd', 's' },         \
   [4] = { ACTION_CLEAR, 'i', 'u', 'y', 't', 'r', 'e', 'w' },           \
   [5] = { ACTION_NOTHING, ACTION_REPEAT, ACTION_CAPS, ASCII_CR, ASCII_LF, 'o', 'l', ASCII_PERIOD }, \
   [6] = { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', ASCII_ZERO, '9', '8' }, \
   [7] = { ASCII_AT, '7', '6', '5', '4', '3', '2', '1' }, \
   ASDF_ASCII_DIP_SWITCHES                   \
  }

#define ASDF_ASCII_CAPS_MAP                                                                          \
  {                                                                     \
    [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING, \
            ASCII_ESC, ASCII_TAB,    ACTION_CTRL,  ASCII_BACKSLASH }, \
    [1] = { ASCII_DEL, 'P', ';', '/', ASCII_SPACE, 'Z', 'A', 'Q' },     \
    [2] = { ACTION_BREAK, ASCII_COMMA, 'M', 'N', 'B', 'V', 'C', 'X' },  \
    [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },        \
    [4] = { ACTION_CLEAR, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },          \
    [5] = { ACTION_NOTHING, ACTION_REPEAT, ACTION_CAPS, ASCII_CR, ASCII_LF, 'O', 'L', ASCII_PERIOD }, \
    [6] = { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', ASCII_ZERO, '9', '8' }, \
    [7] = { ASCII_AT, '7', '6', '5', '4', '3', '2', '1' },              \
    ASDF_ASCII_DIP_SWITCHES                                          \
  }

#define ASDF_ASCII_SHIFT_MAP                                                                       \
  {                                                                     \
   [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,        \
     ASCII_ESC, ASCII_TAB,    ACTION_CTRL,  ASCII_VERT_BAR },      \
   [1] = { ASCII_DEL, 'P', '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },            \
   [2] = { ACTION_BREAK, '<', 'M', 'N', 'B', 'V', 'C', 'X' },                                         \
   [3] = { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },               \
   [4] = { ACTION_CLEAR, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },                                         \
   [5] = { ACTION_NOTHING, ACTION_REPEAT, ACTION_CAPS, ASCII_CR, ASCII_LF, 'O', 'L', '>' },           \
   [6] = { ASCII_TILDE, ASCII_RT_CURLY_BRACE, ASCII_LT_CURLY_BRACE, '=', \
           '*',         ASCII_ZERO,           ASCII_RT_PAREN,       ASCII_LT_PAREN }, \
   [7] = { ASCII_GRAVE_ACCENT, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' }, \
   ASDF_ASCII_DIP_SWITCHES                                           \
  }

#define ASDF_ASCII_CTRL_MAP                                                                        \
  {                                                                     \
   [0] = { ACTION_NOTHING, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,                                  \
      ASCII_ESC, ASCII_TAB,    ACTION_CTRL,  0x1c },                                          \
   [1] = { ACTION_NOTHING, ASCII_CTRL_P, ACTION_NOTHING, ACTION_NOTHING,      \
        ASCII_SPACE,    ASCII_CTRL_Z, ASCII_CTRL_A,   ASCII_CTRL_Q },                              \
   [2] = { ACTION_RESET, ASCII_COMMA, ASCII_CTRL_M, ASCII_CTRL_N,       \
           ASCII_CTRL_B, ASCII_CTRL_V, ASCII_CTRL_C, ASCII_CTRL_X },    \
   [3] = { ACTION_NOTHING, ASCII_CTRL_K, ASCII_CTRL_J, ASCII_CTRL_H, \
           ASCII_CTRL_G, ASCII_CTRL_F, ASCII_CTRL_D, ASCII_CTRL_S }, \
   [4] = { ACTION_CLEAR, ASCII_CTRL_I, ASCII_CTRL_U, ASCII_CTRL_Y,      \
        ASCII_CTRL_T, ASCII_CTRL_R, ASCII_CTRL_E, ASCII_CTRL_W },                                  \
   [5] = { ACTION_NOTHING, ACTION_REPEAT, ACTION_CAPS,  ASCII_CR,       \
        ASCII_LF,      ASCII_CTRL_O,   ASCII_CTRL_L, ACTION_NOTHING },                             \
   [6] = { ACTION_NOTHING, 0x1d,         ASCII_ESC,   ACTION_NOTHING,   \
        ACTION_NOTHING, ACTION_FN_10, ACTION_FN_9, ACTION_FN_8 },                                  \
   [7] = { ASCII_NULL, ACTION_FN_7, ACTION_FN_6, ACTION_FN_5, \
            ACTION_FN_4, ACTION_FN_3, ACTION_FN_2, ACTION_FN_1 }, \
   ASDF_ASCII_DIP_SWITCHES                                        \
  }

#define ASDF_ASCII_MAP_DECLARATIONS                                                                \
  static const FLASH keycode_matrix_t ascii_plain_matrix = ASDF_ASCII_PLAIN_MAP;                        \
  static const FLASH keycode_matrix_t ascii_shift_matrix = ASDF_ASCII_SHIFT_MAP;                        \
  static const FLASH keycode_matrix_t ascii_caps_matrix = ASDF_ASCII_CAPS_MAP;                          \
  static const FLASH keycode_matrix_t ascii_ctrl_matrix = ASDF_ASCII_CTRL_MAP;


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

#define ASDF_ASCII_PLAIN_MAP_DEFS                                    \
  {                                                                     \
   [MOD_PLAIN_MAP] = &ascii_plain_matrix,                                        \
   [MOD_SHIFT_MAP] = &ascii_shift_matrix,                                        \
   [MOD_CAPS_MAP] = &ascii_caps_matrix,                                         \
   [MOD_CTRL_MAP] = &ascii_ctrl_matrix                                          \
  }

#define ASDF_ASCII_CAPS_MAP_DEFS            \
  {                                             \
   [MOD_PLAIN_MAP] = &ascii_caps_matrix,    \
   [MOD_SHIFT_MAP] = &ascii_shift_matrix,    \
   [MOD_CAPS_MAP] = &ascii_caps_matrix,      \
   [MOD_CTRL_MAP] = &ascii_ctrl_matrix       \
  }

#define ASDF_ASCII_ALL_MAPS ASDF_ASCII_PLAIN_MAP_DEFS, ASDF_ASCII_CAPS_MAP_DEFS

#define ASDF_ASCII_ALL_MAPS_COUNT 2

#if !defined(ASDF_NUM_ROWS) || (ASDF_NUM_ROWS < ASDF_ASCII_NUM_ROWS)
#undef ASDF_NUM_ROWS
#define ASDF_NUM_ROWS ASDF_ASCII_NUM_ROWS
#endif

#if !defined(ASDF_NUM_COLS) || (ASDF_NUM_COLS < ASDF_ASCII_NUM_COLS)
#undef ASDF_NUM_COLS
#define ASDF_NUM_COLS ASDF_ASCII_NUM_COLS
#endif

#if !defined(ASDF_KEYMAP_INITIALIZER_LENGTH) || (ASDF_KEYMAP_INITIALIZER_LENGTH < ASDF_ASCII_KEYMAP_INITIALIZER_LENGTH)
#undef ASDF_KEYMAP_INITIALIZER_LENGTH
#define ASDF_KEYMAP_INITIALIZER_LENGTH ASDF_ASCII_KEYMAP_INITIALIZER_LENGTH
#endif

#endif /* !defined (ASDF_KEYMAP_DEFS_ASCII_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

