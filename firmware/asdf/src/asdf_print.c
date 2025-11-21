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
#include <stdarg.h>
#include "asdf.h"
#define NANOPRINTF_IMPLEMENTATION
#include "third_party/nanoprintf.h"

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
static void asdf_print_putchar(int c, void *ctx)
{
  (void) ctx;
  asdf_putc((char) c, NULL);
}

void asdf_print(const char *fmt, ...)
{
  va_list arg_ptr;

  va_start(arg_ptr, fmt);
  npf_vpprintf(asdf_print_putchar, NULL, fmt, arg_ptr);
  va_end(arg_ptr);
}



//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
