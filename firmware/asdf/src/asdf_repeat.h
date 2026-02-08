// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_repeat.h
//
// Copyright 2019 David Fenyes
//
// This program is free software: you can redistribute it and/or modify it
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
//
//

#if !defined(ASDF_REPEAT_H)
#define ASDF_REPEAT_H

#include "asdf_config.h"

// PROCEDURE: asdf_repeat_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Initialize the repeat state state machine
void asdf_repeat_init(void);

// PROCEDURE: asdf_repeast_reset_count
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: resets the repeat counter for the current key, to begin a new
// repeat cycle.  Resest is based on repeat state (no repeat, autorepeat, normal repeat).
void asdf_repeat_reset_count(void);

// PROCEDURE: asdf_repeat_auto_off
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Turns Autorepeat mode off
void asdf_repeat_auto_off(void);

// PROCEDURE: asdf_repeat_auto_on
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Turns Autorepeat mode on
void asdf_repeat_auto_on(void);

// PROCEDURE: asdf_repeat_is_autorepeat_enabled
// OUTPUTS: returns non-zero if autorepeat mode is enabled
uint8_t asdf_repeat_is_autorepeat_enabled(void);

// PROCEDURE: asdf_repeat_activate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: set repeat state machine to repeat mode. Called when REPEAT key
// is pressed.
void asdf_repeat_activate(void);

// PROCEDURE: asdf_repeat_deactivate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Reset repeat state machine to default state. Called when REPEAT
// key is released.
void asdf_repeat_deactivate(void);

// PROCEDURE: asdf_repeat
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: counts down the repeat timer (if activated) and returns a TRUE
// value when the counter times out. A true values indicates that the last value
// should be repeated to the output.
uint8_t asdf_repeat(void);

#endif // !defined (ASDF_REPEAT_H)

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
