// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_virtual_outputs.c
//
// This file contains code that maps "virtual" LEDs and outputs referenced by
// the code to actual LEDs and outputs in hardware. This keeps keymap-specific
// details out of the architecture-dependent files, and provides a flexible way
// for the keymap definitions to specify the LED and output functions for
// different keymaps or keyboard layouts.
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
//

#include <stdint.h>
#include "asdf_physical.h"
#include "asdf_virtual.h"
#include "asdf_config.h"
#include "asdf_arch.h"

// virtual_device_table[] contains all the virtual outputs. An
// asdf_virtual_output_t value is used to identify each element. Each element is
// a virtual output, containing an asdf_virtual_physical_dev_t value indicating
// the first in the list of physical resources (if any) assigned to the virtual
// device. Each element also contains a function that can be applied to the
// physical resources when the virtual output is activated by a keypress.
static struct {
  asdf_physical_dev_t physical_device; // Each virtual output points to a linked
                                       // list of any number of physical resources.
  asdf_virtual_function_t function;
} virtual_device_table[ASDF_VIRTUAL_NUM_RESOURCES];

// PROCEDURE: asdf_virtual_map_function

// INPUTS:
//   (asdf_virtual_function_t) function - function to apply to devices.
//   (asdf_physical_device_t) device - first physical device in linked list
//
// OUTPUTS: none
//
// DESCRIPTION: Iterates through a linked list of physical devices, applying the
// specified function to each device.
//
// SIDE EFFECTS: see DESCRIPTION
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 2
//
void asdf_virtual_map_function(void (*function)(asdf_physical_dev_t), asdf_physical_dev_t device)
{
  while (PHYSICAL_NO_OUT != device) {
    (*function)(device);
    device = asdf_physical_next_device(device);
  }
}

// PROCEDURE: asdf_virtual_action
// INPUTS: (asdf_virtual_output_t) virtual_out: which virtual output to modify
// INPUTS: (asdf_virtual_function_t) function: what function to apply to the virtual output
// OUTPUTS: none
//
// DESCRIPTION: for each physical resource mapped to the virtual output, apply the
// specified function.
//
// SIDE EFFECTS: see above
//
// NOTES: The virtual output points to a linked list of physical resources.
//
// SCOPE: public
//
// COMPLEXITY: 6
//

void asdf_virtual_action(asdf_virtual_dev_t virtual_out, asdf_virtual_function_t function)
{
  asdf_physical_dev_t device_list = virtual_device_table[virtual_out].physical_device;

  switch (function) {

    case V_PULSE_LONG: {
      asdf_virtual_map_function(&asdf_physical_toggle, device_list);
      asdf_arch_pulse_delay_long();
      asdf_virtual_map_function(&asdf_physical_toggle, device_list);
      break;
    }
    case V_PULSE_SHORT: {
      asdf_virtual_map_function(&asdf_physical_toggle, device_list);
      asdf_arch_pulse_delay_short();
      asdf_virtual_map_function(&asdf_physical_toggle, device_list);
      break;
    }
    case V_TOGGLE: {
      asdf_virtual_map_function(&asdf_physical_toggle, device_list);
      break;
    }
    case V_SET_HI: {
      asdf_virtual_map_function(&asdf_physical_on, device_list);
      break;
    }
    case V_SET_LO: {
      asdf_virtual_map_function(&asdf_physical_off, device_list);
    }
    case V_NOFUNC:
    default: break;
  }
}

// PROCEDURE: asdf_virtual_activate
// INPUTS: asdf_virtual_dev_t: The virtual output to be activated
// OUTPUTS: none
//
// DESCRIPTION: for each physical resource mapped to the virtual output, apply the
// function assigned to the virtual output at initialization.
//
// SIDE EFFECTS: see above
//
// NOTES: The virtual output points to a linked list of physical resources.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_virtual_activate(asdf_virtual_dev_t virtual_out)
{
  asdf_virtual_action(virtual_out, virtual_device_table[virtual_out].function);
}

// PROCEDURE: valid_virtual_device
// INPUTS: (asdf_virtual_dev_t) device
// OUTPUTS: returns true (1) if the device is valid, false (0) if not valid.
//
// DESCRIPTION: test to see if device is a valid device value.
//
// SIDE EFFECTS:
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static uint8_t valid_virtual_device(asdf_virtual_dev_t device)
{
  return (device > V_NULL && device < ASDF_VIRTUAL_NUM_RESOURCES);
}

// PROCEDURE: asdf_virtual_assign
// INPUTS: (asdf_virtual_dev_t) virtual_out - virtual output to be paired with the physical resource
//         (asdf_physical_dev_t) physical_out to be assigned to the virtual output.
//         (asdf_virtual_function_t) - the function to be applied to the virtual
//              device when activated by a keypress.
//         (uint8_t) initial_value - the initial state of the physical resource.
//
// OUTPUTS: none
//
// DESCRIPTION: map the virtual output specified by new_vout to physical_out, if
// both arguments are valid. Ignore if not valid.
//
// SIDE EFFECTS: see above.
//
// NOTES:
//   if the virtual output is invalid, or the physical resource is invalid, or
//   the physical resource is already assigned, then nothing happens.
//
// SCOPE: private
//
// COMPLEXITY: 3
//
void asdf_virtual_assign(asdf_virtual_dev_t virtual_out, asdf_physical_dev_t physical_out,
                                asdf_virtual_function_t function, uint8_t initial_value)
{
  if (valid_virtual_device(virtual_out)) {
    asdf_physical_dev_t tail = virtual_device_table[virtual_out].physical_device;

    if (asdf_physical_allocate(physical_out, tail, initial_value)) {

      virtual_device_table[virtual_out].physical_device = physical_out;
      virtual_device_table[virtual_out].function = function;
    }
  }
}

// PROCEDURE: asdf_virtual_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initializes the LED and output mapping
//
// SIDE EFFECTS: see above
//
// NOTES:  ASDF_VIRTUAL_OUT_DEFAULT_VALUE is defined in asdf_config.h
//
// SCOPE: public
//
// COMPLEXITY: 4
//
void asdf_virtual_init(void)
{
  // initialize the physical resource table every time virtual output table is
  // initialized.
  asdf_physical_init();

  // initialize list of virtual outputs
  for (uint8_t i = 0; i < ASDF_VIRTUAL_NUM_RESOURCES; i++) {
    virtual_device_table[i].function = V_NOFUNC;
    virtual_device_table[i].physical_device = PHYSICAL_NO_OUT;
  }
}

// PROCEDURE: asdf_virtual_sync
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Synchronize the physical outputs with their controlling virtual devices.
//
// SIDE EFFECTS: see above
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_virtual_sync(void)
{
  for (uint8_t i = 0; i < ASDF_PHYSICAL_NUM_RESOURCES; i++) {
    asdf_physical_assert((asdf_physical_dev_t) i);
  }
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
