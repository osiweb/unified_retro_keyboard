// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
//  Unfified Keyboard Project
//  ASDF keyboard firmware
//
//  test_keymapdefs.h
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

// While there is nothing preventing a standard keyboard from having both a
// "Shift Lock" key and a "Caps Lock" key, usually only one will be present. For
// testing, both must be present to test their functionality.


#if !(defined) TEST_KEYMAPDEFS_H


#define PLAIN_MATRIX_1 RESERVED_1
#define CAPS_MATRIX_1 RESERVED_2
#define SHIFT_MATRIX_1 RESERVED_3
#define CTRL_MATRIX_1 RESERVED_4

#define SINGLE_TESTS_KEYMAP ASDF_TEST_PLAIN_MAP_INDEX
#define DOUBLE_ASSIGN_TEST_KEYMAP ASDF_TEST_PLAIN_MAP_INDEX
#define TRIPLE_TESTS_KEYMAP ASDF_TEST_CAPS_MAP_INDEX

#define ASDF_TEST_MAP_DIP_SWITCHES                                      \
  [ASDF_LAST_ROW] = { ACTION_MAPSEL_0, ACTION_MAPSEL_1, ACTION_MAPSEL_2, ACTION_MAPSEL_3 }

#endif // TEST_KEYMAPDEFS_H

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
