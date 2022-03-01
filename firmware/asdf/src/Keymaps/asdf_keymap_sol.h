// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymaps_sol.h
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

#if !defined(ASDF_KEYMAP_SOL_H)
#define ASDF_KEYMAP_SOL_H
#include "asdf.h"
#include "asdf_keymap_defs_dipswitch.h"

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#define ASDF_SOL_NUM_ROWS 13 // DIP switches are row 9
#define ASDF_SOL_NUM_COLS 8


// Key Matrix for combination of ASCII controller (ATMega328P version) and Classic ASCII matrix
//
// Col->   0          1          2          3          4          5          6          7
// Row 0   Lt Ctrl    ShiftLock  A          S          D          F          G(alpha)   H
// Row 1   J          K          L          ;(semi)    :(colon)   DEL        Repeat     Rt Ctrl
// Row 2   UpperCase  Lt Shift   Z          X          C          V          B(alpha)   N
// Row 3   M          ,(comma)   .(period)  /(slash)   Rt Shift   ModeSelect
// Row 4   ESC        1          2          3          4          5          6(six)     7
// Row 5   8(eight)   9          0(zero)    -(Dash)    ^(Caret)   [          \          ]
// Row 6   BREAK      TAB        Q          W          E          R          T          Y
// Row 7   U          I          O(alpha)   P          @(at)      Return     LineFeed   Load
// Row 9   LOCAL      UpArrow    LtArrow    Spacebar   RtArrow    DnArrow    Home       Clear
// Row 10  NP-Minus   NP-7       NP-Times   NP-8       NP-Divide  NP-9       (none)     (none)
// Row 11  NP-4       NP-1       NP-5       NP-2       NP-6       NP-3       (none)     (none)
// Row 12  NP-0       NP-period  NP-Plus
//
// Row 8   DIP switches 0-7
//
// Physical Resource mapping:
// LED1: UPPER CASE
// LED2: LOCAL
// LED3: SHIFT LOCK
// OUT1: RESET
// OUT2: BREAK
// OUT3: LOCAL

// Notes:
//
// 1) To ensure consistent DIP switch operation within the keymap, a
//    ASDF_SOL_DIP_SWITCHES macro is defined. Keeping the ACTION_MAPSEL0-3
//    definitions in positions 0-3 ensures consistent map selection among all
//    keymaps.


#define SOL_PRINT_DELAY 40 // msec
#define SOL_ID_MESSAGE_HOOK ASDF_HOOK_USER_10

#define SOL_NUM_ROWS 13
#define SOL_NUM_COLS 8

#define SOL_KBD_VRESET VOUT1
#define SOL_KBD_VBREAK VOUT2
#define SOL_KBD_VLOCAL VOUT3
#define SOL_KBD_LED_ON 1
#define SOL_KBD_LED_OFF 0

// The SOL manual (sec. 7.7.8) indicates shiftlock locks SHIFT on, and SHIFT
// returns to unshifted. For Toggle behavior, change to ACTION_SHIFTLOCK_TOGGLE.
#define SOL_KBD_SHIFTLOCK_ACTION ACTION_SHIFTLOCK_ON


// The weird C preprocessor expansion behavior requires one dereference for each
// expansion.
#define SOL_KBD_VIRTUAL_SUB1(SOL_VDEVICE) ACTION_ ## SOL_VDEVICE
#define SOL_KBD_VIRTUAL_SUB(SOL_VDEVICE) SOL_KBD_VIRTUAL_SUB1(SOL_VDEVICE)
#define SOL_KBD_LOCAL_ACTION SOL_KBD_VIRTUAL_SUB(SOL_KBD_VLOCAL)
#define SOL_KBD_RESET_ACTION SOL_KBD_VIRTUAL_SUB(SOL_KBD_VRESET)
#define SOL_KBD_BREAK_ACTION SOL_KBD_VIRTUAL_SUB(SOL_KBD_VBREAK)

#define SOL_ASCII_LOAD 0x8C
#define SOL_ASCII_MODE_SELECT 0x80
#define SOL_ASCII_UP_ARROW 0x97
#define SOL_ASCII_LT_ARROW 0x81
#define SOL_ASCII_RT_ARROW 0x93
#define SOL_ASCII_DN_ARROW 0x9a
#define SOL_ASCII_HOME 0x8e
#define SOL_ASCII_CLEAR 0x8b

#define SOL_KBD_TTL_HIGH 1
#define SOL_KBD_TTL_LOW 0

#define SOL_KBD_LED_UPPERCASE PHYSICAL_LED1
#define SOL_KBD_LED_LOCAL PHYSICAL_LED2
#define SOL_KBD_LED_SHIFTLOCK PHYSICAL_LED3
#define SOL_KBD_TTLOUT_RESET PHYSICAL_OUT3_OPEN_HI // Emulate open collector output.
#define SOL_KBD_TTLOUT_BREAK PHYSICAL_OUT2
#define SOL_KBD_TTLOUT_LOCAL PHYSICAL_OUT1

#define ASDF_SOL_DIP_SWITCHES ASDF_KEYMAP_DIP_SWITCHES


#endif /* !defined (ASDF_KEYMAP_SOL_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
