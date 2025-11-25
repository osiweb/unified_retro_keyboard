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
#include "asdf_physical.h"
#include "asdf_virtual.h"
#include "asdf_arch.h"

// Stores the state of the SHIFT and SHIFTLOCK keys
static shift_state_t shift_state;

// Stores the state of the CAPS and CAPSLOCK keys
static caps_state_t caps_state;

// Stores the state of the CTRL keys.
static ctrl_state_t ctrl_state;

// The active modifier map depends on the current state of the modifier
// variables. The map encodes the order or precedence of the various modifiers.
static const modifier_index_t modifier_mapping[] = { MOD_PLAIN_MAP, // 0x00: no modifiers
                                                     MOD_SHIFT_MAP, // 0x01: only SHIFT active
                                                     MOD_CAPS_MAP,  // 0x02: only CAPS active
                                                     MOD_SHIFT_MAP, // 0x03: CAPS and SHIFT active
                                                     MOD_CTRL_MAP,  // CTRL overrides SHIFT and CAPS
                                                     MOD_CTRL_MAP,  MOD_CTRL_MAP, MOD_CTRL_MAP };


// PROCEDURE: set_shift_state
// INPUTS: (uint8_t) state: the new shift state
// OUTPUTS: none
//
// DESCRIPTION: sets SHIFT state to specified value, and also set shiftlock LED
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_set_shift_state(uint8_t new_state)
{
  shift_state = new_state;
  asdf_virtual_action(VSHIFT_LED, ((shift_state & SHIFT_LOCKED_ST) ? V_SET_HI : V_SET_LO));
}

// PROCEDURE: asdf_modifier_shift_activate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: sets SHIFT state to ON
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_shift_activate(uint8_t unused)
{
  (void) unused;
  asdf_modifier_set_shift_state(SHIFT_ON_ST);
}


// PROCEDURE: asdf_modifier_shiftlock_on_activate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: sets SHIFTLOCK state to ON
//
// NOTES:
//
// SIDE EFFECTS: affects shift_state as described.
//
// COMPLEXITY: 1
//
void asdf_modifier_shiftlock_on_activate(uint8_t unused)
{
  (void) unused;
  asdf_modifier_set_shift_state(shift_state | SHIFT_LOCKED_ST);
}

// PROCEDURE: asdf_modifier_shiftlock_toggle_activate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: Toggles SHIFTLOCK state.
//
// NOTES:
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_shiftlock_toggle_activate(uint8_t unused)
{
  (void) unused;
  asdf_modifier_set_shift_state(shift_state ^ SHIFT_LOCKED_ST);
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
static void asdf_modifier_set_caps_state(uint8_t new_state)
{
  caps_state = new_state;
  asdf_virtual_action(VCAPS_LED, (caps_state ? V_SET_HI : V_SET_LO));
}

// PROCEDURE: asdf_modifier_capslock_activate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: Toggles Capslock state
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_capslock_activate(uint8_t unused)
{
  (void) unused;
  asdf_modifier_set_caps_state(caps_state ^= CAPS_LOCKED_ST);
}

// PROCEDURE: asdf_modifier_ctrl_activate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: Turns on CTRL mode
//
// SIDE EFFECTS: see DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_ctrl_activate(uint8_t unused)
{
  (void) unused;
  ctrl_state = CTRL_ON_ST;
}

// PROCEDURE: asdf_modifier_shift_deactivate
// INPUTS: unused - parameter required for dispatch table but not used
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
void asdf_modifier_shift_deactivate(uint8_t unused)
{
  (void) unused;
  asdf_modifier_set_shift_state(SHIFT_OFF_ST);
}

// PROCEDURE: asdf_modifier_ctrl_deactivate
// INPUTS: unused - parameter required for dispatch table but not used
// OUTPUTS: none
//
// DESCRIPTION: Turns off CTRL mode
//
// SIDE EFFECTS: See DESCRIPTION
//
// COMPLEXITY: 1
//
void asdf_modifier_ctrl_deactivate(uint8_t unused)
{
  (void) unused;
  ctrl_state = CTRL_OFF_ST;
}

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
}

// PROCEDURE: asdf_modifier_index
// INPUTS: none
// OUTPUTS: returns uint8_t index into key map, based on which modifiers are active.
//
// DESCRIPTION: See OUTPUTS
//
// SIDE EFFECTS: none
//
// COMPLEXITY: 4
//
modifier_index_t asdf_modifier_index(void)
{
  uint8_t active_modifiers = 0;

  if (shift_state) {
    active_modifiers |= ASDF_MODIFIERS_SHIFT_MASK;
  }
  if (caps_state) {
    active_modifiers |= ASDF_MODIFIERS_CAPS_MASK;
  }
  if (ctrl_state) {
    active_modifiers |= ASDF_MODIFIERS_CTRL_MASK;
  }

  return modifier_mapping[active_modifiers];
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
