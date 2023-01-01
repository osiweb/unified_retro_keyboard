// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*- 
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_defs_dipswitch.h
//
// Contains defitions for DIP switch settings shared by all keymaps.
//
// Copyright 2019 David Fenyes
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
 
#if !defined (DEPS_DIPSWITCH_H)
#define DEPS_DIPSWITCH_H

#define ASDF_KEYMAP_DIP_SWITCHES                                     \
  [ASDF_ARCH_DIPSWITCH_ROW] = {                                     \
                               [0] = ACTION_MAPSEL_0,               \
                               [1] = ACTION_MAPSEL_1,               \
                               [2] = ACTION_MAPSEL_2,               \
                               [3] = ACTION_MAPSEL_3,               \
                               [5] = ACTION_FN_11,                   \
                               [6] = ACTION_STROBE_POLARITY_SELECT, \
                               [7] = ACTION_AUTOREPEAT_SELECT,      \
  }

//
// Device and peripheral definitions, comments should include use of devices.
// Please
//

#endif /* !defined (DEPS_DIPSWITCH_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
