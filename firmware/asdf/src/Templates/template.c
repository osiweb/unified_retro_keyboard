// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*- 
//
//  Universal Keyboard Project
//  ASDF keyboard firmware
//
//  <FIXME-filename>.c
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


//iring Information:
// Chip: {Microcontroller type and version}
//
// Example: 
// PIN NAME FUNCTION
// 3   AN1  ADC INPUT: Line sense analog input
// 
// 6   A4   INPUT: (T0CK) COUNT DOWN from quadrature decoder.
//          configured to count on rising edge, synced with xtal 
//


//
// Headers
//

#include <version.h>



//
// Global Variable declarations: Use very sparingly.  Used for communication
// with ISR's.  Exceptions should be documented.
//

// Examples:

// run_clock_thread (global uns 8) when this is set to TRUE (by the
// clock_tick() ISR every 20 ms), the main loop performs certain
// actions, and resets the value to FALSE (see main loop comments)
//
uint8 send_count = FALSE;


//
// ISR routines
//

// PROCEDURE:
// INPUTS:
// OUTPUTS:
//
// DESCRIPTION:
//
// SIDE EFFECTS:
//
// NOTES:
//
// COMPLEXITY: 
//

//
// Regular functions
//

// PROCEDURE:
// INPUTS:
// OUTPUTS:
//
// DESCRIPTION:
//
// SIDE EFFECTS:
//
// NOTES:
//
// SCOPE:
//
// COMPLEXITY:
//





// PROCEDURE: main()
//
// Main program loop; invoked at processor startup.
//

main()
{
  // INITIALIZATION SECTION

cold_start:
  

    // re-initialize variables and re-enter control loop, when the "R" command
    // is received

       warm_start:

    // END OF INITIALIZATION SECTION

    // Main Section:

}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

