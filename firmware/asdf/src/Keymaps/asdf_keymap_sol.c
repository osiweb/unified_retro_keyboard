// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_sol.c
//
// Implements the keymap definition and setup routines for the sol-20 keymap
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
#include "asdf_keymap_sol.h"
#include "asdf.h"
#include "asdf_ascii.h"
#include "asdf_modifiers.h"
#include "asdf_keymaps.h"
#include "asdf_print.h"


#define SOL_PRINT_DELAY 40 // msec
#define SOL_ID_MESSAGE_HOOK ASDF_HOOK_USER_10

static const FLASH asdf_keycode_t sol_plain_map[ASDF_SOL_NUM_ROWS][ASDF_SOL_NUM_COLS] = {
  [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, 'a', 's', 'd', 'f', 'g', 'h' },
  [1] = { 'j', 'k', 'l', ';', ':', ASCII_DEL, ACTION_REPEAT, ACTION_CTRL },
  [2] = { ACTION_CAPS, ACTION_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n' },
  [3] = { 'm', ASCII_COMMA, ASCII_PERIOD, '/', ACTION_SHIFT, SOL_ASCII_MODE_SELECT, ACTION_NOTHING,
          ACTION_NOTHING },
  [4] = { ASCII_ESC, '1', '2', '3', '4', '5', '6', '7' },
  [5] = { '8', '9', ASCII_ZERO, '-', '^', ASCII_LT_SQUARE_BRACE, ASCII_BACKSLASH,
          ASCII_RT_SQUARE_BRACE },
  [6] = { SOL_KBD_BREAK_ACTION, ASCII_TAB, 'q', 'w', 'e', 'r', 't', 'y' },
  [7] = { 'u', 'i', 'o', 'p', ASCII_AT, ASCII_CR, ASCII_LF, SOL_ASCII_LOAD },
  [9] = { SOL_KBD_LOCAL_ACTION, SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW, ASCII_SPACE,
          SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW, SOL_ASCII_HOME, SOL_ASCII_CLEAR },
  [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING },
  [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING },
  [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING,
           ACTION_NOTHING },
  ASDF_SOL_DIP_SWITCHES,
};

static const FLASH asdf_keycode_t sol_caps_map[ASDF_SOL_NUM_ROWS][ASDF_SOL_NUM_COLS] = {
  [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, 'A', 'S', 'D', 'F', 'G', 'H' },
  [1] = { 'J', 'K', 'L', ';', ':', ASCII_DEL, ACTION_REPEAT, ACTION_CTRL },
  [2] = { ACTION_CAPS, ACTION_SHIFT, 'Z', 'X', 'C', 'V', 'B', 'N' },
  [3] = { 'M', ASCII_COMMA, ASCII_PERIOD, '/', ACTION_SHIFT, SOL_ASCII_MODE_SELECT, ACTION_NOTHING,
          ACTION_NOTHING },
  [4] = { ASCII_ESC, '1', '2', '3', '4', '5', '6', '7' }, /**/
  [5] = { '8', '9', ASCII_ZERO, '-', '^', ASCII_LT_SQUARE_BRACE, ASCII_BACKSLASH,
          ASCII_RT_SQUARE_BRACE },
  [6] = { SOL_KBD_BREAK_ACTION, ASCII_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y' },
  [7] = { 'U', 'I', 'O', 'P', ASCII_AT, ASCII_CR, ASCII_LF, SOL_ASCII_LOAD },
  [9] = { SOL_KBD_LOCAL_ACTION, SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW, ASCII_SPACE,
          SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW, SOL_ASCII_HOME, SOL_ASCII_CLEAR },
  [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING },
  [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING },
  [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING,
           ACTION_NOTHING },
  ASDF_SOL_DIP_SWITCHES,
};


static const FLASH asdf_keycode_t sol_shift_map[ASDF_SOL_NUM_ROWS][ASDF_SOL_NUM_COLS] = {
  [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, 'A', 'S', 'D', 'F', 'G', 'H' },
  [1] = { 'J', 'K', 'L', ';', ':', ASCII_UNDERSCORE, ACTION_REPEAT, ACTION_CTRL },
  [2] = { ACTION_CAPS, ACTION_SHIFT, 'Z', 'X', 'C', 'V', 'B', 'N' },
  [3] = { 'M', '<', '>', '?', ACTION_SHIFT, SOL_ASCII_MODE_SELECT, ACTION_NOTHING, ACTION_NOTHING },
  [4] = { ASCII_ESC, '!', ASCII_DOUBLE_QUOTE, '#', '$', '%', '&', ASCII_SINGLE_QUOTE },
  [5] = { ASCII_LT_PAREN, ASCII_RT_PAREN, ASCII_SPACE, '=', ASCII_TILDE, ASCII_LT_SQUARE_BRACE,
          ASCII_BACKSLASH, ASCII_RT_SQUARE_BRACE },
  [6] = { SOL_KBD_BREAK_ACTION, ASCII_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y' },
  [7] = { 'U', 'I', 'O', 'P', ASCII_GRAVE_ACCENT, ASCII_CR, ASCII_LF, SOL_ASCII_LOAD },
  [9] = { SOL_KBD_LOCAL_ACTION, SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW, ASCII_SPACE,
          SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW, SOL_ASCII_HOME, SOL_ASCII_CLEAR },
  [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING },
  [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING },
  [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING,
           ACTION_NOTHING },
  ASDF_SOL_DIP_SWITCHES,
};


static const FLASH asdf_keycode_t sol_ctrl_map[ASDF_SOL_NUM_ROWS][ASDF_SOL_NUM_COLS] = {
  [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, ASCII_CTRL_A, ASCII_CTRL_S, ASCII_CTRL_D,
          ASCII_CTRL_F, ASCII_CTRL_G, ASCII_CTRL_H },
  [1] = { ASCII_CTRL_J, ASCII_CTRL_K, ASCII_CTRL_L, ASCII_VT, ASCII_LF, ASCII_DEL,
          SOL_KBD_RESET_ACTION, ACTION_CTRL },
  [2] = { ACTION_CAPS, ACTION_SHIFT, ASCII_CTRL_Z, ASCII_CTRL_X, ASCII_CTRL_C, ASCII_CTRL_V,
          ASCII_CTRL_B, ASCII_CTRL_N },
  [3] = { ASCII_CTRL_M, ASCII_FF, ASCII_SO, ASCII_SI, ACTION_SHIFT, SOL_ASCII_MODE_SELECT,
          ACTION_NOTHING, ACTION_NOTHING },
  [4] = { ASCII_ESC, ASCII_SOH, ASCII_STX, ASCII_ETX, ASCII_EOT, ASCII_ENQ, ASCII_ACK, ASCII_BEL },
  [5] = { ASCII_BS, ASCII_TAB, ASCII_NULL, ASCII_CR, ASCII_RS, ASCII_ESC, ASCII_FS, ASCII_GS },
  [6] = { SOL_KBD_BREAK_ACTION, ASCII_TAB, ASCII_CTRL_Q, ASCII_CTRL_W, ASCII_CTRL_E, ASCII_CTRL_R,
          ASCII_CTRL_T, ASCII_CTRL_Y },
  [7] = { ASCII_CTRL_U, ASCII_CTRL_I, ASCII_CTRL_O, ASCII_CTRL_P, ASCII_NULL, ASCII_CR, ASCII_LF,
          SOL_ASCII_LOAD },
  [9] = { SOL_KBD_LOCAL_ACTION, SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW, ASCII_SPACE,
          SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW, SOL_ASCII_HOME, SOL_ASCII_CLEAR },
  [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING },
  [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING },
  [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING,
           ACTION_NOTHING },
  ASDF_SOL_DIP_SWITCHES,
};


// PROCEDURE: sol_add_map
// INPUTS: asdf_keycode_t (*matrix) - a SOL_NUM_ROWS x SOL_NUM_COLS matrix of keycodes for each physical row/column pair
//         modifier_index_t modifier index - the modifier state corresponding to the keycode matrix
// OUTPUTS: none
// DESCRIPTION: Passes the keycode matrix and modifier state through to
// asdf_keymaps_add_map(), along with the row/column dimensions.
//
// SIDE EFFECTS: the matrix is added to the keymap
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void sol_add_map(const asdf_keycode_t (*matrix)[ASDF_SOL_NUM_COLS],
                        modifier_index_t modifier_index)
{
  asdf_keymaps_add_map(&matrix[0][0], modifier_index, (uint8_t) ASDF_SOL_NUM_ROWS,
                       (uint8_t) ASDF_SOL_NUM_COLS);
}


static void sol_id_message(void)
{
  asdf_print("[Keybd: Sol-20]");
}

void setup_sol_keymap(void)
{
  sol_add_map(sol_plain_map, MOD_PLAIN_MAP);
  sol_add_map(sol_caps_map, MOD_CAPS_MAP);
  sol_add_map(sol_shift_map, MOD_SHIFT_MAP);
  sol_add_map(sol_ctrl_map, MOD_CTRL_MAP);

  asdf_set_print_delay(SOL_PRINT_DELAY);

  // Set up the ALL CAPS LED, default = off
  asdf_virtual_assign(VCAPS_LED, SOL_KBD_LED_UPPERCASE, V_NOFUNC, SOL_KBD_LED_OFF);

  // Set up the SHIFT LED, default = off
  asdf_virtual_assign(VSHIFT_LED, SOL_KBD_LED_SHIFTLOCK, V_NOFUNC, SOL_KBD_LED_OFF);

  // Set up the LOCAL LED and output, default LED=OFF, TTL output HIGH. Both LED
  // and TTL out are bound to the save virtual device.
  asdf_virtual_assign(SOL_KBD_VLOCAL, SOL_KBD_TTLOUT_LOCAL, V_TOGGLE, SOL_KBD_TTL_HIGH);
  asdf_virtual_assign(SOL_KBD_VLOCAL, SOL_KBD_LED_LOCAL, V_TOGGLE, SOL_KBD_LED_OFF);

  // Set up the RESET output, produce a short pulse when activated. Default output HIGH
  asdf_virtual_assign(SOL_KBD_VRESET, SOL_KBD_TTLOUT_RESET, V_PULSE_SHORT, SOL_KBD_TTL_HIGH);

  // Set up the BREAK output, produce a long pulse when activated, default output high
  asdf_virtual_assign(SOL_KBD_VBREAK, SOL_KBD_TTLOUT_BREAK, V_PULSE_LONG, SOL_KBD_TTL_HIGH);

  // Activate the ALL CAPS mode to emulate the original keyboard:
  asdf_modifier_capslock_activate();

  // Configure negative strobe
  asdf_arch_set_neg_strobe();

  asdf_hook_assign(SOL_ID_MESSAGE_HOOK, sol_id_message);
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
