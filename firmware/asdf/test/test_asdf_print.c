// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Tests for the formatted print shim. Verify that asdf_print() ultimately feeds
// the message buffer (via asdf_putc) and preserves newline translation.

#include "unity.h"
#include "asdf.h"
#include "asdf_print.h"
#include "asdf_arch_test.h"

asdf_cols_t asdf_arch_read_row(uint8_t row)
{
  (void) row;
  return 0;
}

void setUp(void)
{
  asdf_arch_delay_ms_reset_count();
  asdf_init();
}

void tearDown(void) {}

static void expect_string(const char *expected)
{
  for (const char *p = expected; *p; ++p) {
    TEST_ASSERT_EQUAL_INT((int) *p, (int) asdf_next_code());
  }
  TEST_ASSERT_EQUAL_INT(ASDF_INVALID_CODE, (int) asdf_next_code());
}

void test_asdf_print_formats_strings(void)
{
  asdf_print("Value:%02d-%s", 5, "ok");
  expect_string("Value:05-ok");
}

void test_asdf_print_translates_newlines(void)
{
  asdf_print("Line1\nLine2");
  const char *expected = "Line1\r\nLine2";
  for (const char *p = expected; *p; ++p) {
    TEST_ASSERT_EQUAL_INT((int) *p, (int) asdf_next_code());
  }
  TEST_ASSERT_EQUAL_INT(ASDF_INVALID_CODE, (int) asdf_next_code());
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_asdf_print_formats_strings);
  RUN_TEST(test_asdf_print_translates_newlines);
  return UNITY_END();
}
