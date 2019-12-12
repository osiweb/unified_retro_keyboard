#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "unity.h"
#include "asdf.h"
#include "asdf_ascii.h"
#include "asdf_modifiers.h"
#include "asdf_keymaps.h"
#include "asdf_buffer.h"
#include "asdf_repeat.h"

#define A 'a'
#define B 'b'

#define TEST_STRING "abcdefghijklmnop"

#define NUM_REPEATS (ASDF_KEYCODE_BUFFER_SIZE - 2)

#define TESTMAP(row, col, mapname, mapname2)                                                       \
  do {                                                                                             \
    asdf_keycode_t expected = mapname##_matrix[(row)][(col)];                                      \
    asdf_keycode_t result = asdf_keymaps_get_code((row), (col), MOD_##mapname2##_MAP);             \
    TEST_ASSERT_EQUAL_INT(expected, result);                                                       \
  } while (0);

#define TESTPLAIN(row, col, n) TESTMAP((row), (col), PLAIN, n)
#define TESTSHIFT(row, col, n) TESTMAP((row), (col), SHIFT, n)
#define TESTCAPS(row, col, n) TESTMAP((row), (col), CAPS, n)
#define TESTCTRL(row, col, n) TESTMAP((row), (col), CTRL, n)

typedef asdf_keycode_t keycode_matrix_t[ASDF_NUM_ROWS][ASDF_NUM_COLS];

const char test_string[] = TEST_STRING;

const asdf_keycode_t key_a = A;
const asdf_keycode_t key_b = B;

typedef struct {
  int32_t row;
  int32_t col;
} coord_t;


static const keycode_matrix_t PLAIN_matrix = ASCII_PLAIN_MAP;
static const keycode_matrix_t SHIFT_matrix = ASCII_SHIFT_MAP;
static const keycode_matrix_t CAPS_matrix = ASCII_CAPS_MAP;
static const keycode_matrix_t CTRL_matrix = ASCII_CTRL_MAP;

static uint32_t key_matrix[ASDF_NUM_ROWS];


void setUp(void)
{
  asdf_buffer_init();
  asdf_init();

  // initialize simulated key matrix
  for (uint32_t i = 0; i < ASDF_NUM_ROWS; i++) {
    key_matrix[i] = 0;
  }
}

void tearDown(void) {}

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


asdf_keycode_t shifted(asdf_keycode_t code)
{
  coord_t *location = find_code(code);
  return SHIFT_matrix[location->row][location->col];
}

asdf_keycode_t caps(asdf_keycode_t code)
{
  coord_t *xy = find_code(code);
  return CAPS_matrix[xy->row][xy->col];
}

asdf_keycode_t ctrl(asdf_keycode_t code)
{
  coord_t *xy = find_code(code);
  return CTRL_matrix[xy->row][xy->col];
}


void keyscan_delay(int32_t ticks)
{
  for (; ticks; ticks--) {
    asdf_keyscan();
  }
}


void press_no_debounce(asdf_keycode_t code)
{
  coord_t *location = find_code(code);
  key_matrix[location->row] |= (1 << location->col);
}

void release_no_debounce(asdf_keycode_t code)
{
  coord_t *location = find_code(code);
  key_matrix[location->row] &= ~(1 << location->col);
}

void press(asdf_keycode_t code)
{
  press_no_debounce(code);
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS);
}

void release(asdf_keycode_t code)
{
  release_no_debounce(code);
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS);
}


asdf_cols_t asdf_arch_read_row(uint8_t row)
{
  return key_matrix[row];
}



// No repsonse to a keypress before it is debounced.
void pressing_a_gives_nothing_before_debounce(void)
{
  press_no_debounce(key_a);

  // no keypress after only ASDF_DEBOUNCE_TIME_MS -1  ticks (not yet debounced):
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS - 1);
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}

// pressing 'A' gives 'a'
void pressing_a_gives_a(void)
{
  press_no_debounce(key_a);

  // no keypress after only ASDF_DEBOUNCE_TIME_MS -1  ticks (not yet debounced):
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS - 1);
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_get_code());

  // allow the key to finish debounce
  keyscan_delay(1);
  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (int32_t) asdf_get_code());

  // no more codes in the buffer.
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}

// pressing SHIFT+A gives 'A'
void pressing_shift_a_gives_shifted_a(void)
{
  press(ACTION_SHIFT);
  press(key_a);
  TEST_ASSERT_EQUAL_INT32((int32_t) shifted(key_a), (int32_t) asdf_get_code());
}

// pressing CAPS+A gives 'A'
void pressing_caps_a_gives_caps_a(void)
{
  press(ACTION_CAPS);
  release(ACTION_CAPS);
  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) caps(key_a), (int32_t) asdf_get_code());
}

// pressing CTRL+A gives 0x01 (Ctrl-A)
void pressing_ctrl_a_gives_ctrl_a(void)
{
  press(ACTION_CTRL);
  press(key_a);
  TEST_ASSERT_EQUAL_INT32((int32_t) ctrl(key_a), (int32_t) asdf_get_code());
}

// pressing REPT+A repeats 'a'
void pressing_rept_a_repeats_a(void)
{
  press(ACTION_REPEAT);
  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());
  }

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// pressing REPT+SHIFT+A repeats 'A'
void pressing_shift_rept_a_repeats_shifted_a(void)
{
  press(ACTION_REPEAT);
  press(ACTION_SHIFT);
  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) shifted(key_a), (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) shifted(key_a), (uint32_t) asdf_get_code());
  }

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// pressing REPT+CAPS+A repeats 'A'
void pressing_caps_rept_a_repeats_caps_a(void)
{
  press(ACTION_REPEAT);
  press(ACTION_CAPS);

  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) caps(key_a), (uint32_t) asdf_get_code());


  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) caps(key_a), (uint32_t) asdf_get_code());
  }

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}

// pressing REPT+CTRL+A repeats CTRL-A
void pressing_ctrl_rept_a_repeats_ctrl_a(void)
{
  press(ACTION_REPEAT);
  press(ACTION_CTRL);

  press(key_a);
  TEST_ASSERT_EQUAL_INT32((int32_t) ctrl(key_a), (uint32_t) asdf_get_code());


  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  for (int i = 0; i < NUM_REPEATS + 1; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) ctrl(key_a), (uint32_t) asdf_get_code());
  }

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}

// pressing and holding 'A' autorepeats 'A'
void holding_a_autorepeats_a(void)
{
  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(ASDF_AUTOREPEAT_TIME_MS);
  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// pressing and holding 'A' autorepeats 'A'
void holding_a_autorepeats_slow_then_fast(void)
{
  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(ASDF_AUTOREPEAT_TIME_MS);
  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());
  }

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// pressing and holding 'A' and 'B' within less than debounce interval
// eventually returns 'A' then 'B'
void pressing_a_then_b_before_debounce_gives_a_then_b(void)
{
  press_no_debounce(key_a);

  // press B very quickly after a
  keyscan_delay(1);

  press(key_b);

  // first get back A
  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // next get back B
  TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());

  // and then verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// pressing and holding a series of keys (up to buffer size) in rapid
// succession, allowing each key to debounce, before sending the next, sends all
// the keys in order. (n-key rollover)
void test_key_sequence_nkro(void)
{
  for (int i = 0; i < (int32_t) strlen(test_string); i++) {
    press((asdf_keycode_t) test_string[i]);
  }

  for (int i = 0; i < (int32_t) strlen(test_string); i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) test_string[i], (int32_t) asdf_get_code());
  }

  // and then verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// pressing and holding a series of keys (up to buffer size) in rapid succession
// without waiting for prior keys to debounce, eventually debounces and sends
// all the keys in order. (n-key rollover)
void test_key_sequence_nkro_simultaneous_debounce(void)
{
  for (int i = 0; i < (int32_t) strlen(test_string); i++) {
    press_no_debounce((asdf_keycode_t) test_string[i]);
    keyscan_delay(1);
  }

  // several keys are already debounced, but now make sure they all are:
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS);

  for (int i = 0; i < (int32_t) strlen(test_string); i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) test_string[i], (int32_t) asdf_get_code());
  }

  // and then verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// holding 'A' then pressing 'B' before autorepeat interval and holding 'B' gives 'A', then repeats
// 'B'
void holding_a_briefly_then_holding_b_gives_a_and_repeats_b(void)
{
  press(key_a);
  keyscan_delay(ASDF_AUTOREPEAT_TIME_MS / 2);
  press(key_b);

  // hold "a" and "b" for autorepeat delay:
  keyscan_delay(ASDF_AUTOREPEAT_TIME_MS);

  // hold "a" and "b" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  // should get "a" back, then "b"
  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());
  TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());

  // now get back NUM_REEPEATS repetitions of "b"
  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());
  }

  // and then verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


// holding 'B' while repeating 'A' starts autorepeat delay, then starts repeating 'B'
void holding_a_then_holding_b_autorepeats_a_then_autorepeats_b(void)
{
  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // hold "a" for AUTOREPEAT delay
  keyscan_delay(ASDF_AUTOREPEAT_TIME_MS);
  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  // empty the buffer to make room for 'B'
  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());
  }

  // now press "b" while "a" is autorepeating:

  press(key_b);

  TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());

  // hold "a" for autorepeat delay
  keyscan_delay(ASDF_AUTOREPEAT_TIME_MS);
  TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  // empty the buffer to make room for 'B'
  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());
  }

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}

// Pressing and holding 'A' then holding 'B' with repeat key held repeats 'A' then 'B'
void repeating_with_a_then_adding_b_repeats_a_then_repeats_b(void)
{
  press(ACTION_REPEAT);
  press(key_a);

  TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  // empty the buffer to make room for 'B'
  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) key_a, (uint32_t) asdf_get_code());
  }

  // now press "b" while "a" is autorepeating:

  press(key_b);

  TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());

  // hold "a" for NUM_REPEATS repeat cycles:
  keyscan_delay(NUM_REPEATS * ASDF_REPEAT_TIME_MS);

  // empty the buffer to make room for 'B'
  for (int i = 0; i < NUM_REPEATS; i++) {
    TEST_ASSERT_EQUAL_INT32((int32_t) key_b, (uint32_t) asdf_get_code());
  }

  // and verify there are no more codes in buffer:
  TEST_ASSERT_EQUAL_INT32((int32_t) ASDF_INVALID_CODE, (int32_t) asdf_get_code());
}


int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(pressing_a_gives_nothing_before_debounce);
  RUN_TEST(pressing_a_gives_a);
  RUN_TEST(pressing_shift_a_gives_shifted_a);
  RUN_TEST(pressing_caps_a_gives_caps_a);
  RUN_TEST(pressing_ctrl_a_gives_ctrl_a);
  RUN_TEST(pressing_rept_a_repeats_a);
  RUN_TEST(pressing_shift_rept_a_repeats_shifted_a);
  RUN_TEST(pressing_caps_rept_a_repeats_caps_a);
  RUN_TEST(holding_a_autorepeats_a);
  RUN_TEST(holding_a_autorepeats_slow_then_fast);
  RUN_TEST(pressing_a_then_b_before_debounce_gives_a_then_b);
  RUN_TEST(test_key_sequence_nkro);
  RUN_TEST(test_key_sequence_nkro_simultaneous_debounce);
  RUN_TEST(holding_a_briefly_then_holding_b_gives_a_and_repeats_b);
  RUN_TEST(holding_a_then_holding_b_autorepeats_a_then_autorepeats_b);
  RUN_TEST(repeating_with_a_then_adding_b_repeats_a_then_repeats_b);



  return UNITY_END();
}
