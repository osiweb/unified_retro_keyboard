// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_hook.c
//
// This file contains code to allow function "hooks" to be specified in the
// keymap files, so that the keymap can determine the handline of certain
// functions, such as keyboard scanner, output (parallel, serial, USB, etc.),
// keyboard setup (e.g., set capslock or emulate other keypresses), or specify
// functions to be run at every keyscan. The keyboard logic code access the
// functionality via the hooks module rather than directly calling scanning
// functions, etc.
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
#include <stddef.h>
#include "asdf_arch.h"
#include "asdf_hook.h"
#include "asdf_keymap_defs.h"


// hooks_table[] contains all the function hooks. The entry for each ID contains
// a pointer to the first in the list of functions (if any) assigned to the hook
// ID.
asdf_hook_function_t hook_map[ASDF_NUM_HOOKS];

// PROCEDURE: asdf_hook_null_func
// INPUTS: none
// OUTPUTS: none
//
// DESCRIPTION: dummy function, default hook for all but output and scanner.
//
// SIDE EFFECTS: none
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 1
//
void asdf_hook_null_func(void) {}


// PROCEDURE: asdf_hook_valid_id
// INPUTS: (asdf_hook_id_t) hook_it: ID of the hook to be tested
// OUTPUTS: returns true (1) if the hook ID is valid, false (0) if not valid.
//
// DESCRIPTION: test to see if hooks ID is valid (i.e., within the valid range)
//
// SIDE EFFECTS: none
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 1
//
static uint8_t asdf_hook_valid_id(asdf_hook_id_t id)
{
  return (id > ASDF_HOOK_NULL && id < ASDF_NUM_HOOKS);
}

// PROCEDURE: asdf_hook_execute
// INPUTS: (asdf_hook_id_t) hook_id: The hook for which to execute the attached
// function.
//
// OUTPUTS: none

// DESCRIPTION: if the hook ID is valid, then execute the function attached to the hook.
//
// SIDE EFFECTS: variable depending on the hooks.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 2
//
void asdf_hook_execute(asdf_hook_id_t hook_id)
{
  if (asdf_hook_valid_id(hook_id)) {
    hook_map[hook_id]();
  }
}

// PROCEDURE: asdf_hook_get
// INPUTS: (asdf_hook_id_t) hook_id: The hook for which to retrieve the attached
// function.
// OUTPUTS: none

// DESCRIPTION: if the hook ID is valid, then retrieve the function attached to the hook.
//
// SIDE EFFECTS: variable depending on the hooks.
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 2
//
asdf_hook_function_t asdf_hook_get(asdf_hook_id_t hook_id)
{
  return asdf_hook_valid_id(hook_id) ? hook_map[hook_id] : asdf_hook_null_func;
}

// PROCEDURE: asdf_hook_assign
// INPUTS: (asdf_hook_id_t) hook_id: The hook for which to execute attache functions.
//         (asdf_hook_function_t) func: function to be attached to the hook.
//
// OUTPUTS: none
//
// DESCRIPTION: If the hook ID is valid, map the function to the hook ID.
// Ignore if not valid.
//
// SIDE EFFECTS: see above.
//
// NOTES:
//
// SCOPE: private
//
// COMPLEXITY: 2
//
static void asdf_hook_assign(asdf_hook_id_t hook_id, asdf_hook_function_t func)
{
  if (asdf_hook_valid_id(hook_id)) {
    hook_map[hook_id] = func;
  }
}

// PROCEDURE: asdf_hook_init
// INPUTS: (asdf_hook_initializer_t *) initializer_list - contains the hook
//         initializer list for the selected keymap.
//
// OUTPUTS: none
//
// DESCRIPTION: Initializes function hooks for the selected keymap. If a
// function is assigned to the "KEYMAP_SETUP" hook, then execute the function.
// There is no actual slot where KEYMAP_SETUP functions are stored.
//
// SIDE EFFECTS: see above
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 4
//
void asdf_hook_init(asdf_hook_initializer_t *const initializer_list)
{
  // initialize hooks to null function
  for (uint8_t i = 0; i < ASDF_NUM_HOOKS; i++) {
    hook_map[i] = asdf_hook_null_func;
  }

  hook_map[ASDF_HOOK_SCANNER] = (asdf_hook_function_t) ASDF_ARCH_DEFAULT_SCANNER;
  hook_map[ASDF_HOOK_OUTPUT] = (asdf_hook_function_t) ASDF_ARCH_DEFAULT_OUTPUT;

  // run through the keymap specific setup
  for (uint8_t i = 0; i < ASDF_KEYMAP_HOOK_INITIALIZER_LENGTH; i++) {
    asdf_hook_id_t id = initializer_list[i].hook_id;

    if (ASDF_HOOK_KEYMAP_SETUP == id) {
      initializer_list[i].hook_func();
    }
    else {
      asdf_hook_assign(initializer_list[i].hook_id, initializer_list[i].hook_func);
    }
  }
}

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
