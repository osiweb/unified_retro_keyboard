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

#include "asdf.h"

#define FLASH
#define FLASH_READ (a) (*(a))
#define FLASH_READ_MATRIX_ELEMENT(mat,row,col) (mat)[(row)][(col)]

// PROCEDURE: asdf_arch_read_row
// INPUTS: (uint8_t) row: the row number to be scanned
// OUTPUTS: returns a word containing the active (pressed) columns
// DESCRIPTION: Outputs the argument to the ROW port, then reads the column port
// and returns the value. The value is a binary representation of the keys
// pressed within the row, with 1=pressed, 0=released.
asdf_cols_t asdf_arch_read_row(uint8_t row);

// PROCEDURE: asdf_arch_send_screen_clear
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Toggles the SCREEN_CLEAR output.
void asdf_arch_send_screen_clear(void);

// PROCEDURE: asdf_arch_send_reset
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: Toggles the SCREEN_CLEAR output.
void asdf_arch_send_reset(void);

// PROCEDURE: asdf_arch_init
// INPUTS: none
// OUTPUTS: none
// DESCRIPTION: sets up all the hardware for the keyboard
void asdf_arch_init(void);

// PROCEDURE: asdf_arch_caps_led
// INPUTS: (uint8_t) led_state: nonzero value turns on LED, zero turns off LED
// OUTPUTS: none
// DESCRIPTION: Controls the CAPSLOCK LED.  Test version is empty.
void asdf_arch_caps_led(uint8_t led_status);

#endif // !defined (ASDF_ARCH_H)

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.



