// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*- 
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// <asdf_print-filename>.c
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


//
// Headers
//
#include <stdio.h>
#include <avr/io.h>
#include "asdf.h"


static FILE ascii_port = FDEV_SETUP_STREAM(asdf_putc, NULL,
                                           _FDEV_SETUP_WRITE);

//
// Regular functions
//

// PROCEDURE: asdf_print
// INPUTS: (*char) fmt - format string
//         va_arglist - list of args for fmt string
// OUTPUTS: none
//
// DESCRIPTION: output to ascii output port using vfprintf()
//
// SIDE EFFECTS: see DESCRIPTION
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_print(char *fmt, ...)                                                       
{                                                                               
   va_list arg_ptr;                                                             
                                                                                
   va_start(arg_ptr, fmt);                                                      
   vfprintf(&ascii_port, fmt, arg_ptr);                                                       
   va_end(arg_ptr);                                                             
}                                                                               



//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

