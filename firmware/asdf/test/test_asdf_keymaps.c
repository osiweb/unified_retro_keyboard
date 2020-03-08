#include <stdint.h>
#include <stdarg.h>
#include "asdf_arch.h"
#include "unity.h"
#include "asdf.h"
#include "asdf_ascii.h"
#include "asdf_modifiers.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"

#define TESTALPHA 'a'
#define TESTNUM '2'
#define TESTKEYMAP_TAG PLAIN_MATRIX_1
#define NUM_DIPSWITCHES 4

// row: row number
// col: column number
// keymap_name: id of the file defining the matrix to be used.
// defnum: numerical order of the file defining the matrix to be used.
// mapindex: matrix of keymaps to be used (contains all modifier maps for the matrix).
// modifier_name: name of the modifier to be accessed within the map.
#define TESTMAP(row, col, keymap_name, defnum, mapindex, modifier_name)                            \
  do {                                                                                             \
    asdf_keymaps_select_keymap(ASDF_##mapindex##_MAP_INDEX);                                       \
    asdf_keycode_t expected = keymap_name##_##modifier_name##_matrix[(row)][(col)];                \
    asdf_keycode_t result = asdf_keymaps_get_code((row), (col), MOD_##modifier_name##_MAP);        \
    asdf_keycode_t map_id = asdf_keymaps_get_code(0, 0, MOD_##modifier_name##_MAP);                \
    TEST_ASSERT_EQUAL_INT32((uint32_t) expected, (uint32_t) result);                               \
    TEST_ASSERT_EQUAL_INT32((uint32_t) modifier_name##_MATRIX_##defnum, (uint32_t) map_id);        \
  } while (0)

#define TEST0MAP(row, col, modifier) TESTMAP(row, col, test, 1, TEST_PLAIN, modifier)
#define TEST1MAP(row, col, modifier) TESTMAP(row, col, test, 1, TEST_CAPS, modifier)
#define TEST2MAP(row, col, modifier) TESTMAP(row, col, test2, 2, TEST2_PLAIN, modifier)
#define TEST3MAP(row, col, modifier) TESTMAP(row, col, test2, 2, TEST2_CAPS, modifier)


#define TEST_VALID_CODE(position)                                                                  \
  do {                                                                                             \
    coord_t pos = position;                                                                        \
    TEST_ASSERT_FALSE(pos.row == -1);                                                              \
    TEST_ASSERT_FALSE(pos.col == -1);                                                              \
  } while (0)

// check against the "test" keymaps
#define TEST0PLAIN(row, col) TEST0MAP((row), (col), PLAIN)
#define TEST0SHIFT(row, col) TEST0MAP((row), (col), SHIFT)
#define TEST0CAPS(row, col) TEST0MAP((row), (col), CAPS)
#define TEST0CTRL(row, col) TEST0MAP((row), (col), CTRL)

#define TEST1PLAIN(row, col) TEST1MAP((row), (col), PLAIN)
#define TEST1SHIFT(row, col) TEST1MAP((row), (col), SHIFT)
#define TEST1CAPS(row, col) TEST1MAP((row), (col), CAPS)
#define TEST1CTRL(row, col) TEST1MAP((row), (col), CTRL)

// check against the "test2" keymaps

#define TEST2PLAIN(row, col) TEST2MAP((row), (col), PLAIN)
#define TEST2SHIFT(row, col) TEST2MAP((row), (col), SHIFT)
#define TEST2CAPS(row, col) TEST2MAP((row), (col), CAPS)
#define TEST2CTRL(row, col) TEST2MAP((row), (col), CTRL)

#define TEST3PLAIN(row, col) TEST3MAP((row), (col), PLAIN)
#define TEST3SHIFT(row, col) TEST3MAP((row), (col), SHIFT)
#define TEST3CAPS(row, col) TEST3MAP((row), (col), CAPS)
#define TEST3CTRL(row, col) TEST3MAP((row), (col), CTRL)

typedef struct {
  int32_t row;
  int32_t col;
} coord_t;

// The dip switch positions do not need to reflect real hardware. These
// positions reflect the organization of the test keymaps, to ensure that tools
// used to place the codes are functioning and are being properly used.


ASDF_KEYMAP_DECLARATIONS;

// keymap coordinates for special functions
static coord_t alpha_sample;
static coord_t num_sample;
static coord_t keymap_tag;

uint32_t max(uint8_t first, uint8_t second)
{
  uint32_t max = first;
  if (second > max) {
    max = second;
  }
  return max;
}

coord_t *find_code(asdf_keycode_t code)
{
  uint32_t done = 0;
  static coord_t location = { .row = -1, .col = -1 };

  for (uint32_t row = 0; !done && (row < ASDF_NUM_ROWS); row++) {
    for (uint32_t col = 0; !done && (col < ASDF_NUM_COLS); col++) {
      if (test_PLAIN_matrix[row][col] == code) {
        done = 1;
        location.row = row;
        location.col = col;
      }
    }
  }
  return &location;
}


void setUp(void)
{
  coord_t *temp;

  asdf_keymaps_init();

  temp = find_code(TESTALPHA);
  alpha_sample = *temp;

  temp = find_code(TESTNUM);
  num_sample = *temp;

  temp = find_code(TESTKEYMAP_TAG);
  keymap_tag = *temp;
}

void tearDown(void) {}


// set a keymap using the asdf_keymap dip-switch functions
void complicated_set_keymap(uint8_t mapnum)
{
  void (*set_funcs[])(void) = { &asdf_keymaps_map_select_0_set, &asdf_keymaps_map_select_1_set,
                                &asdf_keymaps_map_select_2_set, &asdf_keymaps_map_select_3_set };
  void (*clr_funcs[])(void) = { &asdf_keymaps_map_select_0_clear, &asdf_keymaps_map_select_1_clear,
                                &asdf_keymaps_map_select_2_clear,
                                &asdf_keymaps_map_select_3_clear };

  for (uint8_t i = 0; i < NUM_DIPSWITCHES; i++) {
    if (mapnum & 1) {
      set_funcs[i]();
    }
    else {
      clr_funcs[i]();
    }
    mapnum >>= 1;
  }
}

// the next two test check the preprocessor mechanism for allocating space for
// the largest defined keymap

// check to see that the largest number of columns is detected.
void test_num_cols_is_max_cols(void)
{
  TEST_ASSERT_EQUAL_INT32(max(ASDF_TEST_NUM_COLS, ASDF_TEST2_NUM_COLS), ASDF_NUM_COLS);
}

// check to see that the largest number of rows is detected.
void test_num_rows_is_max_rows(void)
{
  TEST_ASSERT_EQUAL_INT32(max(ASDF_TEST_NUM_ROWS, ASDF_TEST2_NUM_ROWS), ASDF_NUM_ROWS);
}

void test_chars_are_in_map(void)
{
  TEST_VALID_CODE(alpha_sample);
  TEST_VALID_CODE(num_sample);
}

void keymap0_plain_gives_plain_values(void)
{
  TEST0PLAIN(alpha_sample.row, alpha_sample.col);
  TEST0PLAIN(num_sample.row, num_sample.col);
}

void keymap0_shift_gives_shift_values(void)
{
  TEST0SHIFT(alpha_sample.row, alpha_sample.col);
  TEST0SHIFT(num_sample.row, num_sample.col);
}
void keymap0_caps_gives_caps_values(void)
{
  TEST0CAPS(alpha_sample.row, alpha_sample.col);
  TEST0CAPS(num_sample.row, num_sample.col);
}
void keymap0_ctrl_gives_ctrl_values(void)
{
  TEST0CTRL(alpha_sample.row, alpha_sample.col);
  TEST0CTRL(num_sample.row, num_sample.col);
}

void keymap2_plain_gives_plain_values(void)
{
  TEST2PLAIN(alpha_sample.row, alpha_sample.col);
  TEST2PLAIN(num_sample.row, num_sample.col);
}

void keymap2_shift_gives_shift_values(void)
{
  TEST2SHIFT(alpha_sample.row, alpha_sample.col);
  TEST2SHIFT(num_sample.row, num_sample.col);
}
void keymap2_caps_gives_caps_values(void)
{
  TEST2CAPS(alpha_sample.row, alpha_sample.col);
  TEST2CAPS(num_sample.row, num_sample.col);
}
void keymap2_ctrl_gives_ctrl_values(void)
{
  TEST2CTRL(alpha_sample.row, alpha_sample.col);
  TEST2CTRL(num_sample.row, num_sample.col);
}


void keymap1_capsmap_plain_maps_to_caps(void)
{
  // set bit 0 to select keymap 1
  asdf_keymaps_map_select_0_set();
  TEST1CAPS(alpha_sample.row, alpha_sample.col);
  TEST1CAPS(num_sample.row, num_sample.col);
}

void dip_switch_codes_are_in_last_row_test1_map(void)
{
  coord_t dip_switches[NUM_DIPSWITCHES] = { { .row = ASDF_LAST_ROW, .col = 0 },
                                            { .row = ASDF_LAST_ROW, .col = 1 },
                                            { .row = ASDF_LAST_ROW, .col = 2 },
                                            { .row = ASDF_LAST_ROW, .col = 3 } };
  for (uint8_t i = 0; i < NUM_DIPSWITCHES; i++) {
    asdf_keycode_t code =
      asdf_keymaps_get_code(dip_switches[i].row, dip_switches[i].col, ASDF_TEST_PLAIN_MAP_INDEX);
    TEST_ASSERT_EQUAL_INT32((uint32_t) code, (uint32_t)(ACTION_MAPSEL_0 + i));
  }
}

void dip_switch_codes_are_in_last_row_test2_map(void)
{
  coord_t dip_switches[NUM_DIPSWITCHES] = { { .row = ASDF_LAST_ROW, .col = 0 },
                                            { .row = ASDF_LAST_ROW, .col = 1 },
                                            { .row = ASDF_LAST_ROW, .col = 2 },
                                            { .row = ASDF_LAST_ROW, .col = 3 } };
  for (uint8_t i = 0; i < NUM_DIPSWITCHES; i++) {
    asdf_keycode_t code =
      asdf_keymaps_get_code(dip_switches[i].row, dip_switches[i].col, ASDF_TEST2_PLAIN_MAP_INDEX);
    TEST_ASSERT_EQUAL_INT32((uint32_t) code, (uint32_t)(ACTION_MAPSEL_0 + i));
  }
}

void dip_switch_properly_sets_bits(void)
{
  char message[80];


  sprintf(message, "Map 0 is %d.", PLAIN_MATRIX_1);
  TEST_MESSAGE(message);

  for (uint8_t i = 0; i < ASDF_NUM_KEYMAPS; i++) {
    asdf_keycode_t expected;
    asdf_keycode_t result;
    asdf_keymaps_select_keymap(i);
    expected = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);

    // set all keymap bits to '0'
    asdf_keymaps_select_keymap(0);
    complicated_set_keymap(i);
    result = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);

    TEST_ASSERT_EQUAL_INT32(expected, result);
  }
}


void dip_switch_properly_clears_bits(void)
{
  uint8_t mask = 0;
  uint8_t next = 1;
  char message[80];


  sprintf(message, "Map 0 is %d.", PLAIN_MATRIX_1);
  TEST_MESSAGE(message);
  
  // calculate word with most 1's less than (or equal to) ASDF_NUM_KEYMAPS
  while (next < ASDF_NUM_KEYMAPS) {
    mask = next;
    next = (next << 1) | 1;
  }
  for (uint8_t i = 0; i < ASDF_NUM_KEYMAPS; i++) {
    asdf_keycode_t expected;
    asdf_keycode_t result;
    asdf_keymaps_select_keymap(i);
    expected = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);

    // set as many keymap bits to '1' as possible.
    asdf_keymaps_select_keymap(mask);
    complicated_set_keymap(i);
    result = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);
    TEST_ASSERT_EQUAL_INT32(expected, result);
  }
}


void dip_switch_invalid_keymap_has_no_effect(void)
{
  asdf_keycode_t map_id;

  // First, assert that changing to matrix 2 works:
  asdf_keymaps_select_keymap(ASDF_TEST2_PLAIN_MAP_INDEX);
  map_id = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);
  TEST_ASSERT_EQUAL_INT32(PLAIN_MATRIX_2, map_id);

  // assert that resetting keymap to 0 works:
  asdf_keymaps_select_keymap(0);
  map_id = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);
  TEST_ASSERT_EQUAL_INT32(PLAIN_MATRIX_1, map_id);

  // selecting one above the highest keymap should have no effect
  asdf_keymaps_select_keymap(ASDF_NUM_KEYMAPS);
  map_id = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);
  TEST_ASSERT_EQUAL_INT32(PLAIN_MATRIX_1, map_id);

  // selecting one above the highest keymap should have no effect
  map_id = asdf_keymaps_get_code(keymap_tag.row, keymap_tag.col, MOD_PLAIN_MAP);
  asdf_keymaps_select_keymap(UINT8_MAX);
  TEST_ASSERT_EQUAL_INT32(PLAIN_MATRIX_1, map_id);

}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_num_rows_is_max_rows);
  RUN_TEST(test_num_cols_is_max_cols);
  RUN_TEST(test_chars_are_in_map);
  RUN_TEST(keymap0_plain_gives_plain_values);
  RUN_TEST(keymap0_shift_gives_shift_values);
  RUN_TEST(keymap0_caps_gives_caps_values);
  RUN_TEST(keymap0_ctrl_gives_ctrl_values);
  RUN_TEST(keymap2_plain_gives_plain_values);
  RUN_TEST(keymap2_shift_gives_shift_values);
  RUN_TEST(keymap2_caps_gives_caps_values);
  RUN_TEST(keymap2_ctrl_gives_ctrl_values);
  RUN_TEST(keymap1_capsmap_plain_maps_to_caps);
  RUN_TEST(dip_switch_codes_are_in_last_row_test1_map);
  RUN_TEST(dip_switch_codes_are_in_last_row_test2_map);
  RUN_TEST(dip_switch_properly_clears_bits);
  RUN_TEST(dip_switch_properly_sets_bits);
  RUN_TEST(dip_switch_invalid_keymap_has_no_effect);
  return UNITY_END();
}
