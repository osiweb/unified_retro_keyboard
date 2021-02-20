// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_virtual.h
//
// Definitions and prototypes for virtual LED and virtual output management.
//
// Copyright 2019 David Fenyes
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

#if !defined(ASDF_VIRTUAL_H)
#define ASDF_VIRTUAL_H

#include "asdf_physical.h"

// These are "virtual" output identifiers that can be mapped to the real outputs using
// keymap initializer commands.
typedef enum {
  V_NULL,
  VOUT1,
  VOUT2,
  VOUT3,
  VOUT4,
  VOUT5,
  VOUT6,
  VLED1,
  VLED2,
  VLED3,
  VCAPS_LED,
  VSHIFT_LED,
  ASDF_VIRTUAL_NUM_RESOURCES
} asdf_virtual_dev_t;


typedef enum {
  V_NOFUNC,
  V_SET_HI,
  V_SET_LO,
  V_PULSE_SHORT,
  V_PULSE_LONG,
  V_TOGGLE,
  ASDF_VIRTUAL_NUM_FUNCTIONS
} asdf_virtual_function_t;

// Each keymap specifies an array of initializer structs to configure virtual
// devices, specifying the mapped real device and initial value.
typedef struct {
  asdf_virtual_dev_t virtual_device;
  asdf_physical_dev_t physical_device;
  asdf_virtual_function_t function;
  uint8_t initial_value;
} asdf_virtual_initializer_t;

// PROCEDURE: asdf_virtual_action
// INPUTS: (asdf_virtual_dev_t) virtual_out: which virtual output to modify
// INPUTS: (asdf_virtual_function_t) function: what function to apply to the virtual output
// OUTPUTS: none
// DESCRIPTION: for each real output mapped to the virtual output, apply the
// specified function.
void asdf_virtual_action(asdf_virtual_dev_t virtual_out, asdf_virtual_function_t function);

// PROCEDURE: asdf_virtual_activate
// INPUTS: asdf_virtual_dev_t: The virtual device to be activated
// OUTPUTS: none
// DESCRIPTION: for each real output mapped to the virtual output, apply the
// function assigned to the virtual output at initialization.
void asdf_virtual_activate(asdf_virtual_dev_t virtual_out);

// PROCEDURE: asdf_virtual_assign
// INPUTS: (asdf_virtual_dev_t) virtual_out - virtual output to be paired with the physical resource
//         (asdf_physical_dev_t) physical_out to be assigned to the virtual output.
//         (asdf_virtual_function_t) - the function to be applied to the virtual
//              device when activated by a keypress.
//         (uint8_t) initial_value - the initial state of the physical resource.
// OUTPUTS: none
// DESCRIPTION: map the virtual output specified by new_vout to physical_out, if
// both arguments are valid. Ignore if not valid.
// NOTES: if the virtual output is invalid, or the physical resource is invalid,
// or the physical resource is already assigned, then nothing happens.
void asdf_virtual_assign(asdf_virtual_dev_t virtual_out, asdf_physical_dev_t physical_out,
                         asdf_virtual_function_t function, uint8_t initial_value);

// PROCEDURE: asdf_virtual_init
// INPUTS: initializers
// OUTPUTS: none
// DESCRIPTION: Initializes the LED and output mapping
void asdf_virtual_init(void);

// PROCEDURE: asdf_virtual_sync
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Synchronize the physical outputs with their controlling virtual devices.
void asdf_virtual_sync(void);

#endif /* !defined (ASDF_VIRTUAL_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
