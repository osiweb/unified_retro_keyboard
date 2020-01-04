// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
//  Unified Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_ascii.h
//
// This file contains definitions of ASCII control cods and certain symbols, in
// order to avoid escaping special characters in the keymap definitions, and to
// improve keymap readability.
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

#if !defined(ASDF_ASCII_H)
#define ASDF_ASCII_H

typedef enum {
  ASCII_CTRL_A = 0x01,
  ASCII_CTRL_B = 0x02,
  ASCII_CTRL_C = 0x03,
  ASCII_CTRL_D = 0x04,
  ASCII_CTRL_E = 0x05,
  ASCII_CTRL_F = 0x06,
  ASCII_CTRL_G = 0x07,
  ASCII_CTRL_H = 0x08,
  ASCII_CTRL_I = 0x09,
  ASCII_CTRL_J = 0x0a,
  ASCII_CTRL_K = 0x0b,
  ASCII_CTRL_L = 0x0c,
  ASCII_CTRL_M = 0x0d,
  ASCII_CTRL_N = 0x0e,
  ASCII_CTRL_O = 0x0f,
  ASCII_CTRL_P = 0x10,
  ASCII_CTRL_Q = 0x11,
  ASCII_CTRL_R = 0x12,
  ASCII_CTRL_S = 0x13,
  ASCII_CTRL_T = 0x14,
  ASCII_CTRL_U = 0x15,
  ASCII_CTRL_V = 0x16,
  ASCII_CTRL_W = 0x17,
  ASCII_CTRL_X = 0x18,
  ASCII_CTRL_Y = 0x19,
  ASCII_CTRL_Z = 0x1a,
  ASCII_ESC = 0x1b,
  ASCII_SPACE = 0x20,
  ASCII_COMMA = 0x2C,
  ASCII_ZERO = 0x30,
  ASCII_AT = 0x40,
  ASCII_LT_CURLY_BRACE = 0x7b,
  ASCII_RT_CURLY_BRACE = 0x7d,
  ASCII_LT_SQUARE_BRACE = 0x5b,
  ASCII_RT_SQUARE_BRACE = 0x5d,
  ASCII_LT_PAREN = 0x28,
  ASCII_RT_PAREN = 0x29,
  ASCII_SINGLE_QUOTE = 0x27,
  ASCII_DOUBLE_QUOTE = 0x22,
  ASCII_BACKSLASH = 0x5c,
  ASCII_GRAVE_ACCENT = 0x60,
  ASCII_PERIOD = 0x2e,
  ASCII_TILDE = 0x7e,
  ASCII_VERT_BAR = 0x7c,
  ASCII_DEL = 0x7f
} ascii;

#define ASCII_LF ASCII_CTRL_J
#define ASCII_CR ASCII_CTRL_M
#define ASCII_TAB ASCII_CTRL_I

#endif // !defined (ASDF_ASCII_H)

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
