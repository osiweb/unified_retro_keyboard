#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "unity.h"
#include "asdf.h"
#include "asdf_arch.h"
#include "asdf_ascii.h"
#include "asdf_modifiers.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"
#include "asdf_buffer.h"
#include "asdf_repeat.h"
#include "asdf_hook.h"
#include "test_asdf_lib.h"

//ASDF_TEST_DECLARATIONS;

// emulates arch_read_row function, used mainly to see that the read_row hook is
// getting called.
asdf_cols_t asdf_arch_read_row(uint8_t row)
{
  return (asdf_keycode_t) (row + 1);
}


void setUp(void)
{
  test_hook_clear();
  asdf_keymaps_init();
  asdf_init();
}

void tearDown(void) {}


typedef asdf_cols_t (*scanner_func_t)(uint8_t);

void test_default_scan_hook_is_default_scanner(void)
{
  scanner_func_t testfunc = (scanner_func_t) asdf_hook_get(ASDF_HOOK_SCANNER);  
  asdf_cols_t testval = 0;

  // make sure the pointer points to the correct function
  TEST_ASSERT_EQUAL_PTR(testfunc, &asdf_arch_read_row);

  // Now try calling the function
  testval = (*testfunc)(100);
  TEST_ASSERT_EQUAL_INT((int) asdf_arch_read_row(100), (int) testval);
}

// test_alternate_scan_hook
void test_alternate_scan_hook(void)
{
  asdf_keymaps_select_keymap(ASDF_TEST_ALTERNATE_SCANNER_MAP);
  scanner_func_t testfunc = (scanner_func_t) asdf_hook_get(ASDF_HOOK_SCANNER);
  asdf_cols_t testval = 0;

  // make sure the pointer points to the correct function
  TEST_ASSERT_EQUAL_PTR(testfunc, &test_hook_read_row);

  // Now try calling the function
  testval = (*testfunc)(100);
  TEST_ASSERT_EQUAL_INT((int) test_hook_read_row(100), (int) testval);
}

#define NUM_SCAN_TEST_REPS 101

void test_each_scan_hook_is_executed_each_scan(void)
{

  test_hook_clear();
  asdf_keymaps_select_keymap(ASDF_TEST_EACH_SCAN_MAP);
  TEST_ASSERT_EQUAL_INT(0, test_hook_readback());
  for (int i = 0; i < NUM_SCAN_TEST_REPS; i++) {
    asdf_keyscan();
  }
  TEST_ASSERT_EQUAL_INT(NUM_SCAN_TEST_REPS, test_hook_readback());
}

// Check that setup hooks are executed immediately
void test_setup_hook_is_executed_immediately(void)
{
  test_hook_clear();
  asdf_keymaps_select_keymap(0);
  uint32_t expected = TEST_HOOK_VAL1 | TEST_HOOK_VAL2;
  TEST_ASSERT_EQUAL_INT(expected, test_hook_readback());
}

// Check that setup hooks are executed properly after selecting nonzero map
void test_setup_hook_is_executed_immediately_when_selecting_nonzero_map(void)
{
  test_hook_clear();
  asdf_keymaps_select_keymap(1);
  uint32_t expected = TEST_HOOK_VAL3 | TEST_HOOK_VAL4;
  TEST_ASSERT_EQUAL_INT(expected, test_hook_readback());
}




int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_default_scan_hook_is_default_scanner);
  RUN_TEST(test_alternate_scan_hook);
  RUN_TEST(test_setup_hook_is_executed_immediately);
  RUN_TEST(test_setup_hook_is_executed_immediately_when_selecting_nonzero_map);
  RUN_TEST(test_each_scan_hook_is_executed_each_scan);
  return UNITY_END();
}
