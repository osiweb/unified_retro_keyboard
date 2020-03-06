// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_arch.c
//
// This file contains all the architecture dependent code, including register
// setup, I/O, timers, etc.
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


// Wiring Information:
// Chip: {Microcontroller type and version}
//
// Example:
// PIN          NAME      FUNCTION
// 14-19,9,10   PORTB     COLUMN inputs (1 bit per column)
// 23-25        PORTC0-2  ROW outputs (row number)
// 27           PORTC4


#include <stdint.h>
#include "asdf_keymap_defs.h"
#include "asdf_config.h"
#include "asdf_virtual.h"
#include "asdf_arch.h"
// this is to get rid of "unused variable" warnings.
volatile static uint32_t junk_variable;

static uint8_t outputs[NUM_REAL_OUTPUTS];

// PROCEDURE: asdf_arch_led1_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If value is true, turn on LED1.  If value is false, turn off LED1
//
// SIDE EFFECTS: See above.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_led1_set(uint8_t value)
{
  outputs[VMAP_LED1] = value;
}

// PROCEDURE: asdf_arch_led2_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If value is true, turn on LED2.  If value is false, turn off LED2
//
// SIDE EFFECTS: See above.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_led2_set(uint8_t value)
{
  outputs[VMAP_LED2] = value;
}

// PROCEDURE: asdf_arch_led3_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If value is true, turn on LED3.  If value is false, turn off LED3
//
// SIDE EFFECTS: See above.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_led3_set(uint8_t value)
{
  outputs[VMAP_LED3] = value;
}

// PROCEDURE: asdf_arch_out1_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT1 bit if value is true, and clear OUT1 if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_out1_set(uint8_t value)
{
  outputs[VMAP_OUT1] = value;
}

// PROCEDURE: asdf_arch_out1_hi_z_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT1 bit to hi-z if value is true, and low if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_out1_hi_z_set(uint8_t value)
{
  outputs[VMAP_OUT1_OC] = value;
}

// PROCEDURE: asdf_arch_out2_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT2 bit if value is true, and clear OUT2 if value is false.
//
// SIDE EFFECTS: See above.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_out2_set(uint8_t value)
{
  outputs[VMAP_OUT2] = value;
}

// PROCEDURE: asdf_arch_out3_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT3 bit if value is true, and clear OUT3 if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_out3_set(uint8_t value)
{
  outputs[VMAP_OUT3] = value;
}

// PROCEDURE: asdf_arch_out3_hi_z_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT3 bit to hi-z if value is true, and low if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_out3_hi_z_set(uint8_t value)
{
  outputs[VMAP_OUT3_OC] = value;
}

// PROCEDURE: asdf_arch_check_output
// INPUTS:(asdf_virtual_real_dev_t) device - which device to check
// OUTPUTS: the value of the device setting.
//
// DESCRIPTION: For a given real device, return the current setting (true or false)
//
// SIDE EFFECTS: none
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
uint8_t asdf_arch_check_output(asdf_virtual_real_dev_t device)
{
  return outputs[device];
}

// PROCEDURE: asdf_arch_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: sets up all the hardware for the keyboard
//
// SIDE EFFECTS: see DESCRIPTION
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_init(void)
{
  for (uint8_t i = 0; i < NUM_REAL_OUTPUTS; i++) {
    outputs[i] = 0;
  }
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
//
