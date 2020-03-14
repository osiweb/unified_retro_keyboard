// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_physical.c
//
// This file contains code to manage physical resources and serves as an API
// between the virtual layer and the architecture specific code.
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
#include "asdf_keymap_defs.h"
#include "asdf_config.h"
#include "asdf_arch.h"


// physical_out_set[] contains the set() function for each real output device.
static void (*const physical_out_set[])(uint8_t) = {
  [PHYSICAL_NO_OUT] = &asdf_arch_null_output,    //
  [PHYSICAL_OUT1] = &asdf_arch_out1_set,         //
  [PHYSICAL_OUT2] = &asdf_arch_out2_set,         //
  [PHYSICAL_OUT3] = &asdf_arch_out3_set,         //
  [PHYSICAL_OUT1_OC] = &asdf_arch_out1_hi_z_set, //
  [PHYSICAL_OUT2_OC] = &asdf_arch_out2_hi_z_set, //
  [PHYSICAL_OUT3_OC] = &asdf_arch_out3_hi_z_set, //
  [PHYSICAL_LED1] = &asdf_arch_led1_set,         //
  [PHYSICAL_LED2] = &asdf_arch_led2_set,         //
  [PHYSICAL_LED3] = &asdf_arch_led3_set          //
};


// For each physical resource, maintain a "shadow" register for the output value. This
// permits machine independent implementations of the toggle and pulse functions
// to be implemented in this module, requiring only a "set" function for each
// physical resource in the architecture-dependent layer. This implementation is
// not as efficient, but the timing is not critical, and the events are so
// infrequent that the benefits of the refactoring far outweigh any performance
// penalty.

static struct {
  uint8_t shadow;
  asdf_physical_dev_t next;
} physical_device_table[ASDF_PHYSICAL_NUM_RESOURCES];


// PROCEDURE: asdf_physical_set
// INPUTS: (asdf_physical_dev_t) physical_out: which real output to set or clear
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If the physical resource is valid, set to high if value is true, low
// if false.
//
// SIDE EFFECTS: see above
//
// NOTES: No bounds checking.  The caller must ensure a valid device
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_physical_set(asdf_physical_dev_t physical_out, uint8_t value)
{
  physical_out_set[physical_out](value);
  physical_device_table[physical_out].shadow = value;
}


// PROCEDURE: asdf_physical_assert
// INPUTS: (asdf_physical_dev_t) physical_out: which physical resource to set or clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Assert the value of the physical resource shadow register on the output.
//
// SIDE EFFECTS: see above
//
// NOTES: No bounds checking.  Only called from initialization code.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_physical_assert(asdf_physical_dev_t physical_out)
{
  uint8_t value = physical_device_table[physical_out].shadow;
  physical_out_set[physical_out](value);
}

// PROCEDURE: asdf_physical_toggle
// INPUTS: (asdf_physical_dev_t) physical_out: which physical resource to toggle
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Toggle the value of the physical resource.
//
// SIDE EFFECTS: see above
//
// NOTES: No bounds checking.  Only called from initialization code.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_physical_toggle(asdf_physical_dev_t physical_out)
{
  uint8_t value = physical_device_table[physical_out].shadow;

  asdf_physical_set(physical_out, !value);
}

// PROCEDURE: valid_physical_device
// INPUTS: (asdf_physical_dev_t) device
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
static uint8_t valid_physical_device(asdf_physical_dev_t device)
{
  return (device > PHYSICAL_NO_OUT && device < ASDF_PHYSICAL_NUM_RESOURCES);
}

// PROCEDURE: physical_device_is_available
// INPUTS: asdf_physical_dev_t requiested_device
// OUTPUTS: returns PHYSICAL_NO_OUT if device is alreay allocated. If not yet allocated,
// returns the index of the device in the available list before the requested
// device.
//
// DESCRIPTION: iterates through the linked list of available devices. If the
// requested_device is encountered, return the element before the requested
// device in the list.  If the end of the list is reached, return PHYSICAL_NO_OUT.
//
// SIDE EFFECTS: none
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 3
//
uint8_t physical_device_is_available(asdf_physical_dev_t device)
{
  asdf_physical_dev_t current_out = PHYSICAL_NO_OUT;
  asdf_physical_dev_t next_out = physical_device_table[current_out].next;

  while (next_out != PHYSICAL_NO_OUT && next_out != device) {
    current_out = next_out;
    next_out = physical_device_table[current_out].next;
  }
  return (PHYSICAL_NO_OUT == next_out) ? ASDF_PHYSICAL_NUM_RESOURCES : current_out;
}

// PROCEDURE: asdf_physical_next_device
// INPUTS: (asdf_physical_dev_t) device - the current physical resource attached
// to the virtual output being operated on
//
// OUTPUTS: (asdf_physical_dev_t) returns the next physical resource assigned to
// the virtual output.
//
// DESCRIPTION: See above.
//
// SIDE EFFECTS: None.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
asdf_physical_dev_t asdf_physical_next_device(asdf_physical_dev_t device)
{
  return physical_device_table[device].next;
}

// PROCEDURE: asdf_physical_allocate

// INPUTS: (asdf_physical_out_t) physical_out - the desired physical resource to allocate.
//         (asdf_physical_out_t) tail - the list of physical resources to tack on
//         to the requested resource, if available.
//
// OUTPUTS: (asdf_physical_out_t) returns TRUE if the allocation is succesful,
//          FALSE (0) otherwise.
//
// DESCRIPTION: Check that the requested physical resource is valid and
// available. If so, then remove the resource from the physical resource table
// and assign an initial value, then return a TRUE (1). Return FALSE (0) if
// allocation was not successful.
//
// SIDE EFFECTS: see above.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
uint8_t asdf_physical_allocate(asdf_physical_dev_t physical_out, asdf_physical_dev_t tail, uint8_t initial_value)
{
  uint8_t success = 0;
  asdf_physical_dev_t predecessor = physical_device_is_available(physical_out);

  if (valid_physical_device(physical_out)
      && (ASDF_PHYSICAL_NUM_RESOURCES != predecessor)) {

    // remove from available list:
    physical_device_table[predecessor].next = physical_device_table[physical_out].next;

    // tack the tail on to the physical resource

    physical_device_table[physical_out].next = tail;

    // The physical resource shadow value is set here. The shadow values are
    // asserted to the outputs only after all the assignments have been
    // performed.
    physical_device_table[physical_out].shadow = initial_value;

    success = 1;
  }
  return success;
}

// PROCEDURE: asdf_physical_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize physical resource table
//
// SIDE EFFECTS: see above
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_physical_init(void)
{
  // initialize the linked list of free devices
  for (uint8_t i = 0; i < ASDF_PHYSICAL_NUM_RESOURCES; i++) {
    physical_device_table[i].shadow = ASDF_VIRTUAL_OUT_DEFAULT_VALUE;
    physical_device_table[i].next = i + 1; // initialize pointer to next in table
  }
  // The last item in the table is left with a bogus next pointer (beyond the
  // end of the array) after the above loop. Make the last element point to
  // PHYSICAL_NO_OUT.
  physical_device_table[ASDF_PHYSICAL_NUM_RESOURCES - 1].next = PHYSICAL_NO_OUT; // end of list.
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
