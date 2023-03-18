// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_ace1000.h
//
// ASCII keymaps for the Franklin ACE 1000 replacement keyboard
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


// To use this ascii for a new keymap, edit the keymaps definitions as
// desired. The keymaps are organized from row 0, counting upward, and each row
// includes the columns from 0-NUM_COLS.
//

#if !defined(ASDF_KEYMAP_DEFS_ACE1000_H)
#define ASDF_KEYMAP_DEFS_ACE1000_H

#include "asdf_hook.h"

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#define ACE1000_NUM_ROWS 10 // DIP switches are row 8 (zero based)
#define ACE1000_NUM_COLS 8

#define ACE1000_ACTION_BREAK ACTION_NOTHING

#define ACE1000_VIRTUAL_RESET VOUT1
#define ACE1000_ACTION_RESET ACTION_VOUT1
#define ACE1000_RESET_OUTPUT PHYSICAL_OUT3_OPEN_HI
#define ACE1000_RESET_ACTIVE_VALUE 0

#define ACE1000_VIRTUAL_CLR_SCR VOUT2
#define ACE1000_ACTION_CLEAR ACTION_VOUT2
#define ACE1000_CLR_SCR_OUT PHYSICAL_OUT1_OPEN_LO
#define ACE1000_CLR_SCR_ACTIVE_VALUE 1

#define ACE1000_VIRTUAL_POWER_LED VLED1
#define ACE1000_POWER_LED PHYSICAL_LED1
#define ACE1000_POWER_LED_INIT_VALUE 1

#define ACE1000_CAPS_LED PHYSICAL_LED3
#define ACE1000_CAPS_LED_INIT_VALUE 0

#define ACE1000_ID_MESSAGE_HOOK ASDF_HOOK_USER_10
#define APPLESOFT_KEYBOARD_TEST_HOOK ASDF_HOOK_USER_9

#define ASDF_ACE1000_PRINT_SPEED 40

#endif /* !defined (ASDF_KEYMAP_DEFS_ACE1000_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
