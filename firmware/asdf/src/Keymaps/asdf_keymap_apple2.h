// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_apple2.h
//
// Apple 2 keymaps
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


// This file supplies the Apple 2 ASCII keyboard keymap.  Two variants are provided:
//
// 1) An Upper/Lowercase variant. This variant moves the @ and ^ symbols from
//    the P and N keys to the REPEAT key, since the P and N keys need to reserve
//    the shifted value for the uppercase characters. Also, the "Power" key
//    doubles as a caps-lock key.
//
// 2) A CAPS only keyboard, following the standard Apple II conventions and
//    layout, with ^ above the N key and @ above the P key, and a functioning
//    REPEAT key.
//
// For both variants, CTRL+RESET is required for a system reset.

#if !defined(ASDF_KEYMAP_DEFS_APPLE2_H)
#define ASDF_KEYMAP_DEFS_APPLE2_H

// include DIP switch definitions
#include "asdf_keymap_defs_dipswitch.h"

// Edit the number of rows and columns used in this map. If the number is less
// than the maxium, the unused elements will be initialized to 0.

#endif /* !defined (ASDF_KEYMAP_DEFS_APPLE2_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
