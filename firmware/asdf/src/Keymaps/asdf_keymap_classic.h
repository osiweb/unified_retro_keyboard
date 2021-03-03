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

// include DIP switch definitions
#include "asdf_keymap_defs_dipswitch.h"

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#define ASDF_CLASSIC_NUM_ROWS 9 // DIP switches are row 8 (zero based)
#define ASDF_CLASSIC_NUM_COLS 8

#define CLASSIC_ACTION_BREAK ACTION_NOTHING

#define CLASSIC_VIRTUAL_RESET VOUT1
#define CLASSIC_ACTION_RESET ACTION_VOUT1
#define CLASSIC_RESET_OUTPUT PHYSICAL_OUT3_OPEN_HI
#define CLASSIC_RESET_ACTIVE_VALUE 0

#define CLASSIC_VIRTUAL_CLR_SCR VOUT2
#define CLASSIC_ACTION_CLEAR ACTION_VOUT2
#define CLASSIC_CLR_SCR_OUT PHYSICAL_OUT1_OPEN_LO
#define CLASSIC_CLR_SCR_ACTIVE_VALUE 1

#define CLASSIC_VIRTUAL_POWER_LED VLED1
#define CLASSIC_POWER_LED PHYSICAL_LED1
#define CLASSIC_POWER_LED_INIT_VALUE 1

#define CLASSIC_CAPS_LED PHYSICAL_LED3
#define CLASSIC_CAPS_LED_INIT_VALUE 0



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



#endif /* !defined (ASDF_KEYMAP_DEFS_ASCII_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
