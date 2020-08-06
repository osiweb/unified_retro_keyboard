// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// main.c
//
// main program loop.  Initialize hardware.  Schedule key scans and i/o.
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

#include <stdint.h>
#include "asdf.h"
#include "asdf_arch.h"
#include "asdf_buffer.h"
#include "asdf_hook.h"

// PROCEDURE: main
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Initialize hardware, Schedule key scans and i/o
//
// SIDE EFFECTS: See above
//
// NOTES: This code just initializes the hardware, and then loops. The loop
// includes:
//
//     - Check every 1 ms (or whatever the tick is set to), calls the keyboard
//       scan routine.
//
//     - Check every pass through if any characters are buffered to send. If so,
//       send them.
//
// This is not the most efficient use of the hardware, but is an example of how
// the keyboard scanner is used. Of course, this loop can be replaced with an
// RTOS process as well. If an RTOS is used, then asdf_buffer can be modified
// to use RTOS message queues instead of an internal buffer, or to keep the
// internal buffer and use a counting semaphore to indicate characters in the
// buffer.
//
// If you are adding special functions when using an RTOS, make sure the
// functions do not block, or do any heavy computation. Rather, they should be
// small and pass messages to appropriate processes to handle the activities.
//
// COMPLEXITY: 2
//
int main(void)
{
  // initialize the hardware:
  asdf_arch_init();

  // initialize the keyboard logic:
  asdf_init();

  while (1) {

    if (asdf_arch_tick()) {
      asdf_keycode_t code = asdf_next_code();

      if (code != ASDF_INVALID_CODE) {
         void (*output_function)(asdf_keycode_t) =
         (void (*)(asdf_keycode_t)) asdf_hook_get(ASDF_HOOK_OUTPUT);
        (*output_function)(code);
      }
      asdf_keyscan();
    }
  }
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
