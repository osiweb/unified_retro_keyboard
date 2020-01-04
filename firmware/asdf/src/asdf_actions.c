// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_actions.c
//
// This file implements actions that are bound to keys in the keymap that don't
// have a clear home in any other module.
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
#include <stdint.h>
#include "asdf_actions.h"
#include "asdf_arch.h"

// PROCEDURE: asdf_screen_clear
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Performs screen clear. This function contains implementation
// independent actions, which may be simply calling the architecture-dependent
// hardware screen clear routine, or could involve a special character output.
//
// SIDE EFFECTS: causes screen clear may occur.  See DESCRIPTION
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_send_screen_clear(void)
{
  asdf_arch_send_screen_clear();
}

// PROCEDURE: asdf_send_reset
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: Performs host reset. This function contains implementation
// independent actions, which may be simply calling the architecture-dependent
// hardware screen clear routine, or could involve a special character output.
//
// SIDE EFFECTS: causes host reset.  See DESCRIPTION
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_send_reset(void)
{
  asdf_arch_send_reset();
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
