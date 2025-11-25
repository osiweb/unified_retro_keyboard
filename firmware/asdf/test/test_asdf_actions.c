// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// DIP/action regression tests
//
// Exercises the action codes bound to the DIP switch row to ensure that
// architecture hooks (strobe polarity) and repeat-mode toggles are invoked on
// key press and reverted on release.

#include <stdint.h>
#include "unity.h"
#include "asdf.h"
#include "asdf_arch_test.h"
#include "asdf_keymaps.h"
#include "test_asdf_keymap_defs.h"
#include "asdf_repeat.h"

#define DIP_ROW_INDEX (TEST_NUM_ROWS - 1)
#define STROBE_COL 6
#define AUTOREPEAT_COL 7

static uint32_t key_matrix[TEST_NUM_ROWS];

static void keyscan_delay(int32_t ticks)
{
  while (ticks--) {
    asdf_keyscan();
  }
}

asdf_cols_t asdf_arch_read_row(uint8_t row)
{
  return key_matrix[row];
}

static void drive_dip(uint8_t col, uint8_t pressed)
{
  if (pressed) {
    key_matrix[DIP_ROW_INDEX] |= (1u << col);
  } else {
    key_matrix[DIP_ROW_INDEX] &= ~(1u << col);
  }
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS);
}

static void press_dip(uint8_t col)
{
  drive_dip(col, 1);
}

static void release_dip(uint8_t col)
{
  drive_dip(col, 0);
}

void setUp(void)
{
  asdf_init();
  for (uint32_t i = 0; i < TEST_NUM_ROWS; i++) {
    key_matrix[i] = 0;
  }
}

void tearDown(void) {}

void test_dip_strobe_action_toggles_polarity(void)
{
  TEST_ASSERT_FALSE(asdf_arch_is_strobe_positive());

  press_dip(STROBE_COL);
  TEST_ASSERT_TRUE(asdf_arch_is_strobe_positive());

  release_dip(STROBE_COL);
  TEST_ASSERT_FALSE(asdf_arch_is_strobe_positive());
}

void test_dip_autorepeat_action_toggles_mode(void)
{
  asdf_repeat_auto_off(0);
  TEST_ASSERT_FALSE(asdf_repeat_is_autorepeat_enabled());

  press_dip(AUTOREPEAT_COL);
  TEST_ASSERT_TRUE(asdf_repeat_is_autorepeat_enabled());

  release_dip(AUTOREPEAT_COL);
  TEST_ASSERT_FALSE(asdf_repeat_is_autorepeat_enabled());
}

void test_keymap_switch_reapplies_dip_actions(void)
{
  asdf_repeat_auto_off(0);
  TEST_ASSERT_FALSE(asdf_repeat_is_autorepeat_enabled());
  TEST_ASSERT_FALSE(asdf_arch_is_strobe_positive());

  press_dip(STROBE_COL);
  press_dip(AUTOREPEAT_COL);

  TEST_ASSERT_TRUE(asdf_arch_is_strobe_positive());
  TEST_ASSERT_TRUE(asdf_repeat_is_autorepeat_enabled());

  // Switching keymaps should reapply any dip-action state
  asdf_keymaps_select(ASDF_TEST_CAPS_MAP_INDEX);

  TEST_ASSERT_TRUE(asdf_arch_is_strobe_positive());
  TEST_ASSERT_TRUE(asdf_repeat_is_autorepeat_enabled());

  release_dip(STROBE_COL);
  release_dip(AUTOREPEAT_COL);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_dip_strobe_action_toggles_polarity);
  RUN_TEST(test_dip_autorepeat_action_toggles_mode);
  RUN_TEST(test_keymap_switch_reapplies_dip_actions);
  return UNITY_END();
}
