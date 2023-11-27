// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_ace1000_add_map.c
//
// Keymap matrices used by the Franklin ACE 1000 replacement keyboard
// https://github.com/ryucats/Franklin-ACE-1000-Keyboard
//
// Copyright 2023 Chris RYU
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
#include "asdf_print.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_ace1000.h"
#include "asdf_keymap_ace1000_add_map.h"
#include "asdf_keymap_defs_dipswitch.h"

// Key Matrix for the Franklin ACE 1000 replacement keyboard by Chris RYU

#define ASDF_ACE1000_DIP_SWITCHES ASDF_KEYMAP_DIP_SWITCHES

typedef asdf_keycode_t ace1000_keycode_matrix_t[ACE1000_NUM_ROWS][ACE1000_NUM_COLS];

const FLASH ace1000_keycode_matrix_t ace1000_plain_matrix = {
    [0] = { ACE_KEY_ESC, ACE_KEY_BREAK, ACE_KEY_PAUSE, ACTION_CTRL, ACE_KEY_TAB, ACTION_CAPS, ACTION_SHIFT, ACE_KEY_SPACE,  },
    [1] = { ACE_KEY_1, ACE_KEY_Q, ACE_KEY_A, ACE_KEY_Z, ACE_KEY_2, ACE_KEY_W, ACE_KEY_S, ACE_KEY_X,  },
    [2] = { ACE_KEY_3, ACE_KEY_E, ACE_KEY_D, ACE_KEY_C, ACE_KEY_4, ACE_KEY_R, ACE_KEY_F, ACE_KEY_V,  },
    [3] = { ACE_KEY_5, ACE_KEY_T, ACE_KEY_G, ACE_KEY_B, ACE_KEY_6, ACE_KEY_Y, ACE_KEY_H, ACE_KEY_N,  },
    [4] = { ACE_KEY_7, ACE_KEY_U, ACE_KEY_J, ACE_KEY_M, ACE_KEY_8, ACE_KEY_I, ACE_KEY_K, ACE_KEY_COMMA,  },
    [5] = { ACE_KEY_9, ACE_KEY_O, ACE_KEY_L, ACE_KEY_PERIOD, ACE_KEY_RIGHT, ACE_KEY_UNDERSCORE, ACE_KEY_PLUS, ACE_KEY_SPLAT,  },
    [6] = { ACE_KEY_0, ACE_KEY_P, ACE_KEY_SEMI, ACE_KEY_SLASH, ACE_KEY_7, ACE_KEY_4, ACE_KEY_1, ACE_KEY_GT,  },
    [7] = { ACE_KEY_MINUS, ACE_KEY_CURLY, ACE_KEY_QUOTE, ACTION_SHIFT, ACE_KEY_8, ACE_KEY_5, ACE_KEY_2, ACE_KEY_0,  },
    [9] = { ACE_KEY_SLASH, ACE_KEY_SQUARE, ACE_KEY_RETURN, ACE_KEY_LEFT, ACE_KEY_9, ACE_KEY_6, ACE_KEY_3, ACE_KEY_PERIOD,  },
    ASDF_ACE_DIP_SWITCHES,
};

const FLASH ace1000_keycode_matrix_t ace1000_shift_matrix = {
    [0] = { ACE_KEY_SHIFT_ESC, ACE_KEY_SHIFT_BREAK, ACE_KEY_SHIFT_PAUSE, ACTION_CTRL, ACE_KEY_SHIFT_TAB, ACTION_CAPS, ACTION_SHIFT, ACE_KEY_SHIFT_SPACE,  },
    [1] = { ACE_KEY_SHIFT_1, ACE_KEY_SHIFT_Q, ACE_KEY_SHIFT_A, ACE_KEY_SHIFT_Z, ACE_KEY_SHIFT_2, ACE_KEY_SHIFT_W, ACE_KEY_SHIFT_S, ACE_KEY_SHIFT_X,  },
    [2] = { ACE_KEY_SHIFT_3, ACE_KEY_SHIFT_E, ACE_KEY_SHIFT_D, ACE_KEY_SHIFT_C, ACE_KEY_SHIFT_4, ACE_KEY_SHIFT_R, ACE_KEY_SHIFT_F, ACE_KEY_SHIFT_V,  },
    [3] = { ACE_KEY_SHIFT_5, ACE_KEY_SHIFT_T, ACE_KEY_SHIFT_G, ACE_KEY_SHIFT_B, ACE_KEY_SHIFT_6, ACE_KEY_SHIFT_Y, ACE_KEY_SHIFT_H, ACE_KEY_SHIFT_N,  },
    [4] = { ACE_KEY_SHIFT_7, ACE_KEY_SHIFT_U, ACE_KEY_SHIFT_J, ACE_KEY_SHIFT_M, ACE_KEY_SHIFT_8, ACE_KEY_SHIFT_I, ACE_KEY_SHIFT_K, ACE_KEY_SHIFT_COMMA,  },
    [5] = { ACE_KEY_SHIFT_9, ACE_KEY_SHIFT_O, ACE_KEY_SHIFT_L, ACE_KEY_SHIFT_PERIOD, ACE_KEY_SHIFT_RIGHT, ACE_KEY_SHIFT_UNDERSCORE, ACE_KEY_SHIFT_PLUS, ACE_KEY_SHIFT_SPLAT,  },
    [6] = { ACE_KEY_SHIFT_0, ACE_KEY_SHIFT_P, ACE_KEY_SHIFT_SEMI, ACE_KEY_SHIFT_SLASH, ACE_KEY_SHIFT_7, ACE_KEY_SHIFT_4, ACE_KEY_SHIFT_1, ACE_KEY_SHIFT_GT,  },
    [7] = { ACE_KEY_SHIFT_MINUS, ACE_KEY_SHIFT_CURLY, ACE_KEY_SHIFT_QUOTE, ACTION_SHIFT, ACE_KEY_SHIFT_8, ACE_KEY_SHIFT_5, ACE_KEY_SHIFT_2, ACE_KEY_SHIFT_0,  },
    [9] = { ACE_KEY_SHIFT_SLASH, ACE_KEY_SHIFT_SQUARE, ACE_KEY_RETURN, ACE_KEY_SHIFT_LEFT, ACE_KEY_SHIFT_9, ACE_KEY_SHIFT_6, ACE_KEY_SHIFT_3, ACE_KEY_SHIFT_PERIOD,  },
    ASDF_ACE_DIP_SWITCHES,
};

const FLASH ace1000_keycode_matrix_t ace1000_caps_matrix = {
    [0] = { ACE_KEY_ESC, ACE_KEY_BREAK, ACE_KEY_PAUSE, ACTION_CTRL, ACE_KEY_TAB, ACTION_CAPS, ACTION_SHIFT, ACE_KEY_SPACE,  },
    [1] = { ACE_KEY_1, ACE_KEY_SHIFT_Q, ACE_KEY_SHIFT_A, ACE_KEY_SHIFT_Z, ACE_KEY_2, ACE_KEY_SHIFT_W, ACE_KEY_SHIFT_S, ACE_KEY_SHIFT_X,  },
    [2] = { ACE_KEY_3, ACE_KEY_SHIFT_E, ACE_KEY_SHIFT_D, ACE_KEY_SHIFT_C, ACE_KEY_4, ACE_KEY_SHIFT_R, ACE_KEY_SHIFT_F, ACE_KEY_SHIFT_V,  },
    [3] = { ACE_KEY_5, ACE_KEY_SHIFT_T, ACE_KEY_SHIFT_G, ACE_KEY_SHIFT_B, ACE_KEY_6, ACE_KEY_SHIFT_Y, ACE_KEY_SHIFT_H, ACE_KEY_SHIFT_N,  },
    [4] = { ACE_KEY_7, ACE_KEY_SHIFT_U, ACE_KEY_SHIFT_J, ACE_KEY_SHIFT_M, ACE_KEY_8, ACE_KEY_SHIFT_I, ACE_KEY_SHIFT_K, ACE_KEY_COMMA,  },
    [5] = { ACE_KEY_9, ACE_KEY_SHIFT_O, ACE_KEY_SHIFT_L, ACE_KEY_PERIOD, ACE_KEY_RIGHT, ACE_KEY_UNDERSCORE, ACE_KEY_PLUS, ACE_KEY_SPLAT,  },
    [6] = { ACE_KEY_0, ACE_KEY_SHIFT_P, ACE_KEY_SEMI, ACE_KEY_SLASH, ACE_KEY_7, ACE_KEY_4, ACE_KEY_1, ACE_KEY_GT,  },
    [7] = { ACE_KEY_MINUS, ACE_KEY_CURLY, ACE_KEY_QUOTE, ACTION_SHIFT, ACE_KEY_8, ACE_KEY_5, ACE_KEY_2, ACE_KEY_0,  },
    [9] = { ACE_KEY_SLASH, ACE_KEY_SQUARE, ACE_KEY_RETURN, ACE_KEY_LEFT, ACE_KEY_9, ACE_KEY_6, ACE_KEY_3, ACE_KEY_PERIOD,  },
    ASDF_ACE_DIP_SWITCHES,
};

const FLASH ace1000_keycode_matrix_t ace1000_ctrl_matrix = {
    [0] = { ACE_KEY_ESC, ACE_KEY_BREAK, ACE_KEY_PAUSE, ACTION_CTRL, ACE_KEY_TAB, ACTION_CAPS, ACTION_SHIFT, ACE_KEY_SPACE,  },
    [1] = { ACE_KEY_CTRL_1, ACE_KEY_CTRL_Q, ACE_KEY_CTRL_A, ACE_KEY_CTRL_Z, ACE_KEY_CTRL_2, ACE_KEY_CTRL_W, ACE_KEY_CTRL_S, ACE_KEY_CTRL_X,  },
    [2] = { ACE_KEY_CTRL_3, ACE_KEY_CTRL_E, ACE_KEY_CTRL_D, ACE_KEY_CTRL_C, ACE_KEY_CTRL_4, ACE_KEY_CTRL_R, ACE_KEY_CTRL_F, ACE_KEY_CTRL_V,  },
    [3] = { ACE_KEY_CTRL_5, ACE_KEY_CTRL_T, ACE_KEY_CTRL_G, ACE_KEY_CTRL_B, ACE_KEY_CTRL_6, ACE_KEY_CTRL_Y, ACE_KEY_CTRL_H, ACE_KEY_CTRL_N,  },
    [4] = { ACE_KEY_CTRL_7, ACE_KEY_CTRL_U, ACE_KEY_CTRL_J, ACE_KEY_CTRL_M, ACE_KEY_CTRL_8, ACE_KEY_CTRL_I, ACE_KEY_CTRL_K, ACE_KEY_CTRL_COMMA,  },
    [5] = { ACE_KEY_CTRL_9, ACE_KEY_CTRL_O, ACE_KEY_CTRL_L, ACE_KEY_CTRL_PERIOD, ACE_KEY_CTRL_RIGHT, ACE_KEY_CTRL_UNDERSCORE, ACE_KEY_CTRL_PLUS, ACE_KEY_CTRL_SPLAT,  },
    [6] = { ACE_KEY_CTRL_0, ACE_KEY_CTRL_P, ACE_KEY_CTRL_SEMI, ACE_KEY_CTRL_SLASH, ACE_KEY_CTRL_7, ACE_KEY_CTRL_4, ACE_KEY_CTRL_1, ACE_KEY_CTRL_GT,  },
    [7] = { ACE_KEY_CTRL_MINUS, ACE_KEY_CTRL_CURLY, ACE_KEY_CTRL_QUOTE, ACTION_SHIFT, ACE_KEY_CTRL_8, ACE_KEY_CTRL_5, ACE_KEY_CTRL_2, ACE_KEY_CTRL_0,  },
    [9] = { ACE_KEY_CTRL_SLASH, ACE_KEY_CTRL_SQUARE, ACE_KEY_RETURN, ACE_KEY_CTRL_LEFT, ACE_KEY_CTRL_9, ACE_KEY_CTRL_6, ACE_KEY_CTRL_3, ACE_KEY_CTRL_PERIOD,  },
    ASDF_ACE_DIP_SWITCHES,
};

static const ace1000_keycode_matrix_t *ace1000_maps[] = {
  [ACE1000_CAPS_MAP] = &ace1000_caps_matrix,
  [ACE1000_PLAIN_MAP] = &ace1000_plain_matrix,
  [ACE1000_SHIFT_MAP] = &ace1000_shift_matrix,
  [ACE1000_CTRL_MAP] = &ace1000_ctrl_matrix,
};

void ace1000_add_map(const ace1000_map_index_t map_index,
                     modifier_index_t modifier_index)
{

  asdf_keycode_t (*matrix)[ACE1000_NUM_COLS] =
    (asdf_keycode_t (*)[ACE1000_NUM_COLS]) ace1000_maps[map_index];

    asdf_keymaps_add_map(&matrix[0][0], modifier_index, (uint8_t) ACE1000_NUM_ROWS,
                       (uint8_t) ACE1000_NUM_COLS);
}

void ace1000_keyboard_test(void)
{
    asdf_print("10GETA$(0):A=ASC(A$(0)):A$(1)=\"CTL+\"+CHR$(A + 64):?\"'\";A$(A<32);\"' = \";A:IFA<>3GOTO10\r");
}




//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
