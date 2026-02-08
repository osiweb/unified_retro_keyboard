// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*- 
//
//  Unfified Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_arch_test.h
//
// Architecture-dependent definitions for the unit-testing ASDF software.
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


#if !defined (ASDF_ARCH_H)
#define ASDF_ARCH_H

#include <stdint.h>
#include "asdf.h"
#include "asdf_config.h"
#include "asdf_physical.h"
#include "asdf_virtual.h"



typedef enum {
              PD_ST_INITIAL_STATE = 0,
              PD_ST_STABLE_LOW = 1,
              PD_ST_STABLE_HIGH = 2,
              PD_ST_TRANSITION_LOW = 3,
              PD_ST_TRANSITION_HIGH = 4,
              PD_ST_PULSE_DELAY_LOW = 5,
              PD_ST_PULSE_DELAY_HIGH = 6,
              PD_ST_PULSE_HIGH_DETECTED = 7,
              PD_ST_PULSE_LOW_DETECTED = 8,
              PD_ST_NUM_VALID_PULSE_STATES = 9, // error states below this
              PD_ST_ERROR_DOUBLE_DELAY = 10,
              PD_ST_ERROR_DOUBLE_SET = 11,
              PD_ST_ERROR_NO_TRANSITION_BEFORE_DELAY = 12, 
              PD_ST_ERROR_NO_TRANSITION_AFTER_DELAY = 13,
              PD_ST_ERROR_DOUBLE_TRANSITION = 14, // fast pulse without delay
              PD_ST_ERROR_PULSE_FROM_INITIAL_STATE = 15,
} pulse_state_t;

#define FLASH
// PROCEDURE: arch_flash_get_matrix_element
// INPUTS: (const asdf_keycode_t *) matrix - pointer to keycode matrix
//         (uint8_t) row - row index
//         (uint8_t) col - column index
//         (uint8_t) num_cols - number of columns per row
// OUTPUTS: (asdf_keycode_t) the keycode at the given row and column
// DESCRIPTION: Reads a single keycode from a keycode matrix. Test arch
// equivalent of the PROGMEM version; simply indexes into RAM.
// SIDE EFFECTS: none
// COMPLEXITY: 1
static inline asdf_keycode_t arch_flash_get_matrix_element(
    const asdf_keycode_t *matrix, uint8_t row, uint8_t col, uint8_t num_cols) {
    return matrix[(row * num_cols) + col];
}

// PROCEDURE: arch_flash_get_handler
// INPUTS: (asdf_key_handler_t *) dest - destination
//         (const asdf_key_handler_t *) src - source
// OUTPUTS: none
// DESCRIPTION: Copies a key handler struct. Test arch equivalent of the
// PROGMEM version; simply performs a struct copy.
// SIDE EFFECTS: writes to *dest
// COMPLEXITY: 1
static inline void arch_flash_get_handler(asdf_key_handler_t *dest,
                                          const asdf_key_handler_t *src) {
    *dest = *src;
}
#define ASDF_ARCH_DEFAULT_ROW_SCANNER asdf_arch_read_row
#define ASDF_ARCH_DEFAULT_OUTPUT asdf_arch_send_code

// PROCEDURE: asdf_arch_set_pos_strobe
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Initialize strobe output to positive polarity. Initial state is LOW
void asdf_arch_set_pos_strobe(uint8_t unused);

// PROCEDURE: asdf_arch_set_neg_strobe
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Initialize strobe output
void asdf_arch_set_neg_strobe(uint8_t unused);

// PROCEDURE: asdf_arch_is_strobe_positive
// OUTPUTS: returns non-zero if test arch currently uses positive strobe polarity
uint8_t asdf_arch_is_strobe_positive(void);

// PROCEDURE: asdf_arch_null_output
// INPUTS: (uint8_t) value - ignored
// OUTPUTS: none
// DESCRIPTION: Does nothing.
void asdf_arch_null_output(uint8_t value);

// PROCEDURE: asdf_arch_led1_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: If value is true, turn on LED1.  If value is false, turn off LED1
void asdf_arch_led1_set(uint8_t value);

// PROCEDURE: asdf_arch_led2_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: If value is true, turn on LED2.  If value is false, turn off LED2
void asdf_arch_led2_set(uint8_t value);

// PROCEDURE: asdf_arch_led3_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: If value is true, turn on LED3.  If value is false, turn off LED3
void asdf_arch_led3_set(uint8_t value);

// PROCEDURE: asdf_arch_out1_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT1 bit if value is true, and clear OUT1 if value is false.
void asdf_arch_out1_set(uint8_t value);

// PROCEDURE: asdf_arch_out1_open_hi_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Emulates setting the OUT1 bit to high if value is true, and hi-z
// if value is false. For testing, set PHYSICAL_OUT1_OPEN_LO to the value.
void asdf_arch_out1_open_hi_set(uint8_t value);

// PROCEDURE: asdf_arch_out1_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Emulates setting the OUT1 bit to high if value is true, and hi-z
// if value is false. For testing, set PHYSICAL_OUT1_OPEN_LO to the value.
void asdf_arch_out1_open_lo_set(uint8_t value);

// PROCEDURE: asdf_arch_out2_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT2 bit if value is true, and clear OUT2 if value is false.
void asdf_arch_out2_set(uint8_t value);

// PROCEDURE: asdf_arch_out2_open_hi_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Emulates setting the OUT2 bit to hi-z if value is true, and low
// if value is false. For testing, set PHYSICAL_OUT2_OPEN_HI to the value.
void asdf_arch_out2_open_hi_set(uint8_t value);

// PROCEDURE: asdf_arch_out2_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Emulates setting the OUT2 bit to high if value is true, and hi-z
// if value is false. For testing, set PHYSICAL_OUT2_OPEN_LO to the value.
void asdf_arch_out2_open_lo_set(uint8_t value);

// PROCEDURE: asdf_arch_out3_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT3 bit if value is true, and clear OUT3 if value is false.
void asdf_arch_out3_set(uint8_t value);

// PROCEDURE: asdf_arch_out3_open_hi_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Emulates setting the OUT3 bit to high if value is true, and hi-z
// if value is false. For testing, set PHYSICAL_OUT3_OPEN_LO to the value.
void asdf_arch_out3_open_hi_set(uint8_t value);

// PROCEDURE: asdf_arch_out3_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Emulates setting the OUT3 bit to high if value is true, and hi-z
// if value is false. For testing, set PHYSICAL_OUT3_OPEN_LO to the value.
void asdf_arch_out3_open_lo_set(uint8_t value);

// PROCEDURE: asdf_arch_check_output
// INPUTS:(asdf_physical_dev_t) device - which device to check
// OUTPUTS: the value of the device setting.
// DESCRIPTION: For a given real device, return the current setting (true or false)
uint8_t asdf_arch_check_output(asdf_physical_dev_t device);

// PROCEDURE: asdf_arch_check_pulse
// INPUTS:(asdf_physical_dev_t) device - which device to check
// OUTPUTS: the value of the device pulse detector
// DESCRIPTION: For a given real device, return the state of the pulse detector
uint8_t asdf_arch_check_pulse(asdf_physical_dev_t device);

// PROCEDURE: asdf_arch_pulse_delay_short
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Emulates a short delay by advancing the pulse detector state machine
// for each output.
void asdf_arch_pulse_delay_short(void);

// PROCEDURE: asdf_arch_pulse_delay_long
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Emulates a long delay by advancing the pulse detector state machine
// for each output.
void asdf_arch_pulse_delay_long(void);

// PROCEDURE: asdf_arch_read_row
// INPUTS: (uint8_t) row: the row number to be scanned
// OUTPUTS: returns a word containing the emulated active (pressed) columns
// DESCRIPTION: reads the word from the key state emulation array and returns
// the value. The value is a binary representation of the keys pressed within
// the row, with 1=pressed, 0=released.
asdf_cols_t asdf_arch_read_row(uint8_t row);

// PROCEDURE: asdf_arch_send_code
// INPUTS: asdf_keycode_t code
// OUTPUTS: none
// DESCRIPTION: emulates sending a code, by copying code to a register that can
// be tested.
void asdf_arch_send_code(asdf_keycode_t);

// PROCEDURE: asdf_arch_delay_ms
// INPUTS: (uint16) delay_ms - the delay in msec.
// OUTPUTS: none
// DESCRIPTION: Delays a specified number of milliseconds
void asdf_arch_delay_ms(uint16_t delay_ms);

// PROCEDURE: asdf_arch_delay_ms_call_count
// Returns: number of times asdf_arch_delay_ms has been invoked (testing aid)
uint32_t asdf_arch_delay_ms_call_count(void);

// PROCEDURE: asdf_arch_delay_ms_last_value
// Returns: last delay value passed to asdf_arch_delay_ms (testing aid)
uint16_t asdf_arch_delay_ms_last_value(void);

// PROCEDURE: asdf_arch_delay_ms_reset_count
// DESCRIPTION: clear call-count tracking for asdf_arch_delay_ms (testing aid)
void asdf_arch_delay_ms_reset_count(void);

// PROCEDURE: asdf_arch_get_sent_code
// INPUTS: none
// OUTPUTS: returns type (asdf_keycode_t) in register and zeros the register.
// DESCRIPTION: faciliates test of sending a code, by reporting contents of the
// "sent register"
asdf_keycode_t asdf_arch_get_sent_code(void);

// PROCEDURE: asdf_arch_was_code_sent
// INPUTS: none
// OUTPUTS: returns TRUE if a code was sent, FALSE otherwise.
uint8_t asdf_arch_was_code_sent(void);

// PROCEDURE: asdf_arch_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: sets up all the hardware for the keyboard
void asdf_arch_init(void);



//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
//

#endif // !defined (ASDF_ARCH_H)

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
