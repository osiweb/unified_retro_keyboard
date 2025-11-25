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

#include "asdf_arch.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "asdf.h"
#include "asdf_config.h"

static volatile uint8_t tick = 0;

static uint8_t data_polarity = ASDF_DEFAULT_DATA_POLARITY;


// PROCEDURE: ISR for Timer 0 overflow
// INPUTS: none
// OUTPUTS:none
//
// DESCRIPTION: Occurs every 1 ms.  Set tick flag, kick watchdog.
//
// SIDE EFFECTS:
//
// NOTES:
//
// SCOPE:
//
// COMPLEXITY:
//
ISR(TIMER0_COMPA_vect)
{
  tick = 1;
}

// PROCEDURE: set_bit
// INPUTS: port: pointer to a (uint8) port
//         bit: bit position to be set
// OUTPUTS: none
//
// DESCRIPTION: Give a port address and bit position, set the bit position.
//
// SIDE EFFECTS: See DESCRIPTION
//
// NOTES: Declared inline. Will only be inlined for functions in this module, so
// also declared static.
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static inline void set_bit(volatile uint8_t *port, uint8_t bit)
{
  *port |= (1 << bit);
}

// PROCEDURE: clear_bit
// INPUTS: port: pointer to a (uint8) port
//         bit: bit position to be cleared
// OUTPUTS: none
//
// DESCRIPTION: Give a port address and bit position, clear the bit position.
//
// SIDE EFFECTS: See DESCRIPTION
//
// NOTES: Declared inline. Will only be inlined for functions in this module, so
// also declared static.
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static inline void clear_bit(volatile uint8_t *port, uint8_t bit)
{
  *port &= ~(1 << bit);
}

// PROCEDURE: arch_timer0_config
//
// INPUTS: bits: a 4 byte field containing the configuration values for the
// 8-bit timer0 A and B control registers, and the interrupt mask register.
//
// OUTPUTS: none
//
// DESCRIPTION: Takes a 4 byte value with settings for all the control
// registers for the 8-bit counter/timer (timer 0), and writes them all
// to the respective registers.
//
// SIDE EFFECTS: see above
//
// NOTES: Setting all the bits together, and writing all the registers from a
// single word permits more clear initialization of control fields that are
// spread across more than one word.
//
// COMPLEXITY: 1
//
// SCOPE: private
//
static void arch_timer0_config(uint32_t bits)
{
  TCCR0B = 0; // first turn off timer.
  TCCR0A = (bits >> TMR0A_POS) & 0xff;
  TIMSK0 = (bits >> TMR0IMSK_POS) & 0xff;
  TCCR0B = (bits >> TMR0B_POS) & 0xff; // Set the mode (and turn on timer) last
}

// PROCEDURE: arch_tick_timer_init
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Sets up 1ms tick timer.
//
// SIDE EFFECTS:
//
// NOTES: Set up Timer 0 in CTC mode for 1 ms overflow.
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_arch_tick_timer_init(void)
{
  tick = 0;

  // set compare register first, so timer can operate correctly as soon as it is
  // enabled.
  OCR0A = TICK_COUNT;

  // operate in CTC mode to overflow at exactly 1 ms
  // prescaler = 64 and output compare value is 250
  arch_timer0_config(TIMER0_WFM_CTC | TIMER0_DIV64 | TIMER0_INT_ON_COMA);
}

// PROCEDURE: asdf_arch_tick
// INPUTS: none
// OUTPUTS: returns a 1 if the 1ms timer timed out, 0 otherwise
//
// DESCRIPTION: See Outputs.
//
// SIDE EFFECTS: Zeroes out the 1 ms timer flag.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
uint8_t asdf_arch_tick(void)
{
  uint8_t retval = tick;
  tick = 0;
  return retval;
}

// PROCEDURE: asdf_arch_init_timers
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Sets up timer for 1 ms intervals
//
// SIDE EFFECTS: See DESCRIPTION
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_arch_init_clock(void)
{
  CLKPR = (CLKPCE | SYSCLK_DIV1);
}

// PROCEDURE: asdf_arch_init_outputs
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize all LED ports as outputs. Values are not set here.
// They are set by the keymap code
//
// SIDE EFFECTS: See DESCRIPTION
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_arch_init_leds(void)
{
  set_bit(&ASDF_LED1_DDR, ASDF_LED1_BIT);
  set_bit(&ASDF_LED2_DDR, ASDF_LED2_BIT);
  set_bit(&ASDF_LED3_DDR, ASDF_LED3_BIT);
}


// PROCEDURE: asdf_arch_led1_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If value is true, turn on LED1.  If value is false, turn off LED1
//
// SIDE EFFECTS: See above.
//
// NOTES: The LED1 port drives the LED directly by pulling the cathode low, so
// clearing the bit turns the LED on.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_led1_set(uint8_t value)
{
  if (value) {
    clear_bit(&ASDF_LED1_PORT, ASDF_LED1_BIT);
  }
  else {
    set_bit(&ASDF_LED1_PORT, ASDF_LED1_BIT);
  }
}

// PROCEDURE: asdf_arch_led2_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If value is true, turn on LED2.  If value is false, turn off LED2
//
// SIDE EFFECTS: See above.
//
// NOTES: The LED2 output drives the LED via an inverter buffer, so a high
// output pulls the LED cathode low, lighting the LED.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_led2_set(uint8_t value)
{
  if (value) {
    set_bit(&ASDF_LED2_PORT, ASDF_LED2_BIT);
  }
  else {
    clear_bit(&ASDF_LED2_PORT, ASDF_LED2_BIT);
  }
}

// PROCEDURE: asdf_arch_led3_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: If value is true, turn on LED3.  If value is false, turn off LED3
//
// SIDE EFFECTS: See above.
//
// NOTES: The LED3 output drives the LED via an inverter buffer, so a high
// output pulls the LED cathode low, lighting the LED.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_led3_set(uint8_t value)
{
  if (value) {
    set_bit(&ASDF_LED3_PORT, ASDF_LED3_BIT);
  }
  else {
    clear_bit(&ASDF_LED3_PORT, ASDF_LED3_BIT);
  }
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
// COMPLEXITY: 2
//
void asdf_arch_out1_set(uint8_t value)
{
  if (value) {
    set_bit(&ASDF_OUT1_PORT, ASDF_OUT1_BIT);
  }
  else {
    clear_bit(&ASDF_OUT1_PORT, ASDF_OUT1_BIT);
  }
  set_bit(&ASDF_OUT1_DDR, ASDF_OUT1_BIT);
}

// PROCEDURE: asdf_arch_out1_open_hi_set
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
// COMPLEXITY: 2
//
void asdf_arch_out1_open_hi_set(uint8_t value)
{
  if (value) {
    clear_bit(&ASDF_OUT1_DDR, ASDF_OUT1_BIT);
    set_bit(&ASDF_OUT1_PORT, ASDF_OUT1_BIT);
  }
  else {
    clear_bit(&ASDF_OUT1_PORT, ASDF_OUT1_BIT);
    set_bit(&ASDF_OUT1_DDR, ASDF_OUT1_BIT);
  }
}

// PROCEDURE: asdf_arch_out1_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT1 bit to high if value is true, and hi-z if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_out1_open_lo_set(uint8_t value)
{
  if (value) {
    set_bit(&ASDF_OUT1_PORT, ASDF_OUT1_BIT);
    set_bit(&ASDF_OUT1_DDR, ASDF_OUT1_BIT);
  }
  else {
    clear_bit(&ASDF_OUT1_DDR, ASDF_OUT1_BIT);
    clear_bit(&ASDF_OUT1_PORT, ASDF_OUT1_BIT);
  }
}

// PROCEDURE: asdf_arch_out2_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT2 bit if value is true, and clear OUT2 if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES: OUT2 is inverted by the 7404 buffer, so clearing the bit sets the output high.  OUT2
// cannot be high impedance.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_out2_set(uint8_t value)
{
  if (value) {
    clear_bit(&ASDF_OUT2_PORT, ASDF_OUT2_BIT);
  }
  else {
    set_bit(&ASDF_OUT2_PORT, ASDF_OUT2_BIT);
  }
  set_bit(&ASDF_OUT2_DDR, ASDF_OUT2_BIT);
}

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

// PROCEDURE: asdf_arch_out2_open_hi_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT2 bit to hi-z if value is true, and low if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES: Not supported for the ATMega-328 ASCII interface.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_out2_open_hi_set(uint8_t value)
{
  asdf_arch_null_output(value);
}

// PROCEDURE: asdf_arch_out2_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT2 bit to high if value is true, and hi-z if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES: Not supported for the ATMega-328 ASCII interface.
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_out2_open_lo_set(uint8_t value)
{
  asdf_arch_null_output(value);
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
// COMPLEXITY: 2
//
void asdf_arch_out3_set(uint8_t value)
{
  if (value) {
    set_bit(&ASDF_OUT3_PORT, ASDF_OUT3_BIT);
  }
  else {
    clear_bit(&ASDF_OUT3_PORT, ASDF_OUT3_BIT);
  }
  set_bit(&ASDF_OUT3_DDR, ASDF_OUT3_BIT);
}

// PROCEDURE: asdf_arch_out3_open_hi_set
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
// COMPLEXITY: 2
//
void asdf_arch_out3_open_hi_set(uint8_t value)
{
  if (value) {
    clear_bit(&ASDF_OUT3_DDR, ASDF_OUT3_BIT);
    set_bit(&ASDF_OUT3_PORT, ASDF_OUT3_BIT);
  }
  else {
    clear_bit(&ASDF_OUT3_PORT, ASDF_OUT3_BIT);
    set_bit(&ASDF_OUT3_DDR, ASDF_OUT3_BIT);
  }
}

// PROCEDURE: asdf_arch_out3_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
//
// DESCRIPTION: Sets the OUT3 bit to high if value is true, and hi-z if value is false.
//
// SIDE EFFECTS: See above.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_arch_out3_open_lo_set(uint8_t value)
{
  if (value) {
    set_bit(&ASDF_OUT3_PORT, ASDF_OUT3_BIT);
    set_bit(&ASDF_OUT3_DDR, ASDF_OUT3_BIT);
  }
  else {
    clear_bit(&ASDF_OUT3_DDR, ASDF_OUT3_BIT);
    clear_bit(&ASDF_OUT3_PORT, ASDF_OUT3_BIT);
  }
}

// PROCEDURE: asdf_arch_set_pos_strobe
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize strobe output to positive polarity. Initial state is
// LOW
//
// SIDE EFFECTS: See DESCRIPTION
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_set_pos_strobe(uint8_t unused)
{
  (void) unused;
  clear_bit(&ASDF_STROBE_PORT, ASDF_STROBE_BIT);
  set_bit(&ASDF_STROBE_DDR, ASDF_STROBE_BIT);
}

// PROCEDURE: asdf_arch_set_neg_strobe
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize strobe output
//
// SIDE EFFECTS: See DESCRIPTION
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_set_neg_strobe(uint8_t unused)
{
  (void) unused;
  set_bit(&ASDF_STROBE_PORT, ASDF_STROBE_BIT);
  set_bit(&ASDF_STROBE_DDR, ASDF_STROBE_BIT);
}

// PROCEDURE: asdf_arch_init_ascii_output
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Sets up output port for ASCII output
//
// SIDE EFFECTS: See DESCRIPTION
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_arch_init_ascii_output(void)
{

  // set all outputs
  ASDF_ASCII_PORT = data_polarity;
  ASDF_ASCII_DDR = ALL_OUTPUTS;
}

// PROCEDURE: asdf_arch_init_column_inputs
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: configure the shift register control lines. The MODE control is
// LOW for shift and HIGH for load.  Shift or Load occurs when CLK goes high.
//
// SIDE EFFECTS: Cont
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_arch_init_column_control(void)
{

  // COLCLK is output and initialized LOW
  clear_bit(&ASDF_COLCLK_PORT, ASDF_COLCLK_BIT);
  set_bit(&ASDF_COLCLK_DDR, ASDF_COLCLK_BIT);

  // COLMODE is output and initialized HIGH
  set_bit(&ASDF_COLMODE_PORT, ASDF_COLMODE_BIT);
  set_bit(&ASDF_COLMODE_DDR, ASDF_COLMODE_BIT);

  // COL is input, no weak pullup.
  clear_bit(&ASDF_COL_DDR, ASDF_COL_BIT);
  clear_bit(&ASDF_COL_PORT, ASDF_COL_BIT);
}

// PROCEDURE: asdf_arch_init_row_outputs
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Sets up output port to latch keyboard matrix row for scanning.
//
// SIDE EFFECTS: See DESCRIPTION
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static void asdf_arch_init_row_outputs(void)
{
  ASDF_ROW_PORT &= ~ASDF_ROW_MASK;
  ASDF_ROW_DDR |= ASDF_ROW_MASK;
}

// PROCEDURE: asdf_arch_pulse_delay_short
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Delays a fixed amount of time for keyboard output pulses specified by ASDF_PULSE_DELAY_SHORT_US
//
// SIDE EFFECTS: see above.
//
// NOTES: Set ASDF_PULSE_DELAY_US in asdf_config.h
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_pulse_delay_short(void)
{
  _delay_us(ASDF_PULSE_DELAY_SHORT_US);
}

// PROCEDURE: asdf_arch_pulse_delay_long
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Delays a fixed amount of time for keyboard output pulses specified by ASDF_PULSE_DELAY_LONG_MS
//
// SIDE EFFECTS: see above.
//
// NOTES: Set ASDF_PULSE_DELAY_US in asdf_config.h
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_pulse_delay_long(void)
{
  _delay_ms(ASDF_PULSE_DELAY_LONG_MS);
}

// PROCEDURE: asdf_arch_delay_ms
// INPUTS: (uint16) delay_ms - the delay in msec.
// OUTPUTS: none
//
// DESCRIPTION: Delays a specified number of milliseconds
//
// SIDE EFFECTS: see above.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_delay_ms(uint16_t delay_ms)
{
  for (uint16_t i=0; i < delay_ms; i++) {
    _delay_ms(1);
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
  // disable interrupts:
  cli();

  // clear the 1ms timer flag;
  tick = 0;

  // set up timers for 1 msec intervals
  asdf_arch_init_clock();
  asdf_arch_tick_timer_init();

  // set up ASCII output port
  asdf_arch_init_ascii_output();

  // initialize keyboard data polarity and strobe polarity
  data_polarity = ASDF_DEFAULT_DATA_POLARITY;

  if (ASDF_DEFAULT_STROBE_POLARITY == ASDF_POSITIVE_POLARITY) {
    asdf_arch_set_pos_strobe(0);
  } else {
    asdf_arch_set_neg_strobe(0);
  }

  asdf_arch_init_leds();

  asdf_arch_init_leds();

  // set up row output port
  asdf_arch_init_row_outputs();

  // set up column control lines
  asdf_arch_init_column_control();

  // enable interrupts:
  sei();
}


// PROCEDURE: asdf_arch_read_row
// INPUTS: (uint8_t) row: the row number to be scanned
// OUTPUTS: returns a word containing the active (pressed) columns
//
// DESCRIPTION: Outputs the argument to the ROW port, then reads the column port
// and returns the value. The value is a binary representation of the keys
// pressed within the row, with 1=pressed, 0=released.
//
// SIDE EFFECTS: Sets ROW output port.
//
// NOTES:
//
// 1) The keymap represents an unpressed key as a "0" and a pressed key as a
//    "1". So, if a keypress pulls the column line low, then the reading of the
//    physical bits must be inverted.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
asdf_cols_t asdf_arch_read_row(uint8_t row)
{
  asdf_cols_t cols = 0;

  // first, output the new row value:
  ASDF_ROW_PORT = (ASDF_ROW_PORT & ~ASDF_ROW_MASK) 
    | ((row & ASDF_ROW_MASK) << ASDF_ROW_OFFSET);


  // read in the columns.  Set LOAD mode and pulse clock.
  clear_bit(&ASDF_COLMODE_PORT, ASDF_COLMODE_BIT);

  set_bit(&ASDF_COLCLK_PORT, ASDF_COLCLK_BIT);
  clear_bit(&ASDF_COLCLK_PORT, ASDF_COLCLK_BIT);

  // set back to SHIFT mode
  set_bit(&ASDF_COLMODE_PORT, ASDF_COLMODE_BIT);

  // After the load operation, the LSB is already at the output pin, so there
  // will be one fewer read than clock pulse. Continue reading the bits until
  // the leader bit is in the boundary position.
  for (uint8_t i = 0; i < ASDF_MAX_COLS; i++) {

    // invert the bits as they are read (see note 1)
    cols |= (((~(ASDF_COL_PIN) >> ASDF_COL_BIT) & 1) << i);

    set_bit(&ASDF_COLCLK_PORT, ASDF_COLCLK_BIT);
    clear_bit(&ASDF_COLCLK_PORT, ASDF_COLCLK_BIT);
  }

  return cols;
}


// PROCEDURE: asdf_arch_send_code
// INPUTS: (keycode_t) code - the 7-bit ASCII code to be output by the keyboard
// OUTPUTS: none
//
// DESCRIPTION: Takes a character code and outputs the code on a parallel ASCII
// port, with a strobe. This routine could be replaced with UART, I2C, USB, or
// other output mechanism, of course.
//
// SIDE EFFECTS: See above.
//
// NOTES: The strobe is set by the ASDF_STROBE_LENGTH definition. The data
// output and strobe polarity are set by the static data_polarity and static
// strobe_polarity variables.
//
// SCOPE:
//
// COMPLEXITY:
//

void asdf_arch_send_code(asdf_keycode_t code)
{
  ASDF_ASCII_PORT = (code ^ data_polarity);


  // toggle strobe.  Must test before setting to avoid spurious strobe
  set_bit(&ASDF_STROBE_PIN, ASDF_STROBE_BIT);

  _delay_us(ASDF_STROBE_LENGTH_US);

  set_bit(&ASDF_STROBE_PIN, ASDF_STROBE_BIT);
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
//
