// -*- mode: C; tab-width: 2 ; indent-tabs-mode: nil -*-
//
// Output-path regression tests
//
// These tests focus on the public buffering APIs that ferry bytes from the
// firmware into host-visible streams. They exercise:
//   1. Message buffer priority vs. keycodes (`asdf_next_code`).
//   2. CRLF translation performed by `asdf_putc`.
//   3. Print-delay throttling via `asdf_set_print_delay`.
//
#include <stdint.h>
#include "unity.h"
#include "asdf.h"
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

// Verify that system messages (via asdf_putc) are delivered before queued
// keypresses, matching the documented behavior of asdf_next_code.
void test_message_buffer_has_priority_over_keycodes(void)
{
  // Queue a keycode first, then a message byte.
  asdf_put_code('k');
  asdf_putc('m', NULL);

  TEST_ASSERT_EQUAL_INT('m', asdf_next_code());
  TEST_ASSERT_EQUAL_INT('k', asdf_next_code());
  TEST_ASSERT_EQUAL_INT(ASDF_INVALID_CODE, asdf_next_code());
}

// Ensure the firmware's newline handling converts LF to CRLF when buffering
// system messages.
void test_putc_translates_newline_to_crlf(void)
{
  asdf_putc('\n', NULL);

  TEST_ASSERT_EQUAL_INT('\r', asdf_next_code());
  TEST_ASSERT_EQUAL_INT('\n', asdf_next_code());
  TEST_ASSERT_EQUAL_INT(ASDF_INVALID_CODE, asdf_next_code());
}

// Confirm that only message bytes trigger the configured print delay.
void test_print_delay_applies_only_to_messages(void)
{
  const uint8_t delay = 77;

  asdf_set_print_delay(delay);
  asdf_putc('x', NULL);
  asdf_put_code('y');
  asdf_arch_delay_ms_reset_count();

  TEST_ASSERT_EQUAL_INT('x', asdf_next_code());
  TEST_ASSERT_EQUAL_UINT32(1, asdf_arch_delay_ms_call_count());
  TEST_ASSERT_EQUAL_UINT16(delay, asdf_arch_delay_ms_last_value());

  TEST_ASSERT_EQUAL_INT('y', asdf_next_code());
  TEST_ASSERT_EQUAL_UINT32(1, asdf_arch_delay_ms_call_count());
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_message_buffer_has_priority_over_keycodes);
  RUN_TEST(test_putc_translates_newline_to_crlf);
  RUN_TEST(test_print_delay_applies_only_to_messages);
  return UNITY_END();
}
