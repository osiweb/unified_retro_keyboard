// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
//  Unfified Keyboard Project
//  ASDF keyboard firmware
//
//  test_keymapdefs.c
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


#include "test_keymapdefs.h"

#define PLAIN_MATRIX_1 RESERVED_1
#define CAPS_MATRIX_1 RESERVED_2
#define SHIFT_MATRIX_1 RESERVED_3
#define CTRL_MATRIX_1 RESERVED_4

#define ASDF_TEST_PLAIN_MAP_INDEX 0
#define ASDF_TEST_CAPS_MAP_INDEX 1

#define SINGLE_TESTS_KEYMAP ASDF_TEST_PLAIN_MAP_INDEX
#define DOUBLE_ASSIGN_TEST_KEYMAP ASDF_TEST_PLAIN_MAP_INDEX
#define TRIPLE_TESTS_KEYMAP ASDF_TEST_CAPS_MAP_INDEX

#define ASDF_TEST_KEYMAP_INITIALIZER_LENGTH 5

#define ASDF_TEST_MAP_DIP_SWITCHES                                      \
  [ASDF_LAST_ROW] = { ACTION_MAPSEL_0, ACTION_MAPSEL_1, ACTION_MAPSEL_2, ACTION_MAPSEL_3 }


static const FLASH keycode_matrix_t test_PLAIN_matrix = {
  { PLAIN_MATRIX_1, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING, ACTION_CAPS, ASCII_ESC, ACTION_CTRL,
    ASCII_BACKSLASH },
  { ACTION_NOTHING, 'p', ';', '/', ASCII_SPACE, 'z', 'a', 'q' },
  { ACTION_NOTHING, ASCII_COMMA, 'm', 'n', 'b', 'v', 'c', 'x' },
  { ACTION_NOTHING, 'k', 'j', 'h', 'g', 'f', 'd', 's' },
  { ACTION_NOTHING, 'i', 'u', 'y', 't', 'r', 'e', 'w' },
  { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR, ASCII_LF, 'o', 'l',
    ASCII_PERIOD },
  { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', '0', '9', '8' },
  { ACTION_NOTHING, '7', '6', '5', '4', '3', '2', '1' },
  ASDF_TEST_MAP_DIP_SWITCHES,
};

static const FLASH keycode_matrix_t test_CAPS_matrix = {
  { CAPS_MATRIX_1, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING, ACTION_NOTHING, ASCII_ESC,
    ACTION_CTRL, ASCII_BACKSLASH },
  { ACTION_NOTHING, 'P', ';', '/', ASCII_SPACE, 'Z', 'A', 'Q' },
  { ACTION_NOTHING, ASCII_COMMA, 'M', 'N', 'B', 'V', 'C', 'X' },
  { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },
  { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },
  { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR, ASCII_LF, 'O', 'L',
    ASCII_PERIOD },
  { ASCII_TILDE, ASCII_RT_SQUARE_BRACE, ASCII_LT_SQUARE_BRACE, '-', ':', '0', '9', '8' },
  { ACTION_NOTHING, '7', '6', '5', '4', '3', '2', '1' },
  ASDF_TEST_MAP_DIP_SWITCHES
};


static const FLASH keycode_matrix_t test_SHIFT_matrix = {
  { SHIFT_MATRIX_1, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING, ACTION_NOTHING, ASCII_ESC,
    ACTION_CTRL, ASCII_VERT_BAR },
  { ACTION_NOTHING, 'P', '+', '?', ASCII_SPACE, 'Z', 'A', 'Q' },
  { ACTION_NOTHING, '>', 'M', 'N', 'B', 'V', 'C', 'X' },
  { ACTION_NOTHING, 'K', 'J', 'H', 'G', 'F', 'D', 'S' },
  { ACTION_NOTHING, 'I', 'U', 'Y', 'T', 'R', 'E', 'W' },
  { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR, ASCII_LF, 'O', 'L', '<' },
  { ASCII_TILDE, ASCII_RT_CURLY_BRACE, ASCII_LT_CURLY_BRACE, '=', '*', '0', ASCII_RT_PAREN,
    ASCII_LT_PAREN },
  { ACTION_NOTHING, ASCII_SINGLE_QUOTE, '&', '%', '$', '#', ASCII_DOUBLE_QUOTE, '!' },
  ASDF_TEST_MAP_DIP_SWITCHES
};

static const FLASH keycode_matrix_t test_CTRL_matrix = {
  { CTRL_MATRIX_1, ACTION_SHIFT, ACTION_SHIFT, ACTION_NOTHING, ACTION_NOTHING, ASCII_ESC,
    ACTION_CTRL, 0x1c },
  { ACTION_NOTHING, ASCII_CTRL_P, ACTION_NOTHING, ACTION_NOTHING, ASCII_SPACE, ASCII_CTRL_Z,
    ASCII_CTRL_A, ASCII_CTRL_Q },
  { ACTION_NOTHING, ASCII_COMMA, ASCII_CTRL_M, ASCII_CTRL_N, ASCII_CTRL_B, ASCII_CTRL_V,
    ASCII_CTRL_C, ASCII_CTRL_X },
  { ACTION_NOTHING, ASCII_CTRL_K, ASCII_CTRL_J, ASCII_CTRL_H, ASCII_CTRL_G, ASCII_CTRL_F,
    ASCII_CTRL_D, ASCII_CTRL_S },
  { ACTION_NOTHING, ASCII_CTRL_I, ASCII_CTRL_U, ASCII_CTRL_Y, ASCII_CTRL_T, ASCII_CTRL_R,
    ASCII_CTRL_E, ASCII_CTRL_W },
  { ACTION_REPEAT, ACTION_HERE_IS, ACTION_SHIFTLOCK_ON, ASCII_CR, ASCII_LF, ASCII_CTRL_O,
    ASCII_CTRL_L, ACTION_NOTHING },
  { ACTION_NOTHING, 0x1d, ASCII_ESC, ACTION_NOTHING, ACTION_NOTHING, ACTION_FN_1, ACTION_FN_9,
    ACTION_FN_8 },
  { ACTION_NOTHING, ACTION_FN_7, ACTION_FN_6, ACTION_FN_5, ACTION_FN_4, ACTION_FN_3, ACTION_FN_2,
    ACTION_FN_2 },
  ASDF_TEST_MAP_DIP_SWITCHES
};


static void build_test_map_matrices(void)
{
  asdf_keymap_add_keymap(&test_PLAIN_matrix, MOD_PLAIN_MAP);
  asdf_keymap_add_keymap(&test_SHIFT_matrix, MOD_SHIFT_MAP);
  asdf_keymap_add_keymap(&test_CAPS_matrix, MOD_CAPS_MAP); 
  asdf_keymap_add_keymap(&test_CTRL_matrix, MOD_CTRL_MAP);
}

static void build_test_caps_map_matrices(void)
{
  asdf_keymap_add_keymap(&test_CAPS_matrix, MOD_PLAIN_MAP);
  asdf_keymap_add_keymap(&test_SHIFT_matrix, MOD_SHIFT_MAP);
  asdf_keymap_add_keymap(&test_CAPS_matrix, MOD_CAPS_MAP); 
  asdf_keymap_add_keymap(&test_CTRL_matrix, MOD_CTRL_MAP);
}

static void build_test_map_virtual_init(void)
{
  /* Single assignment */                                           \
  asdf_keymap_add_virtual_device(VOUT1, PHYSICAL_OUT1, V_NOFUNC, 0);
  /* single toggle */                                                                        \
  asdf_keymap_add_virtual_device(VOUT2, PHYSICAL_OUT2, V_TOGGLE, 0);
  /* single pulse */
  asdf_keymap_add_virtual_device(VOUT3, PHYSICAL_OUT3, V_PULSE_SHORT, 0);
  /* first of double assignment attempt */
  asdf_keymap_add_virtual_device(VOUT4, PHYSICAL_LED1, V_NOFUNC, 0);
  /* second of double assignment attempt */
  asdf_keymap_add_virtual_device(VOUT5, PHYSICAL_LED1, V_NOFUNC, 1);
}

static void build_test_caps__map_virtual_init(void)
{
  /* Triple assignment */
  asdf_keymap_add_virtual_device(VOUT1, PHYSICAL_OUT1, V_TOGGLE, 0);
  asdf_keymap_add_virtual_device(VOUT1, PHYSICAL_OUT2, V_TOGGLE, 1);
  asdf_keymap_add_virtual_device(VOUT1, PHYSICAL_OUT3, V_TOGGLE, 0);
}

static void build_test_map_hooks(void)
{
  asdf_keymap_add_hook(ASDF_HOOK_KEYMAP_SETUP, &test_hook_1);
  asdf_keymap_add_hook(ASDF_HOOK_KEYMAP_SETUP, &test_hook_2);
}

static void build_test_caps_map_hooks(void)
{
  asdf_keymap_add_hook(ASDF_HOOK_KEYMAP_SETUP, &test_hook_3);
  asdf_keymap_add_hook(ASDF_HOOK_KEYMAP_SETUP, &test_hook_4);
}

void build_test_keymap(void)
{
  asdf_keymaps_build_keymap(ASDF_TEST_PLAIN_MAP_INDEX);
  build_test_map_matrices();
  build_test_map1_virtual_init();
  build_test_map1_hooks();

  asdf_keymaps_build_keymap(ASDF_TEST_CAPS_MAP_INDEX);
  build_test_caps_map_matrices();
  build_test_caps__map_virtual_init();
  build_test_caps_map_hooks();
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
