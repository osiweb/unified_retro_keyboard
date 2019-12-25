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
#include "asdf_arch.h"



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
void asdf_arch_init(void) {}

// PROCEDURE: asdf_arch_send_screen_clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Toggles the SCREEN_CLEAR output.
//
// SIDE EFFECTS: see DESCRIPTION
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_send_screen_clear(void) {}

// PROCEDURE: asdf_arch_send_reset
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Toggles the SCREEN_CLEAR output.
//
// SIDE EFFECTS: see DESCRIPTION
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_arch_send_reset(void) {}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
//
