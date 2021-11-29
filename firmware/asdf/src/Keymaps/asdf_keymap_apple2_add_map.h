// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_apple_add_map.h
//
// defines keymap matrices and add_map() function for apple2 layouts
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

#if !defined(ASDF_KEYMAP_APPLE_ADD_MAP_H)
#define ASDF_KEYMAP_APPLE_ADD_MAP_H

#include "asdf_keymap_defs_dipswitch.h"
#include "asdf_modifiers.h"

#define ASDF_APPLE2_NUM_ROWS 9 // DIP switches are row 8 (zero-based)
#define ASDF_APPLE2_NUM_COLS 8

#define APPLE_ACTION_RESET ACTION_VOUT1
#define APPLE_VIRTUAL_RESET VOUT1
#define APPLE_RESET_OUTPUT PHYSICAL_OUT3_OPEN_HI
#define APPLE_RESET_ACTIVE_VALUE 0

#define APPLE_ACTION_CLEAR ACTION_VOUT2
#define APPLE_VIRTUAL_CLR_SCR VOUT2
#define APPLE_CLR_SCR_OUTPUT PHYSICAL_OUT1_OPEN_LO
#define APPLE_CLR_SCR_ACTIVE_VALUE 1

#define APPLE_VIRTUAL_POWER_LED VLED1
#define APPLE_POWER_LED PHYSICAL_LED1
#define APPLE_POWER_LED_INIT_VALUE 1

#define APPLE_VIRTUAL_DISABLED_LED VLED2
#define APPLE_DISABLED_LED PHYSICAL_LED3
#define APPLE_DISABLED_INIT_VALUE 0

#define ASDF_APPLE2_DIP_SWITCHES ASDF_KEYMAP_DIP_SWITCHES

#define APPLE_LEFT_ARROW ASCII_CTRL_H
#define APPLE_RIGHT_ARROW ASCII_CTRL_U

typedef enum {
  APPLE_PLAIN_MAP,
  APPLE_CAPS_MAP,
  APPLE_SHIFT_MAP,
  APPLE_CAPS_SHIFT_MAP,
  APPLE_CTRL_MAP
} apple_map_index_t;


// function prototypes
void apple_add_map(const apple_map_index_t map_index, modifier_index_t modifier_index);

#endif /* !defined (ASDF_KEYMAP_APPLE_ADD_MAP_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
