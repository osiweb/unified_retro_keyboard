// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Universal Keyboard Project
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

typedef uint16_t key_timer_t;

static repeat_state_t repeat_state;
static repeat_state_t base_repeat_state;

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
  key_repeat_timer = (uint16_t) repeat_state;
}

// PROCEDURE: asdf_repeast_reset_count
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: resets the repeat counter for the current key, to begin a new
// repeat cycle.  Resest is based on repeat state (no repeat, autorepeat, normal repeat).
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_repeat_reset_count(void)
{
  key_repeat_timer = (key_timer_t) repeat_state;
}

// PROCEDURE: asdf_repeat_auto_off
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Turns Autorepeat mode off by setting the base state to
// autorepeat. If key is repeating, then the new behavior will be realized after
// the repeat key is released.
//
// SIDE EFFECTS: See DESCRIPTION
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_repeat_auto_off(void)
{
  base_repeat_state = REPEAT_OFF;
  if (REPEAT_ON != repeat_state) {
    key_repeat_timer = repeat_state = base_repeat_state;
  }
}

// PROCEDURE: asdf_repeat_auto_on
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Turns Autorepeat mode on by setting the base state to
// autorepeat. If key is repeating, then the new behavior will be realized after
// the repeat key is released.
//
// SIDE EFFECTS: see above
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_repeat_auto_on(void)
{
  base_repeat_state = REPEAT_AUTO;
  if (REPEAT_ON != repeat_state) {
    key_repeat_timer = repeat_state = base_repeat_state;
  }
}

// PROCEDURE: asdf_repeat_activate
// INPUTS: none
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
void asdf_repeat_activate(void)
{
  if (key_repeat_timer > REPEAT_ON || REPEAT_OFF == repeat_state) {
    key_repeat_timer = repeat_state = REPEAT_ON;
  }
}

// PROCEDURE: asdf_repeat_deactivate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Reset repeat state machine to default state. Called when REPEAT
// key is released.
//
// SIDE EFFECTS: See DESCRIPTION
//
// NOTES: Releasing repeat disrupts any repeat timers. aIf a key is still held
// down after REPEAT is released, and autorepeat mode is enabled, then restart
// the autorepeat timer. Otherwise disable repeat.
//
// COMPLEXITY: 1
//
void asdf_repeat_deactivate(void)
{
  key_repeat_timer = repeat_state = base_repeat_state;
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

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
