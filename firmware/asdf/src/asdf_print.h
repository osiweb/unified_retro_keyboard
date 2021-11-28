// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_print.h
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

#if !defined (ASDF_PRINT_H)
#define ASDF_PRINT_H

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

// PROCEDURE: asdf_print
// INPUTS: (*char) fmt - format string
//         va_arglist - list of args for fmt string
// OUTPUTS: none
// DESCRIPTION: output to ascii output port using vfprintf()
// COMPLEXITY: 1
void asdf_print(const char *fmt, ...);

#endif /* !defined (ASDF_PRINT_H) */
