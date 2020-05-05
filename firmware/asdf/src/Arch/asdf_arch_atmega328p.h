// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
//  Unfified Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_arch_atmega328p.h
//
// Contains architecture-specific definitions for the atmega 328p.
//
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

#if !defined(ASDF_ARCH_H)
#define ASDF_ARCH_H

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "asdf.h"

// ASDF keyboard definitions:

#define ASDF_STROBE_LENGTH_US 10 // strobe length in microseconds


// Clock definitions:
#define SYSCLK_DIV1 0
#define SYSCLK_DIV2 (CLKPS0)
#define SYCCLK_DIV4 (CLKPS1)
#define SYSCLK_DIV8 (CLKPS1 | CLKPS0)
#define SYSCLK_DIV16 (CLKPS2)
#define SYSCLK_DIV32 (CLKPS2 | CLKPS0)
#define SYSCLK_DIV64 (CLKPS2 | CLKPS1)
#define SYSCLK_DIV128 (CLKPS2 | CLKPS1 | CLKPS0)
#define SYSCLK_DIV256 (CLKPS3)

// Define fields for register A, B, interrupt mask as 8-bit masks, and
// as masks offset into a combined config word
#define TMR0A_POS 0
#define TMR0B_POS 8
#define TMR0IMSK_POS 16
#define TMR0A (1L << TMR0A_POS)
#define TMR0B (1L << TMR0B_POS)
#define TMR0IMSK (1L << TMR0IMSK_POS)

#define TIMER0_COM_A_DISCONNECTED 0
#define TIMER0_COM_B_DISCONNECTED 0
#define TIMER0_WFM_CTC (TMR0A << WGM01)
#define TIMER0_DIV64 ((TMR0B << CS01) | (TMR0B << CS00))
#define TIMER0_INT_ON_COMA (TMR0IMSK << OCIE0A)
#define TIMER0_INT_ON_COMB (TMR0IMSK << OCIE0B)
#define TIMER0_INT_OV_ENABLE (TMR0IMSK << TOIE0)

// Macros for 16-bit timer 1. ATmega328P datasheet section 15, p. 108
//
// Define fields for Registers A, B, C, INT Mask registers as 8-bit
// masks, and as masks offset into a 32-bit combined config word.
//
// Macro definitions for individual registers are named TMR1A_*,
// TMR1B_*, and TMR1C_*.
//
// Macros for the one-step combined timer config functions are named
// TMR1_*.
//
//
// Examples:
//   // Use TMR1B_* definition to set TCCR1B register
//   TCCR1B |= TMR1B_DIV1;
//
//   // Use TMR1_* definitions to configure timer with config function
//   timer1_config(TMR1_WFM_CTC | TMR1_INT_ON_CMPA);
//
#define TMR1A_POS 0
#define TMR1B_POS 8
#define TMR1C_POS 16
#define TMR1IMSK_POS 24
#define TMR1A (1L << TMR1A_POS)
#define TMR1B (1L << TMR1B_POS)
#define TMR1C (1L << TMR1C_POS)
#define TMR1IMSK (1L << TMR1IMSK_POS)

// 16-bit timer reg A - Datasheet 17.11.1, p. 154
#define TMR1A_CMPA_CLR_MATCH_SET_BOTTOM (1 << COM1A1)
#define TMR1A_CMPB_CLR_MATCH_SET_BOTTOM (1 << COM1B1)
#define TMR1A_CMPC_CLR_MATCH_SET_BOTTOM (1 << COM1C1)
#define TMR1_CMPA_CLR_MATCH_SET_BOTTOM (TMR1A << COM1A1)
#define TMR1_CMPB_CLR_MATCH_SET_BOTTOM (TMR1A << COM1B1)
#define TMR1_CMPC_CLR_MATCH_SET_BOTTOM (TMR1A << COM1C1)

// 16-bit timer reg B - Datasheet 17.11.6, p. 156

#define TMR1B_IN_CAP_POS 0x40L
#define TMR1B_IN_CAP_NEG 0L
#define TMR1B_IN_CAP_NOISE_CANCEL 0x80L

// 16-bit timer reg C -- see datasheet, 17.11.9, p. 157
#define TMR1C_FOCA 0x80L
#define TMR1C_FOCB 0x40L
#define TMR1C_FOCC 0x20L

// 16-bit timer int mask -- see datasheet 17.11.33, p. 161.
#define TMR1IM_INT_CMP_MATCH_A (1L << OCIE1A)
#define TMR1IM_INT_CMP_MATCH_B (1L << OCIE1B)
#define TMR1IM_INT_CMP_MATCH_C (1L << OCIE1C)

// 16-bit timer all registers:
#define TMR1_CMPA_DISCONNECTED 0L
#define TMR1_CMPB_DISCONNECTED 0L
#define TMR1_CMPC_DISCONNECTED 0L
#define TMR1_INT_ON_CMPA (TMR1IM_INT_CMP_MATCH_A << TMR1IMSK_POS)

// 16-bit timer clock modes - see Datasheet table 17-6,  p. 157
#define TMR1B_OFF 0
#define TMR1_OFF 0
#define TMR1B_DIV1 (0x01L << CS10)
#define TMR1B_DIV8 (0x02L << CS10)
#define TMR1B_DIV64 (0x03L << CS10)
#define TMR1B_DIV256 (0x04L << CS10)
#define TMR1B_DIV1024 (0x05L << CS10)
#define TMR1B_EXT_FALLING_EDGE (0x06L << CS10)
#define TMR1B_EXT_RISING_EDGE (0x07L << CS10)
#define TMR1B_CLK_MASK 0x07L
#define TMR1_DIV1 (TMR1B_DIV1 << TMR1B_POS)
#define TMR1_DIV8 (TMR1B_DIV8 << TMR1B_POS)
#define TMR1_DIV64 (TMR1B_DIV64 << TMR1B_POS)
#define TMR1_DIV256 (TMR1B_DIV256 << TMR1B_POS)
#define TMR1_DIV1024 (TMR1B_DIV1024 << TMR1B_POS)
#define TMR1_EXT_FALLING_EDGE (TMR1B_EXT_FALLING_EDGE << TMR1B_POS)
#define TMR1_EXT_RISING_EDGE (TMR1B_EXT_RISING_EDGE << TMR1B_POS)

#define TMR1B_EDGE_SEL_POSITIVE (1 << ICES1)
#define TMR1B_EDGE_SEL_NEGATIVE 0L
#define TMR1_EDGE_SEL_POSITIVE (TMR1B << ICES1)
#define TMR1_EDGE_SEL_NEGATIVE 0L

// 16-bit waveform modes (across reg A and B) Datasheet Table 17.2, p 145
#define TMR1_WFM_NORMAL 0L
#define TMR1_WFM_PWM_PC8 (TMR1A << WGM10)                        // PWM Phase Correct 8-bit
#define TMR1_WFM_PWM_PC9 (TMR1A << WGM11)                        // PWM Phase COrrect 9-bit
#define TMR1_WFM_PWM_PC10 ((TMR1A << WGM11) | (TMR1A << WGM10))  // PWM Phase Correct 10-bit
#define TMR1_WFM_CTC (TMR1B << WGM12)                            // CTC
#define TMR1_WFM_PWM_FAST8 ((TMR1B << WGM12) | (TMR1A << WGM10)) // PWM Fast 8-bit
#define TMR1_WFM_PWM_FAST9 ((TMR1B << WGM12) | (TMR1A << WGM11)) // PWM Fast 9-bit
#define TMR1_WFM_PWM_FAST10                                                                        \
  ((TMR1B << WGM12) | (TMR1A << WGM11) | (TMR1A << WGM10)) // PWM Fast 10-bit
#define TMR1_WFM_PWM_PFC_ICR (TMR1B << WGM13)              // PWM Phase and Freq Correct, TpOP=ICR
#define TMR1_WFM_PWM_PFC_OCRA                                                                      \
  ((TMR1B << WGM13) | (TMR1A << WGM10)) // PWM Phase and Freq Correct, TOP = OCRA
#define TMR1_WFM_PWM_PC_ICR ((TMR1B << WGM13) | (TMR1A << WGM11)) // PWM PhaseCorrect, TOP = ICR
#define TMR1_WFM_PWM_PC_OCRA                                                                       \
  ((TMR1B << WGM13) | (TMR1A << WGM11) | (TMR1A << WGM12))     // PWM PhaseCorrect, TOP=OCRA
#define TMR1_WFM_CTC_ICR ((TMR1B << WGM13) | (TMR1B << WGM12)) // CTC, TOP = ICR
#define TMR1_WFM_PWM_FAST_ICR                                                                      \
  ((TMR1B << WGM13) | (TMR1B << WGM12) | (TMR1A << WGM11)) // PWM Fast, TOP = ICR
#define TMR1_WFM_PWM_FAST_OCRA                                                                     \
  ((TMR1B << WGM13) | (TMR1B << WGM12) | (TMR1A << WGM11)                                          \
   | (TMR1A << WGM10)) // PWM Fast, TOP = OCRA


// I/O port definitions:

#define PIN_INPUT 0
#define PIN_OUTPUT 1
#define ALL_INPUTS 0
#define ALL_OUTPUTS 0xff

#define ASDF_ROW_PORT PORTC
#define ASDF_ROW_DDR DDRC
#define ASDF_ROW_MASK 0x0f
#define ASDF_ROW_OFFSET 0

#define ASDF_COL_PORT PORTB
#define ASDF_COL_PIN PINB
#define ASDF_COL_DDR DDRB
#define ASDF_COL_BIT 0
#define ASDF_COL_PULLUPS 0 // disable weak pullup

#define ASDF_COLCLK_PORT PORTB
#define ASDF_COLCLK_PINS PINB
#define ASDF_COLCLK_DDR DDRB
#define ASDF_COLCLK_BIT 2

#define ASDF_COLMODE_PORT PORTB
#define ASDF_COLMODE_PINS PINB
#define ASDF_COLMODE_DDR DDRB
#define ASDF_COLMODE_BIT 1

#define ASDF_ASCII_PORT PORTD
#define ASDF_ASCII_DDR DDRD

#define ASDF_LED1_PORT PORTC
#define ASDF_LED1_DDR DDRC
#define ASDF_LED1_BIT 4

#define ASDF_LED2_PORT PORTB
#define ASDF_LED2_DDR DDRB
#define ASDF_LED2_BIT 5

#define ASDF_LED3_PORT PORTB
#define ASDF_LED3_DDR DDRB
#define ASDF_LED3_BIT 4

#define ASDF_OUT1_PORT PORTC
#define ASDF_OUT1_PIN PINC
#define ASDF_OUT1_DDR DDRC
#define ASDF_OUT1_BIT 5

#define ASDF_OUT2_PORT PORTB
#define ASDF_OUT2_PIN PINB
#define ASDF_OUT2_DDR DDRB
#define ASDF_OUT2_BIT 3

#define ASDF_OUT3_PORT PORTB
#define ASDF_OUT3_PIN PINB
#define ASDF_OUT3_DDR DDRB
#define ASDF_OUT3_BIT 7

#define ASDF_STROBE_PORT PORTB
#define ASDF_STROBE_PIN PINB
#define ASDF_STROBE_DDR DDRB
#define ASDF_STROBE_BIT 6

#define FUSE_INTERNAL_8MHZ_OSC_0MS (FUSE_CKSEL0 | FUSE_CKSEL2 | FUSE_CKSEL3 | FUSE_SUT0 | FUSE_SUT1)
#define FUSE_INTERNAL_8MHZ_OSC_4MS (FUSE_CKSEL0 | FUSE_CKSEL2 | FUSE_CKSEL3 | FUSE_SUT1)
#define FUSE_INTERNAL_8MHZ_OSC_65MS (FUSE_CKSEL0 | FUSE_CKSEL2 | FUSE_CKSEL3 | FUSE_SUT0)

#define FLASH PROGMEM

// not implemented with do-while(0) because this is a function call that returns
// a value, and parameters are expanded inside the parameter list, so this will
// be valid when substituting for function-like syntax.
#define FLASH_READ (a) pgm_read_byte((a))
#define FLASH_READ_MATRIX_ELEMENT(matrix, row, col) pgm_read_byte(&((matrix)[(row)][(col)]))

// For 1 ms tick, (8000000 / 64(prescale)) / 1000(usec) - 1 = 124
#define TICK_COUNT 124


// Default key matrix row scanner
#define ASDF_ARCH_DEFAULT_SCANNER asdf_arch_read_row

// Default keyboard output
#define ASDF_ARCH_DEFAULT_OUTPUT asdf_arch_send_code

// DIP switch is on row 8
#define ASDF_ARCH_DIPSWITCH_ROW 8

// PROCEDURE: asdf_arch_null_output
// INPUTS: (uint8_t) value - ignored
// OUTPUTS: none
// DESCRIPTION: null/dummy output function
// NOTES: Not supported for the ATMega-328 ASCII interface.
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
// DESCRIPTION: Sets the OUT1 bit to hi-z if value is true, and low if value is false.
void asdf_arch_out1_open_hi_set(uint8_t value);

// PROCEDURE: asdf_arch_out1_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT1 bit to hi-z if value is true, and low if value is false.
void asdf_arch_out1_open_lo_set(uint8_t value);

// PROCEDURE: asdf_arch_out2_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT2 bit if value is true, and clear OUT2 if value is false.
void asdf_arch_out2_set(uint8_t value);

// PROCEDURE: asdf_arch_out2_open_hi_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT2 bit to hi-z if value is true, and low if value is false.
// NOTES: Not supported for the ATMega-328 ASCII interface.
void asdf_arch_out2_open_hi_set(uint8_t value);

// PROCEDURE: asdf_arch_out2_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT2 bit to high if value is true, and hi-z if value is false.
void asdf_arch_out2_open_lo_set(uint8_t value);

// PROCEDURE: asdf_arch_out3_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT3 bit if value is true, and clear OUT3 if value is false.
void asdf_arch_out3_set(uint8_t value);

// PROCEDURE: asdf_arch_out3_open_hi_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT3 bit to hi-z if value is true, and low if value is false.
void asdf_arch_out3_open_hi_set(uint8_t value);

// PROCEDURE: asdf_arch_out3_open_lo_set
// INPUTS: (uint8_t) value
// OUTPUTS: none
// DESCRIPTION: Sets the OUT3 bit to hi-z if value is true, and low if value is false.
void asdf_arch_out3_open_lo_set(uint8_t value);

// PROCEDURE: asdf_arch_read_row
// INPUTS: (uint8_t) row: the row number to be scanned
// OUTPUTS: returns a word containing the active (pressed) columns
// DESCRIPTION: Outputs the argument to the ROW port, then reads the column port
// and returns the value. The value is a binary representation of the keys
// pressed within the row, with 1=pressed, 0=released.
asdf_cols_t asdf_arch_read_row(uint8_t row);

// PROCEDURE: asdf_arch_pulse_delay_short
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Delays a fixed amount of time for keyboard output pulses specified by ASDF_PULSE_DELAY_SHORT_US
void asdf_arch_pulse_delay_short(void);


// PROCEDURE: asdf_arch_pulse_delay_long
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Delays a fixed amount of time for keyboard output pulses specified by ASDF_PULSE_DELAY_LONG_MS
void asdf_arch_pulse_delay_long(void);


// PROCEDURE: asdf_arch_tick
// INPUTS: none
// OUTPUTS: returns a 1 if the 1ms timer timed out, 0 otherwise
uint8_t asdf_arch_tick(void);

// PROCEDURE: asdf_arch_send_code
// INPUTS: (keycode_t) code - the code to be output by the keyboard
// OUTPUTS: none
// DESCRIPTION: Takes a character code and outputs the code on a parallel ASCII
// port, with a strobe. This routine could be replaced with UART, I2C, USB, or
// other output mechanism, of course.
void asdf_arch_send_code(asdf_keycode_t code);

// PROCEDURE: asdf_arch_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: sets up all the hardware for the keyboard
void asdf_arch_init(void);

#endif /* !defined (ASDF_ARCH_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
