// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_repeat.c
//
// This file contains the key repeat logic.
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

#include <stdint.h>
#include "asdf_repeat.h"

// This module keeps track of a single repeat event. It is non-reentrant. This
// makes sense for a single keyboard, since only one key can repeat at any given
// time.
//


// counters for key repeat timing are 16-bit unsigned
typedef uint16_t key_timer_t;

// The "State" of the repeat logic is the current repeat rate. This is the value
// loaded into the repeat timer when in repeat mode (autorepeat or repeat key)
// and a key is pressed.
//
// If the base state is REPEAT_OFF, then key repetition only occurs when the
// REPEAT key is pressed along with a "code" key.
//
// If the base state is REPEAT_AUTO, then key repetition occurs when the REPEAT
// key is pressed with a "code" key , or when a "code" key is held for the
// autorepeat delay.
//
// Obviously, the base state is never REPEAT_ON, which would instantly repeat
// any key when pressed.
typedef enum {
  REPEAT_OFF = 0,                        // no repeat
  REPEAT_ON = ASDF_REPEAT_TIME_MS,       // currently repeating
  REPEAT_AUTO = ASDF_AUTOREPEAT_TIME_MS, // wait for autorepeat delay, then start repeating
} repeat_state_t;

// Contains the current repeat state
static repeat_state_t repeat_state;

// Contains the baseline repeat state (either no repeat or autorepeat). When a
// key is released, or when the repeat key is released, the repeat state is
// reset to this value.
static repeat_state_t base_repeat_state;

// The repeat timer counts down to the next repeat event
static key_timer_t key_repeat_timer;


// PROCEDURE: asdf_repeat_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize the repeat state state machine
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_repeat_init(void)
{
  repeat_state = base_repeat_state = ASDF_DEFAULT_REPEAT_STATE;
  key_repeat_timer = (key_timer_t) repeat_state;
}

// PROCEDURE: asdf_repeast_reset_count
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: resets the repeat counter for the current key, to begin a new
// repeat cycle. The counter is reset to the countdown value for the current
// state (no repeat, autorepeat, normal repeat).
//
// SIDE EFFECTS: see DESCRIPTION
//
// SCOPE: Public
//
// COMPLEXITY: 1
//
void asdf_repeat_reset_count(void)
{
  key_repeat_timer = (key_timer_t) repeat_state;
}


// PROCEDURE: asdf_repeat_activate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: set repeat state machine to repeat mode. Called when REPEAT key
// is pressed.
//
// SIDE EFFECTS: see DESCRIPTION
//
// NOTES: If a key is pressed and the key timer is less than or equal to the
// normal repeat rate, then don't change the timing, to avoid appearance of
// stuttering.
//
// COMPLEXITY: 1
//
void asdf_repeat_activate(uint8_t unused)
{
  (void) unused;
  if (key_repeat_timer > REPEAT_ON || REPEAT_OFF == repeat_state) {
    key_repeat_timer = repeat_state = REPEAT_ON;
  }
}

// PROCEDURE: asdf_repeat_deactivate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: Reset repeat state to default state. Called when REPEAT
// key is released.
//
// SIDE EFFECTS: See DESCRIPTION
//
// NOTES: Releasing repeat disrupts any repeat timers. If a key is still held
// down after REPEAT is released, and autorepeat mode is enabled, then restart
// the autorepeat timer. Otherwise disable repeat.
//
// SCOPE: Public
//
// COMPLEXITY: 1
//
void asdf_repeat_deactivate(uint8_t unused)
{
  (void) unused;
  key_repeat_timer = repeat_state = base_repeat_state;
}

uint8_t asdf_repeat_is_autorepeat_enabled(void)
{
  return (base_repeat_state == REPEAT_AUTO);
}

// PROCEDURE: asdf_repeat
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: counts down the repeat timer (if activated) and returns a TRUE
// value when the counter times out. A true values indicates that the last value
// should be repeated to the output.
//
// SIDE EFFECTS: none
//
// NOTES: The key_repeat_timer is only decremented if it is nonzero.
//
// SCOPE: Public
//
// COMPLEXITY: 2
//
uint8_t asdf_repeat(void)
{
  uint8_t timeout = (key_repeat_timer && !(--key_repeat_timer));

  if (timeout) {
    key_repeat_timer = REPEAT_ON;
  }

  return timeout;
}

// PROCEDURE: asdf_repeat_auto_on
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: Enables auto-repeat mode. Used as activate function for
// ACTION_AUTOREPEAT_SELECT DIP switch.
//
// SIDE EFFECTS: Sets auto-repeat mode to enabled
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_repeat_auto_on(uint8_t unused)
{
  (void) unused;
  base_repeat_state = REPEAT_AUTO;
  if (REPEAT_ON != repeat_state) {
    key_repeat_timer = repeat_state = base_repeat_state;
  }
}

// PROCEDURE: asdf_repeat_auto_off
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: Disables auto-repeat mode. Used as deactivate function for
// ACTION_AUTOREPEAT_SELECT DIP switch.
//
// SIDE EFFECTS: Sets auto-repeat mode to disabled
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_repeat_auto_off(uint8_t unused)
{
  (void) unused;
  base_repeat_state = REPEAT_OFF;
  if (REPEAT_ON != repeat_state) {
    key_repeat_timer = repeat_state = base_repeat_state;
  }
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
