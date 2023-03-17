// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_classic_add_map.h
//
// defines keymap matrices and add_map() function for the Franklin ACE 1000
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

#if !defined(ASDF_KEYMAP_ACE1000_ADD_MAP_H)
#define ASDF_KEYMAP_ACE1000_ADD_MAP_H

#include "asdf_modifiers.h"

typedef enum {
  ACE1000_PLAIN_MAP,
  ACE1000_CAPS_MAP,
  ACE1000_SHIFT_MAP,
  ACE1000_CTRL_MAP,
} ace1000_map_index_t;


// function prototypes
void ace1000_add_map(const ace1000_map_index_t map_index, modifier_index_t modifier_index);
void ace1000_keyboard_test(void);

// Key value definitions
#define ACE_KEY_0	0x30
#define ACE_KEY_1	0x31
#define ACE_KEY_2	0x32
#define ACE_KEY_3	0x33
#define ACE_KEY_4	0x34
#define ACE_KEY_5	0x35
#define ACE_KEY_6	0x36
#define ACE_KEY_7	0x37
#define ACE_KEY_8	0x38
#define ACE_KEY_9	0x39
#define ACE_KEY_A	0x61
#define ACE_KEY_B	0x62
#define ACE_KEY_BREAK	0x03
#define ACE_KEY_C	0x63
#define ACE_KEY_COMMA	0x2c
#define ACE_KEY_CTRL_0	0x30
#define ACE_KEY_CTRL_1	0x31
#define ACE_KEY_CTRL_2	0x32
#define ACE_KEY_CTRL_3	0x33
#define ACE_KEY_CTRL_4	0x34
#define ACE_KEY_CTRL_5	0x35
#define ACE_KEY_CTRL_6	0x36
#define ACE_KEY_CTRL_7	0x37
#define ACE_KEY_CTRL_8	0x38
#define ACE_KEY_CTRL_9	0x39
#define ACE_KEY_CTRL_A	0x01
#define ACE_KEY_CTRL_B	0x02
#define ACE_KEY_CTRL_BREAK	0x03
#define ACE_KEY_CTRL_C	0x03
#define ACE_KEY_CTRL_COMMA	0x2c
#define ACE_KEY_CTRL_CURLY	0x7b
#define ACE_KEY_CTRL_D	0x04
#define ACE_KEY_CTRL_E	0x05
#define ACE_KEY_CTRL_ESC	0x1b
#define ACE_KEY_CTRL_F	0x06
#define ACE_KEY_CTRL_G	0x07
#define ACE_KEY_CTRL_H	0x08
#define ACE_KEY_CTRL_I	0x09
#define ACE_KEY_CTRL_J	0x0a
#define ACE_KEY_CTRL_K	0x0b
#define ACE_KEY_CTRL_L	0x0c
#define ACE_KEY_CTRL_LEFT	0x08
#define ACE_KEY_CTRL_M	0x0d
#define ACE_KEY_CTRL_N	0x0e
#define ACE_KEY_CTRL_NUM_0	0x30
#define ACE_KEY_CTRL_NUM_1	0x31
#define ACE_KEY_CTRL_NUM_2	0x32
#define ACE_KEY_CTRL_NUM_3	0x33
#define ACE_KEY_CTRL_NUM_4	0x34
#define ACE_KEY_CTRL_NUM_5	0x35
#define ACE_KEY_CTRL_NUM_6	0x36
#define ACE_KEY_CTRL_NUM_7	0x37
#define ACE_KEY_CTRL_NUM_8	0x38
#define ACE_KEY_CTRL_NUM_9	0x39
#define ACE_KEY_CTRL_GT	0x3e
#define ACE_KEY_CTRL_MINUS	0x2d
#define ACE_KEY_CTRL_SPLAT	0x2a
#define ACE_KEY_CTRL_NUM_PERIOD	0x2e
#define ACE_KEY_CTRL_NUM_PLUS	0x2b
#define ACE_KEY_CTRL_O	0x0f
#define ACE_KEY_CTRL_P	0x10
#define ACE_KEY_RETURN 0x0d
#define ACE_KEY_CTRL_PAUSE	0x13
#define ACE_KEY_CTRL_PERIOD	0x2e
#define ACE_KEY_CTRL_PLUS	0x3d
#define ACE_KEY_CTRL_Q	0x11
#define ACE_KEY_CTRL_SLASH	0x2f
#define ACE_KEY_CTRL_QUOTE	0x27
#define ACE_KEY_CTRL_R	0x12
#define ACE_KEY_CTRL_RIGHT	0x15
#define ACE_KEY_CTRL_S	0x13
#define ACE_KEY_CTRL_SEMI	0x3b
#define ACE_KEY_CTRL_SPACE	0x20
#define ACE_KEY_CTRL_SQUARE	0x1d
#define ACE_KEY_CTRL_T	0x14
#define ACE_KEY_CTRL_TAB	0x09
#define ACE_KEY_CTRL_U	0x15
#define ACE_KEY_CTRL_UNDERSCORE	0x3d
#define ACE_KEY_CTRL_V	0x16
#define ACE_KEY_CTRL_W	0x17
#define ACE_KEY_CTRL_X	0x18
#define ACE_KEY_CTRL_Y	0x19
#define ACE_KEY_CTRL_Z	0x1a
#define ACE_KEY_CURLY	0x7b
#define ACE_KEY_D	0x64
#define ACE_KEY_E	0x65
#define ACE_KEY_ESC	0x1b
#define ACE_KEY_F	0x66
#define ACE_KEY_G	0x67
#define ACE_KEY_H	0x68
#define ACE_KEY_I	0x69
#define ACE_KEY_J	0x6a
#define ACE_KEY_K	0x6b
#define ACE_KEY_L	0x6c
#define ACE_KEY_LEFT	0x08
#define ACE_KEY_M	0x6d
#define ACE_KEY_N	0x6e
#define ACE_KEY_NUM_0	0x30
#define ACE_KEY_NUM_1	0x31
#define ACE_KEY_NUM_2	0x32
#define ACE_KEY_NUM_3	0x33
#define ACE_KEY_NUM_4	0x34
#define ACE_KEY_NUM_5	0x35
#define ACE_KEY_NUM_6	0x36
#define ACE_KEY_NUM_7	0x37
#define ACE_KEY_NUM_8	0x38
#define ACE_KEY_NUM_9	0x39
#define ACE_KEY_GT	0x3e
#define ACE_KEY_MINUS	0x2d
#define ACE_KEY_SPLAT	0x2a
#define ACE_KEY_NUM_PERIOD	0x2e
#define ACE_KEY_NUM_PLUS	0x2b
#define ACE_KEY_O	0x6f
#define ACE_KEY_P	0x70
#define ACE_KEY_PAUSE	0x13
#define ACE_KEY_PERIOD	0x2e
#define ACE_KEY_PLUS	0x3d
#define ACE_KEY_Q	0x71
#define ACE_KEY_SLASH	0x2f
#define ACE_KEY_QUOTE	0x27
#define ACE_KEY_R	0x72
#define ACE_KEY_RIGHT	0x15
#define ACE_KEY_S	0x73
#define ACE_KEY_SEMI	0x3b
#define ACE_KEY_SHIFT_0	0x29
#define ACE_KEY_SHIFT_1	0x21
#define ACE_KEY_SHIFT_2	0x40
#define ACE_KEY_SHIFT_3	0x23
#define ACE_KEY_SHIFT_4	0x24
#define ACE_KEY_SHIFT_5	0x25
#define ACE_KEY_SHIFT_6	0x5e
#define ACE_KEY_SHIFT_7	0x26
#define ACE_KEY_SHIFT_8	0x2a
#define ACE_KEY_SHIFT_9	0x28
#define ACE_KEY_SHIFT_A	0x41
#define ACE_KEY_SHIFT_B	0x42
#define ACE_KEY_SHIFT_BREAK	0x03
#define ACE_KEY_SHIFT_C	0x43
#define ACE_KEY_SHIFT_COMMA	0x3c
#define ACE_KEY_SHIFT_CURLY	0x7d
#define ACE_KEY_SHIFT_D	0x44
#define ACE_KEY_SHIFT_E	0x45
#define ACE_KEY_SHIFT_ESC	0x1b
#define ACE_KEY_SHIFT_F	0x46
#define ACE_KEY_SHIFT_G	0x47
#define ACE_KEY_SHIFT_H	0x48
#define ACE_KEY_SHIFT_I	0x49
#define ACE_KEY_SHIFT_J	0x4a
#define ACE_KEY_SHIFT_K	0x4b
#define ACE_KEY_SHIFT_L	0x4c
#define ACE_KEY_SHIFT_LEFT	0x08
#define ACE_KEY_SHIFT_M	0x4d
#define ACE_KEY_SHIFT_N	0x4e
#define ACE_KEY_SHIFT_NUM_0	0x30
#define ACE_KEY_SHIFT_NUM_1	0x31
#define ACE_KEY_SHIFT_NUM_2	0x32
#define ACE_KEY_SHIFT_NUM_3	0x33
#define ACE_KEY_SHIFT_NUM_4	0x34
#define ACE_KEY_SHIFT_NUM_5	0x35
#define ACE_KEY_SHIFT_NUM_6	0x36
#define ACE_KEY_SHIFT_NUM_7	0x37
#define ACE_KEY_SHIFT_NUM_8	0x38
#define ACE_KEY_SHIFT_NUM_9	0x39
#define ACE_KEY_SHIFT_GT	0x3e
#define ACE_KEY_SHIFT_MINUS	0x2d
#define ACE_KEY_SHIFT_SPLAT	0x2a
#define ACE_KEY_SHIFT_NUM_PERIOD	0x2e
#define ACE_KEY_SHIFT_NUM_PLUS	0x2b
#define ACE_KEY_SHIFT_O	0x4f
#define ACE_KEY_SHIFT_P	0x50
#define ACE_KEY_SHIFT_PAUSE	0x13
#define ACE_KEY_SHIFT_PERIOD	0x3e
#define ACE_KEY_SHIFT_PLUS	0x2b
#define ACE_KEY_SHIFT_Q	0x51
#define ACE_KEY_SHIFT_SLASH	0x3f
#define ACE_KEY_SHIFT_QUOTE	0x22
#define ACE_KEY_SHIFT_R	0x52
#define ACE_KEY_SHIFT_RIGHT	0x15
#define ACE_KEY_SHIFT_S	0x53
#define ACE_KEY_SHIFT_SEMI	0x3a
#define ACE_KEY_SHIFT_SPACE	0x20
#define ACE_KEY_SHIFT_SQUARE	0x5d
#define ACE_KEY_SHIFT_T	0x54
#define ACE_KEY_SHIFT_TAB	0x09
#define ACE_KEY_SHIFT_U	0x55
#define ACE_KEY_SHIFT_UNDERSCORE	0x5f
#define ACE_KEY_SHIFT_V	0x56
#define ACE_KEY_SHIFT_W	0x57
#define ACE_KEY_SHIFT_X	0x58
#define ACE_KEY_SHIFT_Y	0x59
#define ACE_KEY_SHIFT_Z	0x5A
#define ACE_KEY_SPACE	0x20
#define ACE_KEY_SQUARE	0x5b
#define ACE_KEY_T	0x74
#define ACE_KEY_TAB	0x09
#define ACE_KEY_U	0x75
#define ACE_KEY_UNDERSCORE	0x2d
#define ACE_KEY_V	0x76
#define ACE_KEY_W	0x77
#define ACE_KEY_X	0x78
#define ACE_KEY_Y	0x79
#define ACE_KEY_Z	0x7a

#endif /* !defined (ASDF_KEYMAP_ACE1000_ADD_MAP_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
