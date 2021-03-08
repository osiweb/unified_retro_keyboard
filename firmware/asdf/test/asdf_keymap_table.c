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

#include "asdf_keymap_table.h"
#include "test_asdf_keymap_defs.h"

asdf_keymap_setup_function_t keymap_setup_function_lookup_table[ASDF_NUM_KEYMAPS] = {
  [ASDF_TEST_PLAIN_MAP_INDEX] = setup_test_plain_map,
  [ASDF_TEST_CAPS_MAP_INDEX] = setup_test_caps_map,
  [ASDF_TEST2_PLAIN_MAP_INDEX] = setup_test2_plain_map,
  [ASDF_TEST2_CAPS_MAP_INDEX] = setup_test2_caps_map,
  
  // keymap assignments for the virtual device tests
  [SINGLE_TESTS_KEYMAP] = &setup_test_vdevs_single,
  [DOUBLE_ASSIGN_TEST_KEYMAP] = &setup_test_vdevs_double,
  [TRIPLE_TESTS_KEYMAP] = setup_test_vdevs_triple,
  [VCAPS_TEST_KEYMAP] = setup_test_vdevs_vcaps,

  // keymap assignments for the hook mechanism tests
  [ASDF_TEST_DEFAULT_SCANNER_MAP] = setup_test_hooks_alt_scanner,
  [ASDF_TEST_ALTERNATE_OUTPUT_MAP] = setup_test_hooks_alt_output,
  [ASDF_TEST_EACH_SCAN_MAP] = setup_test_hooks_each_scan,
};

//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

