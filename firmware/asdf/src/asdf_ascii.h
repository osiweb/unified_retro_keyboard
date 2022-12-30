// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
//  Unified Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_ascii.h
//
// This file contains definitions of ASCII control codes and certain symbols for
// keymap definitions. The purpose is to improve readability and consistency of
// the keymap matrices, and avoid escaping special characters in the keymap
// definitions.
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

// List of all ASCII control codes
typedef enum {
  ASCII_NULL = 0x00,
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
  ASCII_FS = 0x1c, // File Separator
  ASCII_GS = 0x1d, // Group Separator
  ASCII_RS = 0x1e, // Record Separator
  ASCII_US = 0x1f, // Unit Separator
  ASCII_SPACE = 0x20,
  ASCII_DOUBLE_QUOTE = 0x22,
  ASCII_SINGLE_QUOTE = 0x27,
  ASCII_LT_PAREN = 0x28,
  ASCII_RT_PAREN = 0x29,
  ASCII_COMMA = 0x2C,
  ASCII_PERIOD = 0x2e,
  ASCII_ZERO = 0x30,
  ASCII_AT = 0x40,
  ASCII_LT_SQUARE_BRACE = 0x5b,
  ASCII_RT_SQUARE_BRACE = 0x5d,
  ASCII_UNDERSCORE = 0x5f,
  ASCII_BACKSLASH = 0x5c,
  ASCII_CARET = 0x5e,
  ASCII_GRAVE_ACCENT = 0x60,
  ASCII_LT_CURLY_BRACE = 0x7b,
  ASCII_RT_CURLY_BRACE = 0x7d,
  ASCII_TILDE = 0x7e,
  ASCII_VERT_BAR = 0x7c,
  ASCII_DEL = 0x7f,
  ASCII_MAX_PRINTABLE = 0x7f,
  ASCII_MIN_PRINTABLE = 0x20,
} ascii_defs_t;

#define ASCII_NULL 0
#define ASCII_SOH ASCII_CTRL_A // Start of Heading
#define ASCII_STX ASCII_CTRL_B // Start of Text
#define ASCII_ETX ASCII_CTRL_C // End of Text
#define ASCII_EOT ASCII_CTRL_D // End of Transmission
#define ASCII_ENQ ASCII_CTRL_E // Enquiry
#define ASCII_ACK ASCII_CTRL_F // Acknlowledge
#define ASCII_BEL ASCII_CTRL_G // Bell
#define ASCII_BS ASCII_CTRL_H  // Backspace
#define ASCII_TAB ASCII_CTRL_I // Horizontal Tab
#define ASCII_LF ASCII_CTRL_J  // Line Feed
#define ASCII_VT ASCII_CTRL_K  // Vertical Tab
#define ASCII_FF ASCII_CTRL_L  // Form Feed
#define ASCII_CR ASCII_CTRL_M  // Carriage Return
#define ASCII_SO ASCII_CTRL_N  // Shift Out
#define ASCII_SI ASCII_CTRL_O  // Shift In
#define ASCII_DLE ASCII_CTRL_P // Data Link Escape
#define ASCII_DC1 ASCII_CTRL_Q // Device Control 1
#define ASCII_DC2 ASCII_CTRL_R // Device Control 2
#define ASCII_DC3 ASCII_CTRL_S // Device Control 3
#define ASCII_DC4 ASCII_CTRL_T // Device Control 4
#define ASCII_NAK ASCII_CTRL_U // Negative Acknlowledge
#define ASCII_SYN ASCII_CTRL_V // Synchronous Idle
#define ASCII_ETB ASCII_CTRL_W // End of Transmission Block
#define ASCII_CAN ASCII_CTRL_X // Cancel
#define ASCII_EM ASCII_CTRL_Y  // End of Medium
#define ASCII_SUB ASCII_CTRL_Z // Substitute
#define ASCII_ESC 0x1b


#define ASCII_
#endif // !defined (ASDF_ASCII_H)

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
