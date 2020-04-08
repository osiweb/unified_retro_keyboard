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

#if !defined(ASDF_KEYMAP_DEFS_TEST_H)
#define ASDF_KEYMAP_DEFS_TEST_H

#define ASDF_TEST_NUM_ROWS 9
#define ASDF_TEST_NUM_COLS 8

// The first value in each row serves two purposes:
//
// 1) Indicate a valid row of codes if the value is nonzero.
// 2) Indicate the physical row number corresponding to the keymap row.
//
// Multiple keymaps may be combined, some of which use more rows than other
// keymaps. The keymap with the most rows determines how many rows are allocated
// for each keymap. Since each keymap only initializes the rows it uses, then
// the shorter keymaps may have multiple uninitialized rows that should not be
// scanned. The C99 standard guarantees that all elements no explicitly
// initialized shall be initialized to 0 (C99 Standard 6.7.8.21). Therefore,
// keymap rows starting with a 0 are not valid and are not scanned.
//
// Some hardware may contain blank physical rows To avoid having unused empty
// rows, the first column of each row indicates the physical row. For example, 8
// rows of switches (0-7), and a bank of DIP switches on row 15. In this case,
// only 9 rows need be allocated.


#define PLAIN_MATRIX_1 RESERVED_1
#define CAPS_MATRIX_1 RESERVED_2
#define SHIFT_MATRIX_1 RESERVED_3
#define CTRL_MATRIX_1 RESERVED_4

#define ASDF_LAST_ROW (ASDF_NUM_ROWS - 1)
#define ASDF_TEST_MAP_DIP_SWITCHES                                                                 \
  [ASDF_LAST_ROW] = { ACTION_MAPSEL_0, ACTION_MAPSEL_1, ACTION_MAPSEL_2, ACTION_MAPSEL_3 }

#define ASDF_TEST_PLAIN_MAP                                                                        \
  {                                                                                                \
    { PLAIN_MATRIX_1, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,                                  \
      ACTION_CAPS,    ASCII_ESC,    ACTION_CTRL,  ASCII_BACKSLASH },                               \
      { ACTION_NOTHING, 'p', ';', '/', ASCII_SPACE, 'z', 'a', 'q' },                               \
      { ACTION_NOTHING, ASCII_COMMA, 'm', 'n', 'b', 'v', 'c', 'x' },                                 \
      { ACTION_NOTHING, 'k', 'j', 'h', 'g', 'f', 'd', 's' },                                       \
      { ACTION_NOTHING, 'i', 'u', 'y', 't', 'r', 'e', 'w' },                                       \
      /**/ { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR, ASCII_LF, 'o',            \
             'l',           ASCII_PERIOD },                                                        \
      { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', '0', '9', '8' },      \
      { ACTION_NOTHING, '7', '6', '5', '4', '3', '2', '1' }, ASDF_TEST_MAP_DIP_SWITCHES            \
  }

#define ASDF_TEST_CAPS_MAP                                                                         \
  {                                                                                                \
    { CAPS_MATRIX_1,  ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,                                  \
      ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  ASCII_BACKSLASH },                               \
      { ACTION_NOTHING, 'P', ';', '/', ASCII_SPACE, 'Z', 'A', 'Q' },                               \
      { ACTION_NOTHING, ASCII_COMMA, 'M', 'N', 'B', 'V', 'C', 'X' },                                 \
      { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },                                       \
      { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },                                       \
      /**/ { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR, ASCII_LF, 'O',            \
             'L',           ASCII_PERIOD },                                                        \
      { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', '0', '9', '8' },      \
      { ACTION_NOTHING, '7', '6', '5', '4', '3', '2', '1' }, ASDF_TEST_MAP_DIP_SWITCHES            \
  }

#define ASDF_TEST_SHIFT_MAP                                                                        \
  {                                                                                                \
                                                                                                   \
    { SHIFT_MATRIX_1, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,                                  \
      ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  ASCII_VERT_BAR },                                \
      { ACTION_NOTHING, 'P', '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },                               \
      { ACTION_NOTHING, '>', 'M', 'N', 'B', 'V', 'C', 'X' },                                         \
      { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },                                       \
      { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },                                       \
      { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR, ASCII_LF, 'O', 'L', '<' },     \
      { ASCII_TILDE, ASCII_RT_CURLY_BRACE, ASCII_LT_CURLY_BRACE, '=', '*',                         \
        '0',         ASCII_RT_PAREN,       ASCII_LT_PAREN },                                       \
      { ACTION_NOTHING, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' },         \
      ASDF_TEST_MAP_DIP_SWITCHES                                                                   \
  }


#define ASDF_TEST_CTRL_MAP                                                                         \
  {                                                                                                \
    { CTRL_MATRIX_1,  ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING,                                  \
      ACTION_NOTHING, ASCII_ESC,    ACTION_CTRL,  0x1c },                                          \
      { ACTION_NOTHING, ASCII_CTRL_P, ACTION_NOTHING, ACTION_NOTHING,                              \
        ASCII_SPACE,    ASCII_CTRL_Z, ASCII_CTRL_A,   ASCII_CTRL_Q },                              \
      { ACTION_NOTHING, ASCII_COMMA,  ASCII_CTRL_M, ASCII_CTRL_N,                                    \
        ASCII_CTRL_B, ASCII_CTRL_V, ASCII_CTRL_C, ASCII_CTRL_X },                                  \
      { ACTION_NOTHING, ASCII_CTRL_K, ASCII_CTRL_J, ASCII_CTRL_H,                                  \
        ASCII_CTRL_G,   ASCII_CTRL_F, ASCII_CTRL_D, ASCII_CTRL_S },                                \
      { ACTION_NOTHING, ASCII_CTRL_I, ASCII_CTRL_U, ASCII_CTRL_Y,                                  \
        ASCII_CTRL_T,   ASCII_CTRL_R, ASCII_CTRL_E, ASCII_CTRL_W },                                \
      { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR,                                \
        ASCII_LF,      ASCII_CTRL_O,   ASCII_CTRL_L,      ACTION_NOTHING },                        \
      { ACTION_NOTHING, 0x1d,        ASCII_ESC,   ACTION_NOTHING,                                  \
        ACTION_NOTHING, ACTION_FN_1, ACTION_FN_9, ACTION_FN_8 },                                   \
      { ACTION_NOTHING, ACTION_FN_7, ACTION_FN_6, ACTION_FN_5,                                     \
        ACTION_FN_4,    ACTION_FN_3, ACTION_FN_2, ACTION_FN_2 },                                   \
      ASDF_TEST_MAP_DIP_SWITCHES                                                                   \
  }


#define ASDF_TEST_DECLARATIONS                                                                     \
  static const FLASH keycode_matrix_t test_PLAIN_matrix = ASDF_TEST_PLAIN_MAP;                     \
  static const FLASH keycode_matrix_t test_SHIFT_matrix = ASDF_TEST_SHIFT_MAP;                     \
  static const FLASH keycode_matrix_t test_CAPS_matrix = ASDF_TEST_CAPS_MAP;                       \
  static const FLASH keycode_matrix_t test_CTRL_matrix = ASDF_TEST_CTRL_MAP;

#define ASDF_TEST_MAP_DEFS                                                                         \
  {                                                                                                \
    &test_PLAIN_matrix, &test_SHIFT_matrix, &test_CAPS_matrix, &test_CTRL_matrix                   \
  }

#define ASDF_TEST_CAPS_MAP_DEFS                                                                    \
  {                                                                                                \
    &test_CAPS_matrix, &test_SHIFT_matrix, &test_CAPS_matrix, &test_CTRL_matrix                    \
  }

#define ASDF_TEST_KEYMAPS ASDF_TEST_MAP_DEFS, ASDF_TEST_CAPS_MAP_DEFS

#define ASDF_TEST_KEYMAPS_COUNT 2
#define ASDF_TEST_PLAIN_MAP_INDEX ASDF_TEST_BASE + 0
#define ASDF_TEST_CAPS_MAP_INDEX ASDF_TEST_BASE + 1

#define SINGLE_TESTS_KEYMAP ASDF_TEST_PLAIN_MAP_INDEX
#define DOUBLE_ASSIGN_TEST_KEYMAP ASDF_TEST_PLAIN_MAP_INDEX

#define TRIPLE_TESTS_KEYMAP ASDF_TEST_CAPS_MAP_INDEX

#define ASDF_TEST_KEYMAP_INITIALIZER_LENGTH 5
#define ASDF_TEST_KEYMAP_INITIALIZER_1                                                             \
  {                                                                                                \
    {                                                                                              \
      /* Single assignment */                                                                      \
      .virtual_device = VOUT1,                                                                     \
      .physical_device = PHYSICAL_OUT1,                                                                    \
      .function = V_NOFUNC,                                                                        \
      .initial_value = 0,                                                                          \
    },                                                                                             \
      {                                                                                            \
        /* single toggle */                                                                        \
        .virtual_device = VOUT2,                                                                   \
        .physical_device = PHYSICAL_OUT2,                                                                  \
        .function = V_TOGGLE,                                                                      \
        .initial_value = 0,                                                                        \
      },                                                                                           \
      {                                                                                            \
        /* single pulse */                                                                         \
        .virtual_device = VOUT3,                                                                   \
        .physical_device = PHYSICAL_OUT3,                                                                  \
        .function = V_PULSE_SHORT,                                                                       \
        .initial_value = 0,                                                                        \
      },                                                                                           \
      { /* first of double assignment attempt */                                                   \
        .virtual_device = VOUT4,                                                                   \
        .physical_device = PHYSICAL_LED1,                                                                  \
        .initial_value = 0                                                                         \
      },                                                                                           \
    { /* second of double assignment attempt */                                                    \
      .virtual_device = VOUT5, .physical_device = PHYSICAL_LED1, .initial_value = 1                        \
    }                                                                                              \
  }

#define ASDF_TEST_KEYMAP_INITIALIZER_2                                                             \
  {                                                                                                \
    {                                                                                              \
      /* Triple assignment */                                                                      \
      .virtual_device = VOUT1,                                                                     \
      .physical_device = PHYSICAL_OUT1,                                                                    \
      .function = V_TOGGLE,                                                                        \
      .initial_value = 0,                                                                          \
    },                                                                                             \
      {                                                                                            \
        .virtual_device = VOUT1,                                                                   \
        .physical_device = PHYSICAL_OUT2,                                                                  \
        .function = V_TOGGLE,                                                                      \
        .initial_value = 1,                                                                        \
      },                                                                                           \
    {                                                                                              \
      .virtual_device = VOUT1, .physical_device = PHYSICAL_OUT3, .function = V_TOGGLE, .initial_value = 0, \
    }                                                                                              \
  }

#define ASDF_TEST_KEYMAP_INITIALIZER ASDF_TEST_KEYMAP_INITIALIZER_1, ASDF_TEST_KEYMAP_INITIALIZER_2

// The following preprocessor "code" permits various keymaps to be created and
// included without generating a lot of complicating code dependencies. The use
// of macros in this way is a bit ugly, I realize, and stretches the intention
// of the C preprocessor. The C preprocessor is used to store a bit of state to
// keep track of the number and ordering of the keymaps as they are added, and
// to keep track of the array sizes to be allocated at compile time.


#if !defined(ASDF_NUM_ROWS) || (ASDF_NUM_ROWS < ASDF_TEST_NUM_ROWS)
#undef ASDF_NUM_ROWS
#define ASDF_NUM_ROWS ASDF_TEST_NUM_ROWS
#endif

#if !defined(ASDF_NUM_COLS) || (ASDF_NUM_COLS < ASDF_TEST_NUM_COLS)
#undef ASDF_NUM_COLS
#define ASDF_NUM_COLS ASDF_TEST_NUM_COLS
#endif

#if !defined(ASDF_KEYMAP_INITIALIZER_LENGTH)                                                       \
  || (ASDF_KEYMAP_INITIALIZER_LENGTH < ASDF_TEST_KEYMAP_INITIALIZER_LENGTH)
#undef ASDF_KEYMAP_INITIALIZER_LENGTH
#define ASDF_KEYMAP_INITIALIZER_LENGTH ASDF_TEST_KEYMAP_INITIALIZER_LENGTH
#endif

#endif /* !defined (ASDF_KEYMAP_DEFS_TEST_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
