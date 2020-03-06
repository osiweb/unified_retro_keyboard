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


#include "asdf_virtual.h"
#include "asdf_arch.h"

// For each virtual out, maintain a "shadow" register for the output value. This
// permits machine independent implementations of the toggle and pulse functions
// to be implemented in this module, requiring only a "set" function for each
// virtual output in the architecture-dependent layer. This implementation is
// not as efficient, but the timing is not critical, and the events are so
// infrequent that the benefits of the refactoring far outweigh any performance
// penalty.

typedef struct {
  uint8_t shadow;
  asdf_virtual_real_dev_t next;
} real_dev_t;

typedef struct {
  asdf_virtual_real_dev_t real_device; // Each virtual device points to a linked
                                       // list of any number of real devices.
  asdf_virtual_function_t function;
} virtual_dev_t;


static real_dev_t real_device_table[NUM_REAL_OUTPUTS];


// vout_set[] contains the set() function for each real output device.
static const void (*vout_set[])(uint8_t) = {
  [VMAP_NO_OUT] = NULL,                      //
  [VMAP_OUT1] = &asdf_arch_out1_set,         //
  [VMAP_OUT2] = &asdf_arch_out2_set,         //
  [VMAP_OUT3] = &asdf_arch_out3_set,         //
  [VMAP_OUT1_OC] = &asdf_arch_out1_hi_z_set, //
  [VMAP_OUT2_OC] = &asdf_arch_out2_hi_z_set, //
  [VMAP_OUT3_OC] = &asdf_arch_out3_hi_z_set, //
  [VMAP_VLED1] = &asdf_arch_led1_set,        //
  [VMAP_VLED2] = &asdf_arch_led2_set,        //
  [VMAP_VLED3] = &asdf_arch_led3_set         //
};

// virtual_out[] contains all the virtual outputs. An asdf_virtual_output_t
// value is used to identify each element. Each element is a virtual device,
// containing an asdf_virtual_real_dev_t value indicating the real device (if
// any) assigned to the virtual device.
static virtual_dev_t virtual_device_table[NUM_VIRTUAL_OUTPUTS];


// PROCEDURE: asdf_virtual_real_set
// INPUTS: (asdf_virtual_real_dev_t) real_out: which real output to set or clear
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If the real output is valid, set to high if value is true, low
// if false.
//
// SIDE EFFECTS: see above
//
// NOTES: No bounds checking.  The caller must ensure a valid device
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_virtual_real_set(asdf_virtual_real_dev_t real_out, uint8_t value)
{
  vout_set[real_out](value);
  shadow_out[real_out] = value;
}


// PROCEDURE: asdf_virtual_real_assert
// INPUTS: (asdf_virtual_real_dev_t) real_out: which real output to set or clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Assert the value of the real output shadow register on the output.
//
// SIDE EFFECTS: see above
//
// NOTES: No bounds checking.  Only called from initialization code.
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_virtual_real_assert(asdf_virtual_real_dev_t real_out);
{
  uint8_t value = real_device_table[real_out].shadow;
  vout_set[real_out](value);
}

// PROCEDURE: asdf_virtual_real_toggle
// INPUTS: (asdf_virtual_real_dev_t) real_out: which real output to toggle
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Toggle the value of the real output.
//
// SIDE EFFECTS: see above
//
// NOTES: No bounds checking.  Only called from initialization code.
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_virtual_real_toggle(asdf_virtual_real_dev_t real_out);
{
  uint8_t value = real_device_table[real_out].shadow;

  real_device_table[real_out].shadow = !value;
  vout_set[real_out](value);
}

// PROCEDURE: asdf_virtual_action
// INPUTS: (asdf_virtual_output_t) virtual_out: which virtual output to modify
// INPUTS: (asdf_virtual_function_t) function: what function to apply to the virtual output
// OUTPUTS: none
//
// DESCRIPTION: for each real output mapped to the virtual output, apply the
// specified function.
//
// SIDE EFFECTS: see above
//
// NOTES: The virtual output points to a linked list of real devices.
//
// SCOPE: public
//
// COMPLEXITY: 7
//
void asdf_virtual_action(asdf_virtual_output_t virtual_out, asdf_virtual_function_t function)
{
  real_dev_t device = virtual_device_table[virtual_out].real_device;

  while (VMAP_NO_OUT != device) {
    switch (function) {

      case V_PULSE: {
        asdf_virtual_real_toggle(device);
        asdf_arch_pulse_delay();
        // yes we could omit the next two lines and fall through, but we will
        // spend a few bytes of redundant code for the sake of consistency and
        // readability.
        asdf_virtual_real_toggle(device);
        break;
      }
      case V_TOGGLE: {
        asdf_virtual_real_toggle(device);
        break;
      }
      case V_SET_HI: {
        asdf_virtual_real_set(device, 1);
        break;
      }
      case V_SET_LO: {
        asdf_virtual_real_set(device, 0);
      }
      case V_NOFUNC:
      default: break;
    }
    device = real_device_table[device].next;
  }
}

// PROCEDURE: asdf_virtual_assign
// INPUTS: (asdf_vout_t) virtual_out
//         (uint8_t) real_out
// OUTPUTS: none
//
// DESCRIPTION: map the virtual output specified by new_vout to real_out, if
// both arguments are valid. Ignore if not valid.
//
// SIDE EFFECTS: see above.
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 2
//
static void asdf_virtual_assign(asdf_virtual_output_t virtual_out, asdf_virtual_real_dev_t real_out,
                         asdf_virtual_function_t function, uint8_t initial_value)
{
  virtual_device_table[virtual_device].function = function;

  // add real device to the list associated with the virtual device:

  real_device_table[real_out].next = virtual_device_table[virtual_out].real_device;
  virtual_device_table[virtual_out].real_device = real_out;

  // The real device shadow value is set here. The shadow values are asserted to
  // the outputs only after all the assignments have been performed.
  real_device_table[real_out].shadow = value;
}

// PROCEDURE: asdf_virtual_init
// INPUTS: initializers
// OUTPUTS: none
//
// DESCRIPTION: Initializes the LED and output mapping
//
// SIDE EFFECTS: see above
//
// NOTES: The table of real devices is initialized as a linked list of available
// devices.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_virtual_init(virtual_initializer_t *initializer_list)
{

  // initialize list of virtual outputs
  for (uint8_t i = 0; i < NUM_VIRTUAL_OUTPUTS; i++) {
    virtual_device_table[i].function = V_NOFUNC;
    virtual_device_table[i].real_device = VMAP_NO_OUT;
  }

  // initialize the linked list of free devices
  for (uint8_t i = 0; i < NUM_REAL_OUTPUTS; i++) {
    real_device_table[i].shadow = ASDF_VIRTUAL_OUT_DEFAULT_VALUE;
    real_device_table[i].next = i + 1 // initialize pointer to next in table
  }
  // The last item in the table is left with a bogus next pointer (beyond the
  // end of the array) after the above loop. Make the last element point to
  // NULL.
  real_device_table[NUM_REAL_OUTPUTS - 1].next = VMAP_NO_OUT; // end of list.


  // run through the keymap specific setup
  for (uint8_t i = 0; //
       i < NUM_INITIALIZERS && initializers[i].virtual_device != V_NULL; i++) {

    asdf_virtual_assign(intializer_list[i].virtual_device, intializer_list[i].real_device,
                        initializer_list[i].function, initializer_list[i].initial_value);
  }

  // Now set all the initial LED and output values
  for (uint8_t i = 0; i < NUM_REAL_OUTPUTS; i++) {
    asdf_virtual_real_assert((asdf_virtual_real_dev_t) i);
  }
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
