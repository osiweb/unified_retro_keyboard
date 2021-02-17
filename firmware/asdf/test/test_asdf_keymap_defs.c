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


static const asdf_keycode_matrix_t test_PLAIN_matrix = ASDF_TEST_PLAIN_MAP;
static const asdf_keycode_matrix_t test_SHIFT_matrix = ASDF_TEST_SHIFT_MAP;
static const asdf_keycode_matrix_t test_CAPS_matrix = ASDF_TEST_CAPS_MAP;
static const asdf_keycode_matrix_t test_CTRL_matrix = ASDF_TEST_CTRL_MAP;

static const asdf_keycode_matrix_t test2_PLAIN_matrix = ASDF_TEST2_PLAIN_MAP;
static const asdf_keycode_matrix_t test2_SHIFT_matrix = ASDF_TEST2_SHIFT_MAP;
static const asdf_keycode_matrix_t test2_CAPS_matrix = ASDF_TEST2_CAPS_MAP;
static const asdf_keycode_matrix_t test2_CTRL_matrix = ASDF_TEST2_CTRL_MAP;


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


void setup_test_plain_map(void)
{
  asdf_keymaps_add_map(ASDF_TEST_PLAIN_MAP_INDEX, &test_PLAIN_matrix, MOD_PLAIN_MAP);
  asdf_keymaps_add_map(ASDF_TEST_PLAIN_MAP_INDEX, &test_CAPS_matrix, MOD_CAPS_MAP);
  asdf_keymaps_add_map(ASDF_TEST_PLAIN_MAP_INDEX, &test_SHIFT_matrix, MOD_SHIFT_MAP);
  asdf_keymaps_add_map(ASDF_TEST_PLAIN_MAP_INDEX, &test_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test_caps_map(void)
{
  asdf_keymaps_add_map(ASDF_TEST_CAPS_MAP_INDEX, &test_PLAIN_matrix, MOD_PLAIN_MAP);
  asdf_keymaps_add_map(ASDF_TEST_CAPS_MAP_INDEX, &test_CAPS_matrix, MOD_CAPS_MAP);
  asdf_keymaps_add_map(ASDF_TEST_CAPS_MAP_INDEX, &test_SHIFT_matrix, MOD_SHIFT_MAP);
  asdf_keymaps_add_map(ASDF_TEST_CAPS_MAP_INDEX, &test_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test2_plain_map(void)
{
  asdf_keymaps_add_map(ASDF_TEST2_PLAIN_MAP_INDEX, &test2_PLAIN_matrix, MOD_PLAIN_MAP);
  asdf_keymaps_add_map(ASDF_TEST2_PLAIN_MAP_INDEX, &test2_CAPS_matrix, MOD_CAPS_MAP);
  asdf_keymaps_add_map(ASDF_TEST2_PLAIN_MAP_INDEX, &test2_SHIFT_matrix, MOD_SHIFT_MAP);
  asdf_keymaps_add_map(ASDF_TEST2_PLAIN_MAP_INDEX, &test2_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test2_caps_map(void)
{
  asdf_keymaps_add_map(ASDF_TEST2_CAPS_MAP_INDEX, &test2_PLAIN_matrix, MOD_PLAIN_MAP);
  asdf_keymaps_add_map(ASDF_TEST2_CAPS_MAP_INDEX, &test2_CAPS_matrix, MOD_CAPS_MAP);
  asdf_keymaps_add_map(ASDF_TEST2_CAPS_MAP_INDEX, &test2_SHIFT_matrix, MOD_SHIFT_MAP);
  asdf_keymaps_add_map(ASDF_TEST2_CAPS_MAP_INDEX, &test2_CTRL_matrix, MOD_CTRL_MAP);
}

void setup_test_devs1(void)
{
#define ASDF_TEST_KEYMAP_INITIALIZER_1                                                             \
  {                                                                                                \
    
  asdf_virtual_init();
  /* Single assignment */                       \

  .virtual_device = VOUT1,                                              \
      .physical_device = PHYSICAL_OUT1,                                                            \
      .function = V_NOFUNC,                                                                        \
      .initial_value = 0,                                                                          \
    },                                                                                             \
      {                                                                                            \
        /* single toggle */                                                                        \
        .virtual_device = VOUT2,                                                                   \
        .physical_device = PHYSICAL_OUT2,                                                          \
        .function = V_TOGGLE,                                                                      \
        .initial_value = 0,                                                                        \
      },                                                                                           \
      {                                                                                            \
        /* single pulse */                                                                         \
        .virtual_device = VOUT3,                                                                   \
        .physical_device = PHYSICAL_OUT3,                                                          \
        .function = V_PULSE_SHORT,                                                                 \
        .initial_value = 0,                                                                        \
      },                                                                                           \
      { /* first of double assignment attempt */                                                   \
        .virtual_device = VOUT4,                                                                   \
        .physical_device = PHYSICAL_LED1,                                                          \
        .initial_value = 0                                                                         \
      },                                                                                           \
    { /* second of double assignment attempt */                                                    \
      .virtual_device = VOUT5, .physical_device = PHYSICAL_LED1, .initial_value = 1                \
    }                                                                                              \
  }

  
}

void setup_test_devs2(void)
{
  #define ASDF_TEST_KEYMAP_INITIALIZER_2                                                             \
  {                                                                                                \
    {                                                                                              \
      /* Triple assignment */                                                                      \
      .virtual_device = VOUT1,                                                                     \
      .physical_device = PHYSICAL_OUT1,                                                            \
      .function = V_TOGGLE,                                                                        \
      .initial_value = 0,                                                                          \
    },                                                                                             \
      {                                                                                            \
        .virtual_device = VOUT1,                                                                   \
        .physical_device = PHYSICAL_OUT2,                                                          \
        .function = V_TOGGLE,                                                                      \
        .initial_value = 1,                                                                        \
      },                                                                                           \
    {                                                                                              \
      .virtual_device = VOUT1, .physical_device = PHYSICAL_OUT3, .function = V_TOGGLE,             \
      .initial_value = 0,                                                                          \
    }                                                                                              \
  }

}


//-------|---------|---------+---------+---------+---------+---------+---------+
// Above line is 80 columns, and should display completely in the editor.

