// File recommented by recomment.cpp
// on Dec  9 2019 at 10:14:05.
//
// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
//  Universal Keyboard Project
//  ASDF firmware - small, fast, and simple keyboard encoder.
//
//  asdf.c
//
// This file contains code for:
// - the main scan code and key handler routines
// - key matrix declarations and keyboard state variables not delegated
//   elsewhere.
// - Key debouncing logic and data stuctures
// - dispatch of special functions bound to keys.
//
// Copyright 2019 David Fenyes
//
//  This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any
// later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <https://www.gnu.org/licenses/>.

#include <stdint.h>
#include "asdf.h"
#include "asdf_ascii.h"
#include "asdf_physical.h"
#include "asdf_virtual.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"
#include "asdf_repeat.h"
#include "asdf_modifiers.h"
#include "asdf_buffer.h"
#include "asdf_arch.h"

static asdf_cols_t last_stable_key_state[ASDF_NUM_ROWS];

// Each key is debounced separately, supporting true N-key rollover, allowing a
// new key to be pressed when the previously pressed key is still debouncing.
// This requires a debounce counter for each key. This is is a large RAM
// footprint, 64 bytes for an 8 x 8 key matrix. It would be possible to only
// debounce the most recently pressed key and reduce the RAM usage to a single
// debounce counuter. However, this would probably require different handling of
// key presses and releases, and special handling for modifier keys, perhaps
// including separate debounce logic in the handlers for toggle keys such as
// CAPS_LOCK.
static uint8_t debounce_counters[ASDF_NUM_ROWS][ASDF_NUM_COLS];

// store the last key pressed
static asdf_keycode_t last_key;

// handle for the char output buffer
static asdf_buffer_handle_t asdf_keycode_buffer;


// PROCEDURE: asdf_put_code
// INPUTS: (asdf_keycode_t) code: code to be buffered for output
// OUTPUTS: none
//
// DESCRIPTION: Takes a keycode argument and buffers for output.
//
// SIDE EFFECTS: modifies buffer state.
//
// NOTES: If buffer is full, silently drop the code.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_put_code(asdf_keycode_t code)
{
  asdf_buffer_put(asdf_keycode_buffer, code);
}

// PROCEDURE: asdf_next_code
// INPUTS: none
// OUTPUTS: (asdf_keycode_t) returns next value in buffer.
//
// DESCRIPTION: Takes a keycode argument and buffers for output.
//
// SIDE EFFECTS: modifies buffer state.
//
// NOTES: If buffer is full, silently drop the code.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
asdf_keycode_t asdf_next_code(void)
{
  return asdf_buffer_get(asdf_keycode_buffer);
}

// PROCEDURE: asdf_lookup_keycode
// INPUTS: row, col: specify a row and column in the keyboard matrix
// OUTPUTS: returns a keycode
//
// DESCRIPTION: Given a row and column in the keyboard matrix, returns the
// corresponding keycode, depending on the state of the modifier keys.
//
// SIDE EFFECTS: none
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 1
//
asdf_keycode_t asdf_lookup_keycode(uint8_t row, uint8_t col)
{
  return asdf_keymaps_get_code(row, col, asdf_modifier_index());
}

// PROCEDURE: asdf_activate_action
// INPUTS: keycode: an action key code
// OUTPUTS: none
//
// DESCRIPTION: This routine is called when a key bound to an action code is
// pressed, and maps the action code to a function call, or other action
// appropriate for activation of the function.
//
// SIDE EFFECTS: All the actions may have side effects, depending on the function called.
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_activate_action(action_t keycode)
{
  switch (keycode) {

    case ACTION_SHIFT: {
      asdf_modifier_shift_activate();
      break;
    }
    case ACTION_SHIFT_LOCK: {
      asdf_modifier_shiftlock_activate();
      break;
    }
    case ACTION_CAPS: {
      asdf_modifier_capslock_activate();
      break;
    }
    case ACTION_CTRL: {
      asdf_modifier_ctrl_activate();
      break;
    }
    case ACTION_REPEAT: {
      asdf_repeat_activate();
      break;
    }
    case ACTION_MAPSEL_0: {
      asdf_keymaps_map_select_0_set();
      break;
    }
    case ACTION_MAPSEL_1: {
      asdf_keymaps_map_select_1_set();
      break;
    }
    case ACTION_MAPSEL_2: {
      asdf_keymaps_map_select_2_set();
      break;
    }
    case ACTION_MAPSEL_3: {
      asdf_keymaps_map_select_3_set();
      break;
    }
    case ACTION_VLED1: {
      asdf_virtual_activate(VLED1);
      break;
    }
    case ACTION_VLED2: {
      asdf_virtual_activate(VLED2);
      break;
    }
    case ACTION_VLED3: {
      asdf_virtual_activate(VLED3);
      break;
    }
    case ACTION_VOUT1: {
      asdf_virtual_activate(VOUT1);
      break;
    }
    case ACTION_VOUT2: {
      asdf_virtual_activate(VOUT2);
      break;
    }
    case ACTION_VOUT3: {
      asdf_virtual_activate(VOUT3);
      break;
    }
    case ACTION_VOUT4: {
      asdf_virtual_activate(VOUT4);
      break;
    }
    case ACTION_VOUT5: {
      asdf_virtual_activate(VOUT5);
      break;
    }
    case ACTION_VOUT6: {
      asdf_virtual_activate(VOUT6);
      break;
    }
    case ACTION_NOTHING:
    case ACTION_HERE_IS:
    case ACTION_FN_1:
    case ACTION_FN_2:
    case ACTION_FN_3:
    case ACTION_FN_4:
    case ACTION_FN_5:
    case ACTION_FN_6:
    case ACTION_FN_7:
    case ACTION_FN_8:
    case ACTION_FN_9:
    case ACTION_FN_10:
    default: break;
  }
}

// PROCEDURE: asdf_deactivate_action
// INPUTS: keycode: an action key code
// OUTPUTS: none
//
// DESCRIPTION: This routine is called when a key bound to an action code is
// released, and maps the action code to a function call, or other action
// appropriate for deactivation of the function.
//
// SIDE EFFECTS: All the actions may have side effects, depending on the function called.
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_deactivate_action(action_t keycode)
{
  switch (keycode) {
    case ACTION_SHIFT: {
      asdf_modifier_shift_deactivate();
      break;
    }
    case ACTION_SHIFT_LOCK: {
      asdf_modifier_shiftlock_deactivate();
      break;
    }
    case ACTION_CAPS: {
      asdf_modifier_capslock_deactivate();
      break;
    }

    case ACTION_CTRL: {
      asdf_modifier_ctrl_deactivate();
      break;
    }
    case ACTION_REPEAT: {
      asdf_repeat_deactivate();
      break;
    }
    case ACTION_MAPSEL_0: {
      asdf_keymaps_map_select_0_clear();
      break;
    }
    case ACTION_MAPSEL_1: {
      asdf_keymaps_map_select_1_clear();
      break;
    }
    case ACTION_MAPSEL_2: {
      asdf_keymaps_map_select_2_clear();
      break;
    }
    case ACTION_MAPSEL_3: {
      asdf_keymaps_map_select_3_clear();
      break;
    }
    case ACTION_NOTHING:
    case ACTION_HERE_IS:
    case ACTION_FN_1:
    case ACTION_FN_2:
    case ACTION_FN_3:
    case ACTION_FN_4:
    case ACTION_FN_5:
    case ACTION_FN_6:
    case ACTION_FN_7:
    case ACTION_FN_8:
    case ACTION_FN_9:
    case ACTION_FN_10:
    default: break;
  }
}

// PROCEDURE: asdf_activate_key
// INPUTS: keycode - the code for a key that has been pressed.
// OUTPUTS: none
//
// DESCRIPTION: Called when a key has been pressed. If the key is bound to a
// value, output the value. If the key is bound to an action, call the activate action
// handler with the keycode.
//
// SIDE EFFECTS: If the code is a value, the last key is updated to the current
// value, and repeat timer is reset. If the code is an action code, the activate
// action dispatcher produces side effects.  See asdf_activate_action()
//
// SCOPE: private
//
// COMPLEXITY: 2
//
static void asdf_activate_key(asdf_keycode_t keycode)
{
  if (keycode & ASDF_ACTION) {
    asdf_activate_action((action_t) keycode);
  }
  else {

    // activate a new codable keypress
    asdf_put_code(keycode);
    if (last_key != keycode) {
      last_key = keycode;
      asdf_repeat_reset_count();
    }
  }
}

// PROCEDURE: asdf_deactivate_key
// INPUTS: keycode - the code for a key that has been released
// OUTPUTS: none
//
// DESCRIPTION: Called when a key has been released. If the key is bound to a
// value, output the value. If the key is bound to an action, call the deactivate
// action handler with the keycode.
//
// SIDE EFFECTS: If the code is a value, the last key is set to ACTION_NOTHING,
// which is effectively a NOP. If the code is an action code, the deactivate action
// dispatcher produces side effects. See asdf_deactivate_action()
//
// SCOPE: private
//
// COMPLEXITY: 2
//
static void asdf_deactivate_key(asdf_keycode_t keycode)
{
  if (keycode & ASDF_ACTION) {
    asdf_deactivate_action((action_t) keycode);
  }
  else {

    // deactivate a released keypress
    if (last_key == keycode) {
      last_key = ACTION_NOTHING;
    }
  }
}

// PROCEDURE: asdf_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Reserve an output buffer to hold keycodes to be sent, and
// initialize the keyboard state and debounce counters
//
// SIDE EFFECTS: see DESCRIPTION
//
// SCOPE: public
//
// COMPLEXITY: 3
//
void asdf_init(void)
{

  last_key = ACTION_NOTHING;

  asdf_modifiers_init();
  asdf_repeat_init();
  asdf_keymaps_init();
  asdf_buffer_init();

  // reserve a buffer:
  asdf_keycode_buffer = asdf_buffer_new(ASDF_KEYCODE_BUFFER_SIZE);

  for (uint8_t row = 0; row < ASDF_NUM_ROWS; row++) {
    last_stable_key_state[row] = 0;
    for (uint8_t col = 0; col < ASDF_NUM_COLS; col++) {
      debounce_counters[row][col] = ASDF_DEBOUNCE_TIME_MS;
    }
  }
}

// PROCEDURE: asdf_handle_key_press_or_release
// INPUTS: row, col: the row and column number of the key that has changed.
// OUTPUTS: none
//
// DESCRIPTION: Given a row and column of a key that has changed:
//
// 1) Debounce the key by decrementing a debounce timer. If not yet debounced,
//    return.
// 2) When the key is debounced, if the key is pressed, then call the activation
//    function associated with the key. Otherwise, if the key is released, call
//    the deactivation function for the key.
//
// SIDE EFFECTS: - Modifies debounce counter for the row and column
//               - After key debounces, modifies the table of stable key states
//               - Activate/deactivate functions have side effects
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 3
//
static void asdf_handle_key_press_or_release(uint8_t row, uint8_t col, uint8_t key_was_pressed)
{
  uint8_t *debounce_count = &debounce_counters[row][col];

  if (!(--(*debounce_count))) {

    // debounce timed out. Set new stable state and activate or

    // deactivate key.
    *debounce_count = ASDF_DEBOUNCE_TIME_MS;
    if (key_was_pressed) {
      last_stable_key_state[row] |= 1 << col;
      asdf_activate_key(asdf_lookup_keycode(row, col));
    }
    else {
      // key was released

      last_stable_key_state[row] &= ~(1 << col);
      asdf_deactivate_key(asdf_lookup_keycode(row, col));
    }
  }
}

// PROCEDURE: asdf_handle_key_held_pressed
// INPUTS: row, col: The row and column of a key that is being held down
// OUTPUTS: none
//
// DESCRIPTION: Given a row and column of a key that has been debounced and
// continues to be pressed:
// 1) Determine if this is the last key pressed.
// 2) If it's the most recent key, then check to see if it's time to repeat the key code.
// 3) If it's time to repeat, then do the repeat and reset the repeat timer.
//
// SIDE EFFECTS:
// - Causes repeat timer to tick, and may reset the repeat timer.
// - activate_key() will send a key code.
//
// NOTES: last_key is always a key code, never an action function, so only valid
// key codes will be repeated.
//
// SCOPE: private
//
// COMPLEXITY: 3
//
static void asdf_handle_key_held_pressed(uint8_t row, uint8_t col)
{
  if (asdf_lookup_keycode(row, col) == last_key) {

    // if last debounced code-producing key is still pressed, handle repeat
    if (asdf_repeat()) {
      asdf_activate_key(last_key);
    }
  }
}

// PROCEDURE: asdf_keyscan
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Scans the key matrix. For each row, read the columns and compare
// with last stable state. For each changed key, call a key-change handler
// function. For each stable pressed key, call a "continued press" handler
// function.
//
// SIDE EFFECTS:
//
// NOTES: 1) The keyboard state is stored as an array of words, with one word
//           per row, and each bit in a word representing one key in the row.
//
//        2) While it is tempting to use bit hacks to reduce the number of
//           cycles through the inner loop, I have opted to just loop over all
//           the bits (as long as there are some changed or pressed keys). For
//           an 8-bit word, bit tricks don't deliver much performance boost,
//           but do decrease code clarity.
//
// COMPLEXITY: 5
//
void asdf_keyscan(void)
{
  for (uint8_t row = 0; row < ASDF_NUM_ROWS; row++) {
    asdf_cols_t row_key_state = asdf_arch_read_row(row);
    asdf_cols_t changed = row_key_state ^ last_stable_key_state[row];

    // loop over the bits until all changed or pressed keys in the row are handled.
    for (uint8_t col = 0; (changed | row_key_state) && col < ASDF_NUM_COLS; col++) {
      if (changed & 1) {
        // key state is different from last stable state
        asdf_handle_key_press_or_release(row, col, row_key_state & 1);
      }
      else if (row_key_state & 1) {
        asdf_handle_key_held_pressed(row, col);
      }
      changed >>= 1;
      row_key_state >>= 1;
    }
  }
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
