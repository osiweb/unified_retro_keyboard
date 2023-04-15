// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_classic.h
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

#if !defined(ASDF_KEYMAP_DEFS_CLASSIC_H)
#define ASDF_KEYMAP_DEFS_CLASSIC_H

#include "asdf_hook.h"

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#define CLASSIC_NUM_ROWS 9 // DIP switches are row 8 (zero based)
#define CLASSIC_NUM_COLS 8

#define CLASSIC_VIRTUAL_BREAK, V_NULL

#define CLASSIC_VIRTUAL_RESET VOUT1
#define CLASSIC_RESET_OUTPUT PHYSICAL_OUT3_OPEN_HI
#define CLASSIC_RESET_ACTIVE_VALUE 0

#define CLASSIC_VIRTUAL_CLR_SCR VOUT2
#define CLASSIC_CLR_SCR_OUT PHYSICAL_OUT1_OPEN_LO
#define CLASSIC_CLR_SCR_ACTIVE_VALUE 1

#define CLASSIC_VIRTUAL_POWER_LED VLED1
#define CLASSIC_POWER_LED PHYSICAL_LED1
#define CLASSIC_POWER_LED_INIT_VALUE 1

#define CLASSIC_CAPS_LED PHYSICAL_LED3
#define CLASSIC_CAPS_LED_INIT_VALUE 0

#define CLASSIC_ID_MESSAGE_HOOK ASDF_HOOK_USER_10
#define APPLESOFT_KEYBOARD_TEST_HOOK ASDF_HOOK_USER_9

#define ASDF_CLASSIC_PRINT_SPEED 40

#endif /* !defined (ASDF_KEYMAP_DEFS_ASCII_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
