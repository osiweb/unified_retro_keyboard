// File recommented by recomment.cpp
// on Dec  9 2019 at 10:14:05.
//
// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
//  Unfified Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_modifiers.h
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

#if !defined(ASDF_MODIFIERS_H)
#define ASDF_MODIFIERS_H

typedef enum { SHIFT_OFF_ST = 0, SHIFT_ON_ST = 0x01, SHIFT_LOCKED_ST = 0x02 } shift_state_t;
typedef enum { CAPS_OFF_ST = 0, CAPS_ON_ST = 0x02 } caps_state_t;
typedef enum { CTRL_OFF_ST = 0, CTRL_ON_ST = 0x04 } ctrl_state_t;
typedef enum {
  MOD_PLAIN_MAP = 0,
  MOD_SHIFT_MAP,
  MOD_CAPS_MAP,
  MOD_CTRL_MAP,
  MOD_NUM_MAPS
} modifier_index_t;

typedef enum { TOGGLE_SHIFTLOCK = 0, HOLD_SHIFTLOCK = 1 } shiftlock_mode_t;


// PROCEDURE: asdf_modifier_shift_activate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: sets SHIFT state to ON
//
void asdf_modifier_shift_activate(void);

// PROCEDURE: asdf_modifier_shiftlock_activate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: sets SHIFTLOCK state if in NORMAL mode, and toggle shiftlock if in TOGGLE mode.
//
void asdf_modifier_shiftlock_activate(void);

// PROCEDURE: asdf_modifier_capslock_activate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Turns on Capslock state
//
void asdf_modifier_capslock_activate(void);

// PROCEDURE: asdf_modifier_ctrl_activate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Turns on CTRL mode
//
void asdf_modifier_ctrl_activate(void);

// PROCEDURE: asdf_modifier_shift_deactivate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Turns off shift mode.
//
void asdf_modifier_shift_deactivate(void);

// PROCEDURE: asdf_modifier_ctrl_deactivate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Turns off CTRL mode
//
void asdf_modifier_ctrl_deactivate(void);

// PROCEDURE: asdf_modifier_shiftlock_deactivate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: No action. This is called when releasing the SHIFT LOCK key,
//
void asdf_modifier_shiftlock_deactivate(void);

// PROCEDURE: asdf_modifier_capslock_deactivate
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: No action.  Called when releasing the CAPS LOCK key.
//
void asdf_modifier_capslock_deactivate(void);

// PROCEDURE: asdf_modifiers_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Initialize the modifier key state variables to OFF state
//
void asdf_modifiers_init(void);

// PROCEDURE: asdf_modifier_index
// INPUTS: none
// OUTPUTS: returns uint8_t index into key map, based on modifier key status
// DESCRIPTION: See OUTPUTS
//
modifier_index_t asdf_modifier_index(void);

#endif // !defined (ASDF_MODIFIERS_H)

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
