// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Unified Keyboard Project
// ASDF keyboard firmware
//
// test_asdf_keymap_defs.c
//
// Contains keymap definitions for unit tests
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

#include <test_asdf_keymap_defs.h>
#include "asdf_ascii.h"
#include "asdf_modifiers.h"
#include "asdf_keymaps.h"


static const asdf_keycode_t test_PLAIN_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST_PLAIN_MAP;
static const asdf_keycode_t test_SHIFT_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST_SHIFT_MAP;
static const asdf_keycode_t test_CAPS_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST_CAPS_MAP;
static const asdf_keycode_t test_CTRL_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST_CTRL_MAP;

static const asdf_keycode_t test2_PLAIN_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST2_PLAIN_MAP;
static const asdf_keycode_t test2_SHIFT_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST2_SHIFT_MAP;
static const asdf_keycode_t test2_CAPS_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST2_CAPS_MAP;
static const asdf_keycode_t test2_CTRL_matrix[TEST_NUM_ROWS][TEST_NUM_COLS] = ASDF_TEST2_CTRL_MAP;


void test_keymaps_add_map(const asdf_keycode_t (*matrix)[TEST_NUM_COLS],
                          modifier_index_t modifier_index)
{
  asdf_keymaps_add_map(&matrix[0][0], modifier_index, (uint8_t) TEST_NUM_ROWS,
                       (uint8_t) TEST_NUM_COLS);
}


void setup_test_plain_map(void)
{
  test_keymaps_add_map(&test_PLAIN_matrix[0], MOD_PLAIN_MAP);
  test_keymaps_add_map(test_CAPS_matrix, MOD_CAPS_MAP);
  test_keymaps_add_map(test_SHIFT_matrix, MOD_SHIFT_MAP);
  test_keymaps_add_map(test_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test_caps_map(void)
{
  test_keymaps_add_map(test_PLAIN_matrix, MOD_PLAIN_MAP);
  test_keymaps_add_map(test_CAPS_matrix, MOD_CAPS_MAP);
  test_keymaps_add_map(test_SHIFT_matrix, MOD_SHIFT_MAP);
  test_keymaps_add_map(test_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test2_plain_map(void)
{
  test_keymaps_add_map(test2_PLAIN_matrix, MOD_PLAIN_MAP);
  test_keymaps_add_map(test2_CAPS_matrix, MOD_CAPS_MAP);
  test_keymaps_add_map(test2_SHIFT_matrix, MOD_SHIFT_MAP);
  test_keymaps_add_map(test2_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test2_caps_map(void)
{
  test_keymaps_add_map(test2_PLAIN_matrix, MOD_PLAIN_MAP);
  test_keymaps_add_map(test2_CAPS_matrix, MOD_CAPS_MAP);
  test_keymaps_add_map(test2_SHIFT_matrix, MOD_SHIFT_MAP);
  test_keymaps_add_map(test2_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test_vdevs_map0(void)
{
  setup_test_plain_map();

  asdf_virtual_init();

  /* single assignment */
  asdf_virtual_assign(VOUT1, PHYSICAL_OUT1, V_NOFUNC, 0);

  /* single toggle */
  asdf_virtual_assign(VOUT2, PHYSICAL_OUT2, V_TOGGLE, 0);

  /* single pulse */
  asdf_virtual_assign(VOUT3, PHYSICAL_OUT3, V_PULSE_SHORT, 0);

  /* first of double assignment attempt */
  asdf_virtual_assign(VOUT4, PHYSICAL_LED1, V_NOFUNC, 0);

  /* second of double assignment attempt */
  asdf_virtual_assign(VOUT5, PHYSICAL_LED1, V_NOFUNC, 1);

  asdf_virtual_sync();
}

void setup_test_vdevs_map1(void)
{

  setup_test_caps_map();

  asdf_virtual_init();

  /* Triple assignment */
  asdf_virtual_assign(VOUT1, PHYSICAL_OUT1, V_TOGGLE, 0);
  asdf_virtual_assign(VOUT1, PHYSICAL_OUT2, V_TOGGLE, 1);
  asdf_virtual_assign(VOUT1, PHYSICAL_OUT3, V_TOGGLE, 0);

  asdf_virtual_sync();
}

void setup_test_vdevs_map2(void)
{
  setup_test2_plain_map();

  asdf_virtual_init();

  asdf_virtual_assign(VCAPS_LED, PHYSICAL_LED1, V_NOFUNC, 0);
  asdf_virtual_assign(VSHIFT_LED, PHYSICAL_LED2, V_NOFUNC, 0);
  asdf_virtual_assign(VOUT2, PHYSICAL_OUT3, V_NOFUNC, 0);
  asdf_virtual_assign(VOUT2, ASDF_PHYSICAL_NUM_RESOURCES, V_NOFUNC, 0);

  asdf_virtual_sync();
}

void setup_test_vdevs_map3(void)
{
  setup_test2_caps_map();

  asdf_virtual_init();

  asdf_virtual_assign(VCAPS_LED, PHYSICAL_LED1, V_NOFUNC, 0);
  asdf_virtual_assign(VSHIFT_LED, PHYSICAL_LED2, V_NOFUNC, 0);
  asdf_virtual_assign(VOUT2, PHYSICAL_OUT3, V_NOFUNC, 0);
  asdf_virtual_assign(VOUT2, ASDF_PHYSICAL_NUM_RESOURCES, V_NOFUNC, 0);

  asdf_virtual_sync();
}




//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.
