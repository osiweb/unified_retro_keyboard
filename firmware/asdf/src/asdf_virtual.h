// -*- mode: C; tab-width: 4 ; indent-tabs-mode: nil -*-
//
// Unfified Keyboard Project
// ASDF keyboard firmware
//
// asdf_virtual.h
//
// Definitions and prototypes for virtual LED and virtual output management.
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

#if !defined(ASDF_VIRTUAL_H)
#define ASDF_VIRTUAL_H


// These are "virtual" output identifiers that can be mapped to the real outputs using
// keymap initializer commands.
typedef enum {
  V_NULL,
  VOUT1,
  VOUT2,
  VOUT3,
  VOUT4,
  VOUT5,
  VOUT6,
  VLED1,
  VLED2,
  VLED3,
  VCAPS_LED,
  VSHIFT_LED,
  NUM_VIRTUAL_OUTPUTS
} asdf_virtual_output_t;

// The asdf_virtual_real_dev_t enumerates real outputs that can be assigned to
// virtual outputs via the asdf_virtual_assign() function. The name is a bit
// confusing, containing virtual and real. The "virtual" part refers to the
// module and the "real_dev" part attempts to clarify that these are the
// hardware outputs implemented by the architecture-specific module.
typedef enum {
  VMAP_NO_OUT = 0,
  VMAP_OUT1,
  VMAP_OUT1_OC,
  VMAP_OUT2,
  VMAP_OUT2_OC,
  VMAP_OUT3,
  VMAP_OUT3_OC,
  VMAP_LED1,
  VMAP_LED2,
  VMAP_LED3,
  NUM_REAL_OUTPUTS
} asdf_virtual_real_dev_t;

typedef enum {
  V_NOFUNC,
  V_SET_HI,
  V_SET_LO,
  V_PULSE,
  V_TOGGLE,
  NUM_VIRTUAL_FUNCTIONS
} asdf_virtual_function_t;

// Each keymap specifies an array of initializer structs to configure virtual
// devices, specifying the mapped real device and initial value.
typedef struct {
  asdf_virtual_output_t virtual_device;
  asdf_virtual_real_dev_t real_device;
  asdf_virtual_function_t function;
  uint8_t initial_value;
} asdf_virtual_initializer_t;

// PROCEDURE: asdf_virtual_action
// INPUTS: (asdf_virtual_output_t) virtual_out: which virtual output to modify
// INPUTS: (asdf_virtual_function_t) function: what function to apply to the virtual output
// OUTPUTS: none
// DESCRIPTION: for each real output mapped to the virtual output, apply the
// specified function.
void asdf_virtual_action(asdf_virtual_output_t virtual_out, asdf_virtual_function_t function);

// PROCEDURE: asdf_virtual_activate
// INPUTS: asdf_virtual_output_t: The virtual device to be activated
// OUTPUTS: none
// DESCRIPTION: for each real output mapped to the virtual output, apply the
// function assigned to the virtual output at initialization.
void asdf_virtual_activate(asdf_virtual_output_t virtual_out);

// PROCEDURE: asdf_virtual_init
// INPUTS: initializers
// OUTPUTS: none
// DESCRIPTION: Initializes the LED and output mapping
void asdf_virtual_init(asdf_virtual_initializer_t *const initializer_list);


#endif /* !defined (ASDF_VIRTUAL_H) */

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
