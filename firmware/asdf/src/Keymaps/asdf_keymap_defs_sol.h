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

#if !defined(ASDF_KEYMAP_DEFS_SOL20_H)
#define ASDF_KEYMAP_DEFS_SOL20_H

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
#define SOL_KBD_VIRTUAL_SUB1(SOL_VDEVICE) ACTION_##SOL_VDEVICE
#define SOL_KBD_VIRTUAL_SUB(SOL_VDEVICE) SOL_KBD_VIRTUAL_SUB1(SOL_VDEVICE)
#define SOL_KBD_LOCAL_ACTION SOL_KBD_VIRTUAL_SUB(SOL_KBD_VLOCAL)

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

#define ASDF_SOL_KEYMAP_INITIALIZER_LENGTH 6

// Notice that TTLOUT_LOCAL (OUT3) and LED_LOCAL (PHYSICAL_LED2) are both bound
// to the VLOCAL_OUT virtual device.
#define ASDF_SOL_KEYMAP_INITIALIZER                                                                \
  {                                                                                                \
    { .virtual_device = VCAPS_LED,                                                                 \
      .physical_device = SOL_KBD_LED_UPPERCASE,                                                    \
      .initial_value = SOL_KBD_LED_OFF },                                                           \
      { .virtual_device = VSHIFT_LED,                                                              \
        .physical_device = SOL_KBD_LED_SHIFTLOCK,                                                  \
        .initial_value = SOL_KBD_LED_OFF },                                                        \
      { .virtual_device = SOL_KBD_VLOCAL,                                                          \
        .physical_device = SOL_KBD_TTLOUT_LOCAL,                                                   \
        .function = V_TOGGLE,                                                                      \
        .initial_value = SOL_KBD_TTL_HIGH },                                                       \
      { .virtual_device = SOL_KBD_VLOCAL,                                                          \
        .physical_device = SOL_KBD_LED_LOCAL,                                                      \
        .function = V_TOGGLE,                                                                      \
        .initial_value = SOL_KBD_LED_OFF },                                                        \
      { .virtual_device = SOL_KBD_VRESET,                                                          \
        .physical_device = SOL_KBD_TTLOUT_RESET,                                                   \
        .function = V_PULSE_SHORT,                                                                 \
        .initial_value = SOL_KBD_TTL_HIGH },                                                       \
      { .virtual_device = SOL_KBD_VBREAK,                                                          \
        .physical_device = SOL_KBD_TTLOUT_BREAK,                                                   \
        .function = V_PULSE_LONG,                                                                  \
        .initial_value = SOL_KBD_TTL_HIGH },                                                       \
  }

// function hooks for the SOL keyboard. At Setup, activate CAPSLOCK to emulate
// original keyboard.
#define ASDF_SOL_KEYMAP_HOOK_INITIALIZER_LENGTH 1
#define ASDF_SOL_KEYMAP_HOOK_INITIALIZER                                                           \
  {                                                                                                \
    {                                                                                              \
      .hook_id = ASDF_HOOK_KEYMAP_SETUP,                                                           \
      .hook_func = asdf_modifier_capslock_activate,                                                \
    },                                                                                             \
  }

#define ASDF_SOL_DIP_SWITCHES                                                                      \
  [ASDF_ARCH_DIPSWITCH_ROW] = { ACTION_MAPSEL_0, ACTION_MAPSEL_1, ACTION_MAPSEL_2, ACTION_MAPSEL_3 }

// clang-format off
#define ASDF_SOL_PLAIN_MAP                                              \
  {                                                                     \
    [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, 'a', 's', 'd', 'f', 'g', 'h' }, \
    [1] = { 'j', 'k', 'l', ';', ':', ASCII_DEL, ACTION_REPEAT, ACTION_CTRL }, \
    [2] = { ACTION_CAPS, ACTION_SHIFT, 'z', 'x', 'c', 'v', 'b', 'n' },  \
    [3] = { 'm',          ASCII_COMMA,           ASCII_PERIOD,   '/',   \
            ACTION_SHIFT, SOL_ASCII_MODE_SELECT, ACTION_NOTHING, ACTION_NOTHING }, \
    [4] = { ASCII_ESC, '1', '2', '3', '4', '5', '6', '7' }, /**/          \
    [5] = { '8', '9', ASCII_ZERO, '-', '^',                             \
            ASCII_LT_SQUARE_BRACE, ASCII_BACKSLASH, ASCII_RT_SQUARE_BRACE }, \
    [6] = { SOL_KBD_VBREAK, ASCII_TAB, 'q', 'w', 'e', 'r', 't', 'y' }, /**/     \
    [7] = { 'u', 'i', 'o', 'p', ASCII_AT, ASCII_CR, ASCII_LF, SOL_ASCII_LOAD }, \
    [9] = { SOL_KBD_LOCAL_ACTION,         SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW,     \
            ASCII_SPACE,    SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW,     \
            SOL_ASCII_HOME, SOL_ASCII_CLEAR },                          \
    [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING }, \
    [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING }, \
    [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING,                    \
             ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING }, \
    ASDF_SOL_DIP_SWITCHES,                                              \
  }

#define ASDF_SOL_CAPS_MAP                                               \
  {                                                                     \
    [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, 'A', 'S', 'D', 'F', 'G', 'H' }, \
    [1] = { 'J', 'K', 'L', ';', ':', ASCII_DEL, ACTION_REPEAT, ACTION_CTRL }, \
    [2] = { ACTION_CAPS, ACTION_SHIFT, 'Z', 'X', 'C', 'V', 'B', 'N' },  \
    [3] = { 'M',          ASCII_COMMA,           ASCII_PERIOD,   '/',   \
            ACTION_SHIFT, SOL_ASCII_MODE_SELECT, ACTION_NOTHING, ACTION_NOTHING }, \
    [4] = { ASCII_ESC, '1', '2', '3', '4', '5', '6', '7' }, /**/          \
    [5] = { '8', '9', ASCII_ZERO, '-', '^',                             \
            ASCII_LT_SQUARE_BRACE, ASCII_BACKSLASH, ASCII_RT_SQUARE_BRACE }, \
    [6] = { SOL_KBD_VBREAK, ASCII_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y' }, /**/     \
    [7] = { 'U', 'I', 'O', 'P', ASCII_AT, ASCII_CR, ASCII_LF, SOL_ASCII_LOAD }, \
    [9] = { SOL_KBD_LOCAL_ACTION,         SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW,     \
            ASCII_SPACE,    SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW,     \
            SOL_ASCII_HOME, SOL_ASCII_CLEAR },                          \
    [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING }, \
    [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING }, \
    [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING,                    \
             ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING }, \
    ASDF_SOL_DIP_SWITCHES,                                              \
  }

#define ASDF_SOL_SHIFT_MAP                                              \
  {                                                                     \
    [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, 'A', 'S', 'D', 'F', 'G', 'H' }, \
    [1] = { 'J', 'K', 'L', ';', ':', ASCII_UNDERSCORE, ACTION_REPEAT, ACTION_CTRL }, \
    [2] = { ACTION_CAPS, ACTION_SHIFT, 'Z', 'X', 'C', 'V', 'B', 'N' },  \
    [3] = { 'M',          '<',           '>',   '?',   \
            ACTION_SHIFT, SOL_ASCII_MODE_SELECT, ACTION_NOTHING, ACTION_NOTHING }, \
    [4] = { ASCII_ESC, '!', ASCII_DOUBLE_QUOTE, '#', '$', '%', '&', ASCII_SINGLE_QUOTE }, \
    [5] = { ASCII_LT_PAREN, ASCII_RT_PAREN, ASCII_SPACE, '=', ASCII_TILDE,                             \
            ASCII_LT_SQUARE_BRACE, ASCII_BACKSLASH, ASCII_RT_SQUARE_BRACE }, \
    [6] = { SOL_KBD_VBREAK, ASCII_TAB, 'Q', 'W', 'E', 'R', 'T', 'Y' },          \
    [7] = { 'U', 'I', 'O', 'P', ASCII_GRAVE_ACCENT, ASCII_CR, ASCII_LF, SOL_ASCII_LOAD }, \
    [9] = { SOL_KBD_LOCAL_ACTION,         SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW,     \
            ASCII_SPACE,    SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW,     \
            SOL_ASCII_HOME, SOL_ASCII_CLEAR },                          \
    [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING }, \
    [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING }, \
    [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING,                    \
             ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING }, \
    ASDF_SOL_DIP_SWITCHES,                                              \
  }

#define ASDF_SOL_CTRL_MAP                                               \
  {                                                                     \
    [0] = { ACTION_CTRL, SOL_KBD_SHIFTLOCK_ACTION, ASCII_CTRL_A, ASCII_CTRL_S, \
            ASCII_CTRL_D, ASCII_CTRL_F, ASCII_CTRL_G, ASCII_CTRL_H },       \
    [1] = { ASCII_CTRL_J, ASCII_CTRL_K, ASCII_CTRL_L, ASCII_VT,         \
            ASCII_LF, ASCII_DEL, ACTION_REPEAT, ACTION_CTRL },          \
    [2] = { ACTION_CAPS, ACTION_SHIFT, ASCII_CTRL_Z, ASCII_CTRL_X, \
            ASCII_CTRL_C, ASCII_CTRL_V, ASCII_CTRL_B, ASCII_CTRL_N },                                       \
    [3] = { ASCII_CTRL_M, ASCII_FF, ASCII_SO,   ASCII_SI,   \
            ACTION_SHIFT, SOL_ASCII_MODE_SELECT, ACTION_NOTHING, ACTION_NOTHING }, \
    [4] = { ASCII_ESC, ASCII_SOH, ASCII_STX, ASCII_ETX,                 \
            ASCII_EOT, ASCII_ENQ, ASCII_ACK, ASCII_BEL },               \
    [5] = { ASCII_BS, ASCII_TAB, ASCII_NULL, ASCII_CR, ASCII_RS,        \
            ASCII_ESC, ASCII_FS, ASCII_GS },                            \
    [6] = { SOL_KBD_VBREAK, ASCII_TAB, ASCII_CTRL_Q, ASCII_CTRL_W,              \
            ASCII_CTRL_E, ASCII_CTRL_R, ASCII_CTRL_T, ASCII_CTRL_Y },   \
    [7] = { ASCII_CTRL_U, ASCII_CTRL_I, ASCII_CTRL_O, ASCII_CTRL_P,     \
            ASCII_NULL, ASCII_CR, ASCII_LF, SOL_ASCII_LOAD },             \
    [9] = { SOL_KBD_LOCAL_ACTION,         SOL_ASCII_UP_ARROW, SOL_ASCII_LT_ARROW,     \
            ASCII_SPACE,    SOL_ASCII_RT_ARROW, SOL_ASCII_DN_ARROW,     \
            SOL_ASCII_HOME, SOL_ASCII_CLEAR },                          \
    [10] = { '-', '7', '*', '8', '/', '9', ACTION_NOTHING, ACTION_NOTHING }, \
    [11] = { '4', '1', '5', '2', '6', '3', ACTION_NOTHING, ACTION_NOTHING }, \
    [12] = { '0', ASCII_PERIOD, '+', ACTION_NOTHING,                    \
             ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING, ACTION_NOTHING }, \
    ASDF_SOL_DIP_SWITCHES,                                              \
  }

// clang-format on

#define ASDF_SOL_MAP_DECLARATIONS                                                                  \
  static const FLASH keycode_matrix_t asdf_sol_plain_matrix = ASDF_SOL_PLAIN_MAP;                  \
  static const FLASH keycode_matrix_t asdf_sol_shift_matrix = ASDF_SOL_SHIFT_MAP;                  \
  static const FLASH keycode_matrix_t asdf_sol_caps_matrix = ASDF_SOL_CAPS_MAP;                    \
  static const FLASH keycode_matrix_t asdf_sol_ctrl_matrix = ASDF_SOL_CTRL_MAP;


// Here, you can specify which maps are associated with which modifier keys.
// There can be multiple definitions. For example, as shown here, an ALL CAPS
// keymap can be made by assigning the caps map to the "no modifier" position.
// Or, more additional keymaps can be defined above, and keymap sets can be
// defined below that pick and choose between them.  The modifiers are assigned as follows:
//
// [0]: plain (no modifiers)
// [1]: shift (shift key or shift lock active)
// [2]: caps (caps lock active)
// [3]: ctrl: (control key active)

#define ASDF_SOL_MAP_DEFS                                                                          \
  {                                                                                                \
    [MOD_PLAIN_MAP] = &asdf_sol_plain_matrix, [MOD_SHIFT_MAP] = &asdf_sol_shift_matrix,            \
    [MOD_CAPS_MAP] = &asdf_sol_caps_matrix, [MOD_CTRL_MAP] = &asdf_sol_ctrl_matrix                 \
  }

#define ASDF_SOL_ALL_MAPS ASDF_SOL_MAP_DEFS

#define ASDF_SOL_ALL_MAPS_COUNT 1

#if !defined(ASDF_NUM_ROWS) || (ASDF_NUM_ROWS < ASDF_SOL_NUM_ROWS)
#undef ASDF_NUM_ROWS
#define ASDF_NUM_ROWS ASDF_SOL_NUM_ROWS
#endif

#if !defined(ASDF_NUM_COLS) || (ASDF_NUM_COLS < ASDF_SOL_NUM_COLS)
#undef ASDF_NUM_COLS
#define ASDF_NUM_COLS ASDF_SOL_NUM_COLS
#endif

#if !defined(ASDF_KEYMAP_INITIALIZER_LENGTH)                                                       \
  || (ASDF_KEYMAP_INITIALIZER_LENGTH < ASDF_SOL_KEYMAP_INITIALIZER_LENGTH)
#undef ASDF_KEYMAP_INITIALIZER_LENGTH
#define ASDF_KEYMAP_INITIALIZER_LENGTH ASDF_SOL_KEYMAP_INITIALIZER_LENGTH
#endif

#if !defined(ASDF_KEYMAP_HOOK_INITIALIZER_LENGTH)                                                  \
  || (ASDF_KEYMAP_HOOK_INITIALIZER_LENGTH < ASDF_SOL_KEYMAP_HOOK_INITIALIZER_LENGTH)
#undef ASDF_KEYMAP_HOOK_INITIALIZER_LENGTH
#define ASDF_KEYMAP_HOOK_INITIALIZER_LENGTH ASDF_SOL_KEYMAP_HOOK_INITIALIZER_LENGTH
#endif

#endif /* !defined (ASDF_KEYMAP_DEFS_SOL20_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
