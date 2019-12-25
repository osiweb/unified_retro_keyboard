#include <stdint.h>
#include "unity.h"
#include "asdf.h"
#include "asdf_ascii.h"
#include "asdf_modifiers.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"

#define TESTALPHA 'a'
#define TESTNUM '2'

#define TESTMAP(row, col, mapname, mapname2)                                                       \
  do {                                                                                             \
    asdf_keycode_t expected = mapname##_matrix[(row)][(col)];                                      \
    asdf_keycode_t result = asdf_keymaps_get_code((row), (col), MOD_ ## mapname2 ## _MAP);             \
    TEST_ASSERT_EQUAL_INT(expected, result);                                                       \
  } while (0);

#define TEST_VALID_CODE(position) do { \
  coord_t pos = position; \
  TEST_ASSERT_FALSE(pos.row == -1); \
  TEST_ASSERT_FALSE(pos.col == -1); \
  } while (0);

#define TESTPLAIN(row, col, n) TESTMAP((row), (col), PLAIN, n)
#define TESTSHIFT(row, col, n) TESTMAP((row), (col), SHIFT, n)
#define TESTCAPS(row, col, n) TESTMAP((row), (col), CAPS, n)
#define TESTCTRL(row, col, n) TESTMAP((row), (col), CTRL, n)

typedef asdf_keycode_t keycode_matrix_t[ASDF_NUM_ROWS][ASDF_NUM_COLS];

typedef struct {
  int32_t row;
  int32_t col;
} coord_t;


static const keycode_matrix_t PLAIN_matrix = ASCII_PLAIN_MAP;
static const keycode_matrix_t SHIFT_matrix = ASCII_SHIFT_MAP;
static const keycode_matrix_t CAPS_matrix = ASCII_CAPS_MAP;
static const keycode_matrix_t CTRL_matrix = ASCII_CTRL_MAP;

 static coord_t alpha_sample;

static coord_t num_sample;

coord_t *find_code(asdf_keycode_t code)
{
  uint32_t done = 0;
  static coord_t location = { .row = -1, .col = -1 };

  for (uint32_t row = 0; !done && (row < ASDF_NUM_ROWS); row++) {
    for (uint32_t col = 0; !done && (col < ASDF_NUM_COLS); col++) {
      if (PLAIN_matrix[row][col] == code) {
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
}

void tearDown(void) {}


void test_chars_are_in_map(void) {
  TEST_VALID_CODE(alpha_sample);
  TEST_VALID_CODE(num_sample);
}

void plain_map_gives_plain_values(void)
{
  TESTPLAIN(alpha_sample.row, alpha_sample.col, PLAIN);
  TESTPLAIN(num_sample.row, num_sample.col, PLAIN);
}

void shift_map_gives_shift_values(void)
{
  TESTSHIFT(alpha_sample.row, alpha_sample.col, SHIFT);
  TESTSHIFT(num_sample.row, num_sample.col, SHIFT);
}
void caps_map_gives_caps_values(void)
{
  TESTCAPS(alpha_sample.row, alpha_sample.col, CAPS);
  TESTCAPS(num_sample.row, num_sample.col, CAPS);
}
void ctrl_map_gives_ctrl_values(void)
{
  TESTCTRL(alpha_sample.row, alpha_sample.col, CTRL);
  TESTCTRL(num_sample.row, num_sample.col, CTRL);
}


int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_chars_are_in_map);
  RUN_TEST(plain_map_gives_plain_values);
  RUN_TEST(shift_map_gives_shift_values);
  RUN_TEST(caps_map_gives_caps_values);
  RUN_TEST(ctrl_map_gives_ctrl_values);

  return UNITY_END();
}
