// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*- 
//
//  Universal Keyboard Project
//  ASDF keyboard firmware
//
//  asdf_config.h
//
// This file gathers configuration parameters related to the user-detectable
// keyboard experience. For example, put key debounce times, repeat rates,
// buffer sized, baud rates, etc. here. Details such as processor clock speed,
// etc. should go in the architecture-dependent files. System details such as
// number of buffer handles, etc. should go with the appropriate module, but
// certain buffer sized may go here if they can affect the user experience (such
// as how long a macro can be).
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

#if !defined (CONFIG_H)
#define CONFIG_H

#define ASDF_POSITIVE_POLARITY 0
#define ASDF_NEGATIVE_POLARITY (~ASDF_POSITIVE_POLARITY)

// data polarity is positive (inactive is low, active is high)
#define ASDF_DEFAULT_DATA_POLARITY ASDF_POSITIVE_POLARITY

// Strobe polarity is positive (inactive is low, active is high)
#define ASDF_DEFAULT_STROBE_POLARITY ASDF_POSITIVE_POLARITY

// RESET output polarity is negative (inactive is high, active is low)
#define ASDF_DEFAULT_RESET_POLARITY ASDF_NEGATIVE_POLARITY

// SCREEN_CLEAR output polarity is positive (inactive is low, active is high)
#define ASDF_DEFAULT_SCREEN_CLEAR_POLARITY ASDF_POSITIVE_POLARITY


// size of the keycode output buffer.
#define ASDF_KEYCODE_BUFFER_SIZE 16

// key debounce period (in msec)
#define ASDF_DEBOUNCE_TIME_MS 10

// Autorepeat default behavior. Set to REPEAT_AUTO for default autorepeat.
// Set to REPEAT_OFF for default no autorepeat by default.
#define ASDF_DEFAULT_REPEAT_STATE REPEAT_AUTO

// time to hold down a key in milliseconds before autorepeat starts
#define ASDF_AUTOREPEAT_TIME_MS 525     // 525 msec.

// time between repeats of a character with repeat key held, or in autorepeat (milliseconds)
#define ASDF_REPEAT_TIME_MS (1000 / 15) // l5 characters per sec.

// duration of keyboard output pulses (RESET, SCREEN CLEAR, BREAK, etc.)
#define ASDF_PULSE_DELAY_US 100

// DEFAULT value of keyboard outputs
#define ASDF_VIRTUAL_OUT_DEFAULT_VALUE 1 // High if not used.

#endif /* !defined (CONFIG_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

