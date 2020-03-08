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

typedef enum {
  INITIAL_STATE,
  STABLE_LOW,
  STABLE_HIGH,
  TRANSITION_LOW,
  TRANSITION_HIGH,
  PULSE_DELAY_LOW,
  PULSE_DELAY_HIGH,
  PULSE_HIGH_DETECTED,
  PULSE_LOW_DETECTED,
  NUM_VALID_PULSE_STATES, // error states below this
  ERROR_DOUBLE_DELAY,
  ERROR_DOUBLE_SET,
  ERROR_NO_TRANSITION_BEFORE_DELAY, 
  ERROR_NO_TRANSITION_AFTER_DELAY,
  ERROR_DOUBLE_TRANSITION, // fast pulse without delay
  ERROR_DOUBLE_PULSE,
} pulse_state_t;

typedef enum { SET_HIGH, SET_LOW, PULSE_DELAY, NUM_PULSE_STATE_INPUTS } pulse_state_event_t;

static pulse_state_t pulse_transition_table[NUM_VALID_PULSE_STATES][NUM_PULSE_STATE_INPUTS] =
  {
   [STABLE_LOW] =
   {
    [SET_HIGH] = TRANSITION_HIGH,
    [SET_LOW] = ERROR_DOUBLE_SET,
    [PULSE_DELAY] = ERROR_NO_TRANSITION_BEFORE_DELAY,
   },
   [STABLE_HIGH] =
   {
    [SET_HIGH] = ERROR_DOUBLE_SET,
    [SET_LOW] = TRANSITION_LOW,
    [PULSE_DELAY] = ERROR_NO_TRANSITION_BEFORE_DELAY,
   },
   [TRANSITION_LOW] =
   {
    [SET_HIGH] = ERROR_DOUBLE_TRANSITION,
    [SET_LOW] = ERROR_DOUBLE_SET,
    [PULSE_DELAY] = PULSE_DELAY_LOW,
   },
   [TRANSITION_HIGH] =
   {
    [SET_HIGH] = ERROR_DOUBLE_SET,
    [SET_LOW] = ERROR_DOUBLE_TRANSITION,
    [PULSE_DELAY] = PULSE_DELAY_HIGH,
   },
   [PULSE_DELAY_LOW] =
   {
    [SET_HIGH] = PULSE_LOW_DETECTED,
    [SET_LOW] = ERROR_NO_TRANSITION_AFTER_DELAY,
    [PULSE_DELAY] = ERROR_DOUBLE_PULSE,
   },
   [PULSE_DELAY_HIGH] = 
   {
    [SET_HIGH] = ERROR_NO_TRANSITION_AFTER_DELAY,
    [SET_LOW] = PULSE_HIGH_DETECTED,
    [PULSE_DELAY] = ERROR_DOUBLE_PULSE,
   },
   [PULSE_HIGH_DETECTED] = 
   {
    [SET_HIGH] = STABLE_HIGH,
    [SET_LOW] = STABLE_LOW,
    [PULSE_DELAY] = ERROR_NO_TRANSITION_BEFORE_DELAY
   },
   [PULSE_LOW_DETECTED] = 
   {
    [SET_HIGH] = STABLE_HIGH,
    [SET_LOW] = STABLE_LOW,
    [PULSE_DELAY] = ERROR_NO_TRANSITION_BEFORE_DELAY
   },
  };
  
static uint8_t outputs[NUM_REAL_OUTPUTS];
static pulse_state_t pulses[NUM_REAL_OUTPUTS];

// PROCEDURE: asdf_arch_null_output
// INPUTS: (uint8_t) value - ignored
// OUTPUTS: none
//
// DESCRIPTION: Does nothing.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_null_output(uint8_t value)
{
  (void) value;
}

// PROCEDURE: pulse_detect
// INPUTS: (pulse_state_t) current_state
//         (pulse_event_t) event - current input to the state machine
// OUTPUTS: returns new pulse detector state for the output.
//
// DESCRIPTION: Given an output and a new value for the output, calculate the
// next state of the pulse detector for the output.
//
// SIDE EFFECTS: none.
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 2
//
static pulse_state_t pulse_detect(pulse_state_t current_state, pulse_state_event_t event)
{
  pulse_state_t next_state = current_state;

  // advance state if current state is valid (not an error state)
  if (current_state < NUM_VALID_PULSE_STATES) {
    next_state = pulse_transition_table[current_state][event];
  }
  return next_state;
}


// PROCEDURE: set_output
// INPUTS: (asdf_virtual_real_dev_t) output_dev - the output to set
//         (uint8_t) value - value to assert on the output
// OUTPUTS: none
//
// DESCRIPTION: Given an output and a new value for the output, set the output
// and advance the pulse detector state for the output.
//
// SIDE EFFECTS: see above.
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void set_output(asdf_virtual_real_dev_t output_dev, uint8_t value)
{
  pulse_state_event_t pulse_event = value ? SET_HIGH : SET_LOW;

  outputs[output_dev] = value;
  pulses[output_dev] = pulse_detect(pulses[output_dev], pulse_event);
}


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
  set_output(VMAP_LED1, value);
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
  set_output(VMAP_LED2, value);
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
  set_output(VMAP_LED3, value);
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
  set_output(VMAP_OUT1, value);
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
  set_output(VMAP_OUT1_OC, value);
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
  set_output(VMAP_OUT2, value);
}


// PROCEDURE: asdf_arch_out2_hi_z_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT2 bit to hi-z if value is true, and low if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_out2_hi_z_set(uint8_t value)
{
  set_output(VMAP_OUT2_OC, value);
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
  set_output(VMAP_OUT3, value);
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
  set_output(VMAP_OUT3_OC, value);
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

// PROCEDURE: asdf_arch_pulse_delay
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Emulates a delay by advancing the pulse detector state machine
// for each output.
//
// SIDE EFFECTS: see above.
//
// NOTES: Set ASDF_PULSE_DELAY_US in asdf_config.h
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_pulse_delay(void)
{
  for (uint8_t i = 0; i < NUM_REAL_OUTPUTS; i++) {
    pulses[i] = pulse_detect(pulses[i], PULSE_DELAY);
  }
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
    pulses[i] = INITIAL_STATE;
  }
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
//
