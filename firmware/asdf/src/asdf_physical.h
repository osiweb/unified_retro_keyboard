// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_physical.h
//
// Definitions and prototypes for physical LED and virtual output resources.
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

#if !defined(ASDF_PHYSICAL_H)
#define ASDF_PHYSICAL_H


// The asdf_virtual_real_dev_t enumerates real outputs that can be assigned to
// virtual outputs via the asdf_virtual_assign() function. The name is a bit
// confusing, containing virtual and real. The "virtual" part refers to the
// module and the "real_dev" part attempts to clarify that these are the
// hardware outputs implemented by the architecture-specific module.
typedef enum {
  PHYSICAL_NO_OUT = 0,
  PHYSICAL_OUT1,
  PHYSICAL_OUT1_OPEN_HI,
  PHYSICAL_OUT1_OPEN_LO,
  PHYSICAL_OUT2,
  PHYSICAL_OUT2_OPEN_HI,
  PHYSICAL_OUT2_OPEN_LO,
  PHYSICAL_OUT3,
  PHYSICAL_OUT3_OPEN_HI,
  PHYSICAL_OUT3_OPEN_LO,
  PHYSICAL_LED1,
  PHYSICAL_LED2,
  PHYSICAL_LED3,
  ASDF_PHYSICAL_NUM_RESOURCES
} asdf_physical_dev_t;

// PROCEDURE: asdf_physical_set
// INPUTS: (asdf_physical_dev_t) physical_out: which real output to set or clear
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: If the physical resource is valid, set to high if value is true, low
// if false.
void asdf_physical_set(asdf_physical_dev_t physical_out, uint8_t value);

// PROCEDURE: asdf_physical_assert
// INPUTS: (asdf_physical_dev_t) physical_out: which physical resource to set or clear
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Assert the value of the physical resource shadow register on the output.
void asdf_physical_assert(asdf_physical_dev_t physical_out);

// PROCEDURE: asdf_physical_toggle
// INPUTS: (asdf_physical_dev_t) physical_out: which physical resource to toggle
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Toggle the value of the physical resource.
void asdf_physical_toggle(asdf_physical_dev_t physical_out);

// PROCEDURE: physical_device_is_available
// INPUTS: asdf_physical_dev_t requiested_device
// OUTPUTS: returns PHYSICAL_NO_OUT if device is alreay allocated. If not yet allocated,
// returns the index of the device in the available list before the requested
// device.
// DESCRIPTION: iterates through the linked list of available devices. If the
// requested_device is encountered, return the element before the requested
// device in the list.  If the end of the list is reached, return PHYSICAL_NO_OUT.
uint8_t physical_device_is_available(asdf_physical_dev_t device);

// PROCEDURE: asdf_physical_next_device
// INPUTS: (asdf_physical_dev_t) device - the current physical resource attached
// to the virtual output being operated on
// OUTPUTS: (asdf_physical_dev_t) returns the next physical resource assigned to
// the virtual output.
asdf_physical_dev_t asdf_physical_next_device(asdf_physical_dev_t device);

// PROCEDURE: asdf_physical_allocate
// INPUTS: (asdf_physical_out_t) physical_out - the desired physical resource to allocate.
//         (asdf_physical_out_t) tail - the list of physical resources to tack on
//         to the requested resource, if available.
// OUTPUTS: (asdf_physical_out_t) returns TRUE if the allocation is succesful,
//          FALSE (0) otherwise.
// DESCRIPTION: Check that the requested physical resource is valid and
// available. If so, then remove the resource from the physical resource table
// and assign an initial value, then return a TRUE (1). Return FALSE (0) if
// allocation was not successful.
uint8_t asdf_physical_allocate(asdf_physical_dev_t physical_out, asdf_physical_dev_t tail,
                               uint8_t initial_value);

// PROCEDURE: asdf_physical_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Initialize physical resource table
void asdf_physical_init(void);


#endif /* !defined (ASDF_PHYSICAL_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
