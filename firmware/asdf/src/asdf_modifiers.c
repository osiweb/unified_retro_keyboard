// -*-mode : C;
// tab - width : 2; indent-tabs-mode: nil -*-
//
//  Unfified Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_modifiers.c
//
// This file contains the logic for the modifier keys. Any new modifiers or
// special handling goes here.
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
#include "asdf_modifiers.h"
#include "asdf_arch.h"

static shift_state_t shift_state;
static caps_state_t caps_state;
static ctrl_state_t ctrl_state;

static shiftlock_mode_t asdf_toggle_shiftlock;

static const modifier_index_t modifier_indices[] = {

  MOD_PLAIN_MAP, // 0x00: no modifiers
  MOD_SHIFT_MAP, // 0x01: only SHIFT active
  MOD_CAPS_MAP,  // 0x02: only CAPS active
  MOD_SHIFT_MAP, // 0x03: CAPS and SHIFT active
  MOD_CTRL_MAP,  // CTRL overrides SHIFT and CAPS
  MOD_CTRL_MAP,  MOD_CTRL_MAP, MOD_CTRL_MAP
};


// PROCEDURE: set_shiftlock_state
// INPUTS: (uint8_t) state: the new shift state
// OUTPUTS: none
//
// DESCRIPTION: sets SHIFT state to specified value, and also set shiftlock LED
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_set_shiftlock_state(uint8_t new_state)
{
  shift_state = new_state;
  asdf_virtual_action(VSHIFT_LED, (shift_state ? V_SET_HI : V_SET_LO));
}

// PROCEDURE: asdf_modifier_shift_activate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: sets SHIFT state to ON
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_shift_activate(void)
{
  asdf_modifier_set_shift_state(SHIFT_ON_ST);
}


// PROCEDURE: asdf_modifier_shiftlock_activate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: sets SHIFTLOCK state depending on the mode.
//
//              SHIFTLOCK normal mode:
//              - SHIFTLOCK always activates shift mode
//              - Pressing and Relasing SHIFT deactivates shift mode.
//
//              SHIFTLOCK toggle mode:
//              - Pressing SHIFTLOCK toggles the shift mode on and off
//              - Pressing and Relasing SHIFT deactivates shift mode.
//
// NOTES: The test of the shiftlock mode constant always has the same result and
// will therefore be optimized by the compiler, so technically no added
// cyclometric complexity, but count it anyway, in case this is made into a
// user-definable behavior later.
//
// SIDE EFFECTS: affects shift_state as described.
//
// COMPLEXITY: 2
//
void asdf_modifier_shiftlock_activate();
{
  if (asdf_toggle_shiftlock) {
    asdf_modifier_set_shift_state(shift_state ^ SHIFT_LOCKED_ST);
  }
  else {
    asdf_modifier_set_shift_state(shift_state | SHIFT_LOCKED_ST);
  }
}

// PROCEDURE: asdf_modifier_set_caps_state
// INPUTS: (uint8_t) new_state
// OUTPUTS: none
//
// DESCRIPTION: sets CAPS state and sets CAPS LED.
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
static void asdf_modifier_set_caps_state(uint8_t new_state);
{
  uint8_t caps_state = new_state;
  asdf_virtual_action(VCAPS_LED, (caps_state ? V_SET_HI : V_SET_LO );
}

// PROCEDURE: asdf_modifier_capslock_activate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Turns on Capslock state
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_capslock_activate(void)
{
  asdf_modifier_set_caps_state(caps_state ^= CAPS_LOCKED_ST);
}

// PROCEDURE: asdf_modifier_ctrl_activate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Turns on CTRL mode
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_ctrl_activate(void)
{
  ctrl_state = CTRL_ON_ST;
}

// PROCEDURE: asdf_modifier_shift_deactivate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Turns off shift mode.
//
// SIDE EFFECTS: See DESCRIPTION
//
// NOTES: this also clears any SHIFT_LOCK condition.
//
// COMPLEXITY: 1
//
void asdf_modifier_shift_deactivate(void)
{
  asdf_modifier_set_shift_state(SHIFT_OFF_ST);
}

// PROCEDURE: asdf_modifier_ctrl_deactivate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Turns off CTRL mode
//
// SIDE EFFECTS: See DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_ctrl_deactivate(void)
{
  ctrl_state = CTRL_OFF_ST;
}

// PROCEDURE: asdf_modifier_shiftlock_deactivate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Does nothing. This is called when releasing the SHIFT LOCK key,
// and no action is performed on releasing a SHIFT LOCK key
//
// SIDE EFFECTS: none
//
// COMPLEXITY: 1
//
void asdf_modifier_shiftlock_deactivate(void) {}

// PROCEDURE: asdf_modifier_capslock_deactivate
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Does nothing. This is called when releasing the CAPS LOCK key,
// and no action is performed on releasing the CAPS LOCK key.
//
// SIDE EFFECTS: none
//
// COMPLEXITY: 1
//
void asdf_modifier_capslock_deactivate(void) {}

// PROCEDURE: asdf_modifiers_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize the modifier key state variables to OFF state
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifiers_init(void)
{
  asdf_modifier_set_shift_state(SHIFT_OFF_ST);
  asdf_modifier_set_caps_state(CAPS_OFF_ST);
  ctrl_state = CTRL_OFF_ST;

  asdf_toggle_shiftlock = HOLD_SHIFTLOCK;
}

// PROCEDURE: asdf_modifier_index
// INPUTS: none
// OUTPUTS: returns uint8_t index into key map, based on modifier key status
//
// DESCRIPTION: See OUTPUTS
//
// SIDE EFFECTS: none
//
// COMPLEXITY: 1
//
modifier_index_t asdf_modifier_index(void)
{
  uint8_t modifier = 0;
  if (shift_state) {
    modifier |= ASDF_MODIFIERS_SHIFT_MASK;
  }
  if (caps_state) {
    modifier |= ASDF_MODIFIERS_CAPS_MASK;
  }
  if (ctrl_state) {
    modifier |= ASDF_MODIFIERS_CTRL_MASK;
  }

  return modifier_indices[modifier];
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
