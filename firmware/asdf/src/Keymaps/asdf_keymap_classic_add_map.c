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
#include "asdf_ascii.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_classic.h"
#include "asdf_keymap_classic_add_map.h"
#include "asdf_keymap_defs_dipswitch.h"

// Key Matrix for combination of ASCII controller and Classic ASCII matrix
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

#define ASDF_CLASSIC_DIP_SWITCHES ASDF_KEYMAP_DIP_SWITCHES

typedef asdf_keycode_t classic_keycode_matrix_t[CLASSIC_NUM_ROWS][CLASSIC_NUM_COLS];



const FLASH classic_keycode_matrix_t classic_plain_matrix = {
[0][0] = {no_action, no_action, 0},
[0][1] = {asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0},
[0][2] = {asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0},
[0][3] = {no_action, no_action, 0},
[0][4] = {insert, no_action, ASCII_ESC},
[0][5] = {insert, no_action, ASCII_TAB},
[0][6] = {asdf_modifier_ctrl_activate, asdf_modifier_ctrl_deactivate, 0},
[0][7] = {insert, no_action, ASCII_BACKSLASH},

[1][0] = {insert, no_action, ASCII_DEL},
[1][1] = {insert, no_action, 'p'},
[1][2] = {insert, no_action, ';'},
[1][3] = {insert, no_action, '/'},
[1][4] = {insert, no_action, ASCII_SPACE},
[1][5] = {insert, no_action, 'z'},
[1][6] = {insert, no_action, 'a'},
[1][7] = {insert, no_action, 'q'},

[2][0] = {asdf_virtual_activate, no_action, CLASSIC_ACTION_BREAK},
[2][1] = {insert, no_action, ASCII_COMMA},
[2][2] = {insert, no_action, 'm'},
[2][3] = {insert, no_action, 'n'},
[2][4] = {insert, no_action, 'b'},
[2][5] = {insert, no_action, 'v'},
[2][6] = {insert, no_action, 'c'},
[2][7] = {insert, no_action, 'x'},

[3][0] = {no_action, no_action, 0},
[3][1] = {insert, no_action, 'k'},
[3][2] = {insert, no_action, 'j'},
[3][3] = {insert, no_action, 'h'},
[3][4] = {insert, no_action, 'g'},
[3][5] = {insert, no_action, 'f'},
[3][6] = {insert, no_action, 'd'},
[3][7] = {insert, no_action, 's'},

[4][0] = {no_action, no_action, 0},
[4][1] = {insert, no_action, 'i'},
[4][2] = {insert, no_action, 'u'},
[4][3] = {insert, no_action, 'y'},
[4][4] = {insert, no_action, 't'},
[4][5] = {insert, no_action, 'r'},
[4][6] = {insert, no_action, 'e'},
[4][7] = {insert, no_action, 'w'},

[5][0] = {no_action, no_action, 0},
[5][1] = {asdf_repeat_activate, asdf_repeat_deactivate, 0},
[5][2] = {asdf_modifier_capslock_activate, no_action, 0},
[5][3] = {insert, no_action, ASCII_CR},
[5][4] = {insert, no_action, ASCII_LF},
[5][5] = {insert, no_action, 'o'},
[5][6] = {insert, no_action, 'l'},
[5][7] = insert, no_action, ASCII_PERIOD},

  [6][0] = {insert, no_action, ASCII_TILDE},
  [6][1] = {insert, no_action, ASCII_RT_SQUARE_BRACE},
  [6][2] = {insert, no_action, ASCII_LT_SQUARE_BRACE},
  [6][3] = {insert, no_action, '-'},
  [6][4] = {insert, no_action, ':'},
  [6][5] = {insert, no_action, ASCII_ZERO},
  [6][6] = {insert, no_action, '9'},
  [6][7] = {insert, no_action, '8'},

  [7][0] = {insert, no_action, ASCII_AT},
  [7][1] = {insert, no_action, '7'},
  [7][2] = {insert, no_action, '6'},
  [7][3] = {insert, no_action, '5'},
  [7][4] = {insert, no_action, '4'},
  [7][5] = {insert, no_action, '3'},
  [7][6] = {insert, no_action, '2'},
  [7][7] = {insert, no_action, '1'},

  ASDF_CLASSIC_DIP_SWITCHES
  };

const FLASH classic_keycode_matrix_t classic_shift_matrix = {

[0][0] = {no_action, no_action, 0},
[0][1] = {asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0}
[0][2] = {{asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0}
[0][3] = {no_action, no_action, 0},
[0][4] = {insert, no_action, ASCII_ESC},
[0][5] = {insert, no_action, ASCII_TAB},
[0][6] = {asdf_modifier_ctrl_activate, asdf_modifier_ctrl_deactivate, 0},
[0][7] = {insert, no_action, ASCII_VERT_BAR},

[1][0] = {insert, no_action, ASCII_DEL},
[1][1] = {insert, no_action, 'P'},
[1][2] = {insert, no_action, '+'},
[1][3] = {insert, no_action, '?'},
[1][4] = {insert, no_action, ASCII_SPACE},
[1][5] = {insert, no_action, 'Z'},
[1][6] = {insert, no_action, 'A'},
[1][7] = {insert, no_action, 'Q'},

[2][0] = {asdf_virtual_activate, no_action, CLASSIC_ACTION_CLEAR},
[2][1] = {insert, no_action, '<'},
[2][2] = {insert, no_action, 'M'},
[2][3] = {insert, no_action, 'N'},
[2][4] = {insert, no_action, 'B'},
[2][5] = {insert, no_action, 'V'},
[2][6] = {insert, no_action, 'C'},
[2][7] = {insert, no_action, 'X'},

[3][0] = {no_action, no_action, 0},
[3][1] = {insert, no_action, 'K'},
[3][2] = {insert, no_action, 'J'},
[3][3] = {insert, no_action, 'H'},
[3][4] = {insert, no_action, 'G'},
[3][5] = {insert, no_action, 'F'},
[3][6] = {insert, no_action, 'D'},
[3][7] = {insert, no_action, 'S'},

[4][0] = {no_action, no_action, 0},
[4][1] = {insert, no_action, 'I'},
[4][2] = {insert, no_action, 'U'},
[4][3] = {insert, no_action, 'Y'},
[4][4] = {insert, no_action, 'T'},
[4][5] = {insert, no_action, 'R'},
[4][6] = {insert, no_action, 'E'},
[4][7] = {insert, no_action, 'W'},

[5][0] = {no_action, no_action, 0},
[5][1] = {asdf_repeat_activate, asdf_repeat_deactivate, 0},
[5][2] = {asdf_modifier_capslock_activate, asdf_modifier_capslock_activate, 0},
[5][3] = {insert, no_action, ASCII_CR},
[5][4] = {insert, no_action, ASCII_LF},
[5][5] = {insert, no_action, 'O'},
[5][6] = {insert, no_action, 'L'},
[5][7] = {insert, no_action, '>'},

[6][0] = {insert, no_action, ASCII_TILDE},
[6][1] = {insert, no_action, ASCII_RT_CURLY_BRACE},
[6][2] = {insert, no_action, ASCII_LT_CURLY_BRACE},
[6][3] = {insert, no_action, '='},
[6][4] = {insert, no_action, '*'},
[6][5] = {insert, no_action, ASCII_ZERO},
[6][6] = {insert, no_action, ASCII_RT_PAREN},
[6][7] = {insert, no_action, ASCII_LT_PAREN},


[7][0] = {insert, no_action, ASCII_GRAVE_ACCENT},
[7][1] = {insert, no_action, ASCII_SINGLE_QUOTE},
[7][2] = {insert, no_action, '&'},
[7][3] = {insert, no_action, '%'},
[7][4] = {insert, no_action, '$'},
[7][5] = {insert, no_action, '#'},
[7][6] = {insert, no_action, ASCII_DOUBLE_QUOTE},
[7][7] = {insert, no_action, '!'},

ASDF_CLASSIC_DIP_SWITCHES
};

const FLASH classic_keycode_matrix_t classic_caps_matrix = {

[0][0] = {no_action, no_action, 0},
[0][1] = {asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0},
[0][2] = {asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0},
[0][3] = {no_action, no_action, 0},
[0][4] = {insert, no_action, ASCII_ESC},
[0][5] = {insert, no_action, ASCII_TAB},
[0][6] = {asdf_modifier_ctrl_activate, asdf_modifier_ctrl_deactivate, 0},
[0][7] = {insert, no_action, ASCII_BACKSLASH},

[1][0] = {insert, no_action, ASCII_DEL},
[1][1] = {insert, no_action, 'P'},
[1][2] = {insert, no_action, ';'},
[1][3] = {insert, no_action, '/'},
[1][4] = {insert, no_action, ASCII_SPACE},
[1][5] = {insert, no_action, 'Z'},
[1][6] = {insert, no_action, 'A'},
[1][7] = {insert, no_action, 'Q'},


[2][0] = {asdf_virtual_activate, no_action, CLASSIC_ACTION_BREAK},
[2][1] = {insert, no_action, ASCII_COMMA},
[2][2] = {insert, no_action, 'M'},
[2][3] = {insert, no_action, 'N'},
[2][4] = {insert, no_action, 'B'},
[2][5] = {insert, no_action, 'V'},
[2][6] = {insert, no_action, 'C'},
[2][7] = {insert, no_action, 'X'},

[3][0] = {no_action, no_action, 0},
[3][1] = {insert, no_action, 'K'},
[3][2] = {insert, no_action, 'J'},
[3][3] = {insert, no_action, 'H'},
[3][4] = {insert, no_action, 'G'},
[3][5] = {insert, no_action, 'F'},
[3][6] = insert, no_action, 'D'},
[3][7] = {insert, no_action, 'S'},

[4][0] = {no_action, no_action, 0},
[4][1] = {insert, no_action, 'I'},
[4][2] = {insert, no_action, 'U'},
[4][3] = {insert, no_action, 'Y'},
[4][4] = {insert, no_action, 'T'},
[4][5] = {insert, no_action, 'R'},
[4][6] = {insert, no_action, 'E'},
[4][7] = {insert, no_action, 'W'},

[5][0] = {no_action, no_action, 0},
[5][1] = {asdf_repeat_activate, asdf_repeat_deactivate, 0},
[5][2] = {asdf_modifier_capslock_activate, asdf_modifier_capslock_activate, 0},
[5][3] = {insert, no_action, ASCII_CR},
[5][4] = {insert, no_action, ASCII_LF},
[5][5] = {insert, no_action, 'O'},
[5][6] = {insert, no_action, 'L'},
[5][7] = {insert, no_action, ASCII_PERIOD},

[6][0] = {insert, no_action, ASCII_TILDE},
[6][1] = {insert, no_action, ASCII_RT_SQUARE_BRACE},
[6][2] = {insert, no_action, ASCII_LT_SQUARE_BRACE},
[6][3] = {insert, no_action, '-'},
[6][4] = {insert, no_action, ':'},
[6][5] = {insert, no_action, ASCII_ZERO},
[6][6] = {insert, no_action, '9'},
[6][7] = {insert, no_action, '8'},

[7][0] = {insert, no_action, ASCII_AT},
[7][1] = {insert, no_action, '7'},
[7][2] = {insert, no_action, '6'},
[7][3] = {insert, no_action, '5'},
[7][4] = {insert, no_action, '4'},
[7][5] = {insert, no_action, '3'},
[7][6] = {insert, no_action, '2'},
[7][7] = {insert, no_action, '1'},

ASDF_CLASSIC_DIP_SWITCHES
};

const FLASH classic_keycode_matrix_t classic_ctrl_matrix = {
[0][0] = {no_action, no_action, 0},
[0][1] = {asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0},
[0][2] = {asdf_modifier_shift_activate, asdf_modifier_shift_deactivate, 0},
[0][3] = {no_action, no_action, 0},
[0][4] = {insert, no_action, ASCII_ESC},
[0][5] = {insert, no_action, ASCII_TAB},
[0][6] = {asdf_modifier_ctrl_activate, asdf_modifier_ctrl_deactivate, 0},
[0][7] = {insert, no_action, ASCII_FS}

[1][0] = {no_action, no_action, 0},
[1][1] = {insert, no_action, ASCII_CTRL_P},
[1][2] = {no_action, no_action, 0},
[1][3] = {no_action, no_action, 0},
[1][4] = {insert, no_action, ASCII_SPACE},
[1][5] = {insert, no_action, ASCII_CTRL_Z},
[1][6] = {insert, no_action, ASCII_CTRL_A},
[1][7] = {insert, no_action, ASCII_CTRL_Q},

[2][0] = {asdf_virtual_activate, no_action, CLASSIC_ACTION_RESET},
[2][1] = {insert, no_action, ASCII_COMMA,},
[2][2] = {insert, no_action, ASCII_CTRL_M},
[2][3] = {insert, no_action, ASCII_CTRL_N},
[2][4] = {insert, no_action, ASCII_CTRL_B},
[2][5] = {insert, no_action, ASCII_CTRL_V},
[2][6] = {insert, no_action, ASCII_CTRL_C},
[2][7] = {insert, no_action, ASCII_CTRL_X},

[3][0] = {no_action, no_action, 0},
[3][1] = {insert, no_action, ASCII_CTRL_K},
[3][2] = {insert, no_action, ASCII_CTRL_J},
[3][3] = {insert, no_action, ASCII_CTRL_H},
[3][4] = {insert, no_action, ASCII_CTRL_G},
[3][5] = {insert, no_action, ASCII_CTRL_F},
[3][6] = {insert, no_action, ASCII_CTRL_D},
[3][7] = {insert, no_action, ASCII_CTRL_S},

[4][0] = {no_action, no_action, 0},
[4][1] = {insert, no_action, ASCII_CTRL_I},
[4][2] = {insert, no_action, ASCII_CTRL_U},
[4][3] = {insert, no_action, ASCII_CTRL_Y},
[4][4] = {insert, no_action, ASCII_CTRL_T},
[4][5] = {insert, no_action, ASCII_CTRL_R},
[4][6] = {insert, no_action, ASCII_CTRL_E},
[4][7] = {insert, no_action, ASCII_CTRL_W},

[5][0] = {no_action, no_action, 0},
[5][1] = {asdf_repeat_activate, asdf_repeat_deactivate, 0}
[5][2] = {asdf_modifier_capslock_activate, asdf_modifier_capslock_activate, 0},
[5][3] = {insert, no_action, ASCII_CR},
[5][4] = {insert, no_action, ASCII_LF},
[5][5] = {insert, no_action, ASCII_CTRL_O},
[5][6] = {insert, no_action, ASCII_CTRL_L},
[5][7] = {no_action, no_action, 0},

[6][0] = {no_action, no_action, 0},
[6][1] = {insert, no_action, ASCII_GS},
[6][2] = {insert, no_action, ASCII_ESC},
[6][3] = {no_action, no_action, 0},
[6][4] = {no_action, no_action, 0},
[6][5] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_10},
[6][6] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_9},
[6][7] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_8},

[7][0] = {insert, no_action, ASCII_NULL},
[7][1] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_7},
[7][2] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_6},
[7][3] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_5},
[7][4] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_4},
[7][5] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_3},
[7][6] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_2},
[7][7] = {asdf_hook_execute, no_action, ASDF_HOOK_USER_1},

ASDF_CLASSIC_DIP_SWITCHES,
};



static const classic_keycode_matrix_t *classic_maps[] = {
[CLASSIC_CAPS_MAP] = &classic_caps_matrix,
[CLASSIC_PLAIN_MAP] = &classic_plain_matrix,
[CLASSIC_SHIFT_MAP] = &classic_shift_matrix,
[CLASSIC_CTRL_MAP] = &classic_ctrl_matrix,
};

void classic_add_map(const classic_map_index_t map_index,
                     modifier_index_t modifier_index)
{

  asdf_keycode_t (*matrix)[CLASSIC_NUM_COLS] =
    (asdf_keycode_t (*)[CLASSIC_NUM_COLS]) classic_maps[map_index];

  asdf_keymaps_add_map(&matrix[0][0], modifier_index, (uint8_t) CLASSIC_NUM_ROWS,
                       (uint8_t) CLASSIC_NUM_COLS);
}



//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
