// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*- 
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// asdf_keymap_table.c
//
// initialize keymap setup function table
//
// *** This is a special versiof for testing.
// *** Not auto-generated.
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
#include "asdf_keymap_table.h"
#include "test_asdf_keymap_defs.h"

// PROCEDURE: asdf_keymap_setup
//
// INPUTS: (uint8_t) index - index of the keymap setup function to call
// OUTPUTS: none
////
// DESCRIPTION: This function calls the keymap setup function specified
//              by the index.
//
// SIDE EFFECTS: See Description
//
// NOTES: This function is necessary because functions defined in external
// modules are not considered compile-time constants by the C99 standard, so the
// array cannot be initialized with a compile-time declaration.
//
// SCOPE: public
//
// COMPLEXITY: 1
//
void asdf_keymap_setup(uint8_t index) {
  switch(index) {

    default:
    case ASDF_TEST_PLAIN_MAP_INDEX: setup_test_plain_map(); break;
    case ASDF_TEST_CAPS_MAP_INDEX: setup_test_caps_map(); break;
    case ASDF_TEST2_PLAIN_MAP_INDEX: setup_test2_plain_map(); break;
    case ASDF_TEST2_CAPS_MAP_INDEX: setup_test2_caps_map();
      break;

      // keymap assignments for the virtual device tests
    case SINGLE_TESTS_KEYMAP: setup_test_vdevs_single(); break;
    case DOUBLE_ASSIGN_TEST_KEYMAP: setup_test_vdevs_double(); break;
    case TRIPLE_TESTS_KEYMAP: setup_test_vdevs_triple(); break;
    case VCAPS_TEST_KEYMAP: setup_test_vdevs_vcaps();
      break;

      // keymap assignments for the hook mechanism tests
    case ASDF_TEST_DEFAULT_SCANNER_MAP: setup_test_hooks_alt_scanner(); break;
    case ASDF_TEST_ALTERNATE_OUTPUT_MAP: setup_test_hooks_alt_output(); break;
    case ASDF_TEST_EACH_SCAN_MAP: setup_test_hooks_each_scan(); break;
  }
}

// PROCEDURE: asdf_keymap_valid
//
// INPUTS: (uint8_t) index - index of the keymap setup function to check
// OUTPUTS: (uintu_t) returns TRUE (nonzero) if valid, FALSE (0) otherwise
//
// DESCRIPTION: This function returns TRUE if the index corresponds to
//              a valid keymap.
//
// SIDE EFFECTS: none
//
// NOTES:
//
// SCOPE: public
//
// COMPLEXITY: 1
//
uint8_t asdf_keymap_valid(uint8_t index) {
  uint8_t valid = 0;

  switch(index) {
    case ASDF_TEST_PLAIN_MAP_INDEX:
    case ASDF_TEST_CAPS_MAP_INDEX:
    case ASDF_TEST2_PLAIN_MAP_INDEX:
    case ASDF_TEST2_CAPS_MAP_INDEX:

    // keymap assignments for the virtual device tests
    case SINGLE_TESTS_KEYMAP:
    case DOUBLE_ASSIGN_TEST_KEYMAP:
    case TRIPLE_TESTS_KEYMAP:
    case VCAPS_TEST_KEYMAP:

    // keymap assignments for the hook mechanism tests
    case ASDF_TEST_DEFAULT_SCANNER_MAP:
    case ASDF_TEST_ALTERNATE_OUTPUT_MAP:
    case ASDF_TEST_EACH_SCAN_MAP:

      valid = 1;
      break;

    default:
      valid = 0;
    break;
  }

  return valid;
}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

