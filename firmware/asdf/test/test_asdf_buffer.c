#include <stdio.h>
#include <stdint.h>

#include "unity.h"
#include "asdf.h"
#include "asdf_buffer.h"


#define TEST_VALUE 'a'
#define MAX_BUFFER ASDF_BUFFER_POOL_SIZE
#define HALF_BUFFER (ASDF_BUFFER_POOL_SIZE / 2)

static const char test_string[] = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int test_string_size = sizeof(test_string) - 1;

static const char * const more_strings[] = {
                                      "abcdefghijkl",
                                      "12345",
                                      "ABCDEFG",
                                      "The quick brown",
                                      "We the people",
                                      "+"
};

static asdf_buffer_handle_t handle;

void setUp(void)
{
  asdf_buffer_init();
  handle = asdf_buffer_new(MAX_BUFFER);
}
void tearDown(void) {}



// function to generate pseudo-random sequence to fill buffer.
asdf_keycode_t random_code(asdf_keycode_t seed)
{
    uint8_t msb = seed & 0x80;
    seed <<= 1;
    if (msb) {
        seed ^= 0x88;
    }
    return seed;
}

// allocating first buffer returns handle 0
void test_allocating_first_buffer_returns_handle_0(void)
{
  TEST_ASSERT_EQUAL_INT32(0, (int32_t) handle);
}

// allocating second buffer returns handle 1
void test_allocating_second_buffer_returns_handle_1(void)
{
  asdf_buffer_handle_t handle_1;
  asdf_buffer_handle_t handle_2;

  asdf_buffer_init();
  handle_1 = asdf_buffer_new(HALF_BUFFER);
  TEST_ASSERT_EQUAL_INT32(0, (int32_t) handle_1);

  handle_2 = asdf_buffer_new(HALF_BUFFER);
  TEST_ASSERT_EQUAL_INT32(1, (int32_t) handle_2);
}

// allocating more buffers than available returns invalid buffer handle
void test_allocating_too_many_buffers_returns_invalid(void)
{
  asdf_buffer_init();

  for (int i = 0; i <= ASDF_BUFFER_NUM_HANDLES; i++) {
    handle = asdf_buffer_new(1);
  }

  TEST_ASSERT_EQUAL_INT32(ASDF_BUFFER_INVALID, (int32_t) handle);
}

// all of the alloted handles can be allocated
void test_all_handles_are_allocated(void)
{
  asdf_buffer_init();

  for (int i = 0; i < ASDF_BUFFER_NUM_HANDLES; i++) {
    handle = asdf_buffer_new(1);
    TEST_ASSERT_EQUAL_INT32(i, (int32_t) handle);
  }

  // and one more should be an invalid handle:
  handle = asdf_buffer_new(1);
  TEST_ASSERT_EQUAL_INT32(ASDF_BUFFER_INVALID, (int32_t) handle);
}

// allocating more space than available returns invalid buffer handle
void test_allocating_too_much_space_returns_invalid(void)
{
  asdf_buffer_init();
  handle = asdf_buffer_new(MAX_BUFFER + 1);
  TEST_ASSERT_EQUAL_INT32(ASDF_BUFFER_INVALID, (int32_t) handle);
}
// get from an invalid buffer returns invalid code
void test_get_from_invalid_handle_returns_invalid_code(void)
{
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_buffer_get(ASDF_BUFFER_INVALID));
}

void test_get_from_unallocated_handle_returns_invalid_code(void)
{
  asdf_keycode_t code = asdf_buffer_get(ASDF_BUFFER_NUM_HANDLES-1);

  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) code);
}



// retrieving from empty queue gives invalid code
void get_from_empty_queue_returns_error(void)
{
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_buffer_get(handle));
}

// adding and retrieving give the same code back.
void sending_code_and_retrieve_returns_same_code(void)
{
  asdf_buffer_put(handle, TEST_VALUE);
  TEST_ASSERT_EQUAL_INT32(TEST_VALUE, (int32_t) asdf_buffer_get(handle));
}


// adding then fetching a string of codes one-by-one gives the same string back in order
void test_adding_and_retrieving_string_one_by_one(void)
{

  for (int i = 0; i < (int) sizeof(test_string); i++) {
    asdf_buffer_put(handle, (asdf_keycode_t) test_string[i]);
    TEST_ASSERT_EQUAL_INT32((int32_t) test_string[i], (int32_t) asdf_buffer_get(handle));
  }
}


// should return the same string.
void test_fill_buffer_then_retrieve_string(void)
{
  for (int sent = 0; sent < MAX_BUFFER; sent++) {
    asdf_buffer_put(handle, (asdf_keycode_t) test_string[sent % test_string_size]);
  }
  for (int received = 0; received < MAX_BUFFER; received++) {
    int32_t code = (int32_t) asdf_buffer_get(handle);
    TEST_ASSERT_EQUAL_INT32((int32_t) test_string[received % test_string_size],code);
  }
  // assert that next code request returns invalid code:
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_buffer_get(handle));
}


// adding a string longer than the buffer length gives the first BUFFER_LENGTH
// characters back, quietly dropping the overflow.
void test_overfilling_buffer_and_retrieve_drops_overflow(void)
{
  const asdf_keycode_t seed = 0x3b;
  asdf_keycode_t next_random_code;

  // send the entire test string to overflow the buffer.
  for (int i = 0, next_rand_code = seed; i < MAX_BUFFER * 2; i++) {
    next_rand_code = random_code(next_rand_code);
    asdf_buffer_put(handle, next_rand_code);
  }
  // read until invalid character is received, testing that each character is
  // correct.
  for (int i = 0, next_rand_code = seed; i < MAX_BUFFER; i++) {
    asdf_keycode_t code = asdf_buffer_get(handle);
    next_rand_code = random_code(next_rand_code);
    TEST_ASSERT_EQUAL_INT32((int32_t) next_rand_code, (int32_t) code);
  }

  // the next code request returns invalid code:
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_buffer_get(handle));
}

// with an alternating pattern of adding and retrieving codes, the sent code string matches the retrieved string.
void test_send_get_multiple_strings(void)
{

  for (int i = 0; '+' != more_strings[i][0]; i++) {
    for (const char * chrptr = (const char *) &more_strings[i][0]; *chrptr; chrptr++) {
      asdf_buffer_put(handle, (asdf_keycode_t) *chrptr);
    }
  // read until invalid character is received, testing that each character is
  // correct.
    for (const char * chrptr = (const char *) &more_strings[i][0]; *chrptr; chrptr++) {
      asdf_keycode_t code = asdf_buffer_get(handle);
      TEST_ASSERT_EQUAL_INT32((int32_t) *chrptr, (int32_t) code);
  }
  // the next code request returns invalid code:
  TEST_ASSERT_EQUAL_INT32(ASDF_INVALID_CODE, (int32_t) asdf_buffer_get(handle));

  }
}



int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_allocating_first_buffer_returns_handle_0);
  RUN_TEST(test_allocating_second_buffer_returns_handle_1);
  RUN_TEST(test_allocating_too_many_buffers_returns_invalid);
  RUN_TEST(test_all_handles_are_allocated);
  RUN_TEST(test_allocating_too_much_space_returns_invalid);
  RUN_TEST(test_get_from_invalid_handle_returns_invalid_code);
  RUN_TEST(test_get_from_unallocated_handle_returns_invalid_code);
  RUN_TEST(get_from_empty_queue_returns_error);
  RUN_TEST(sending_code_and_retrieve_returns_same_code);
  RUN_TEST(test_adding_and_retrieving_string_one_by_one);
  RUN_TEST(test_fill_buffer_then_retrieve_string);
  RUN_TEST(test_overfilling_buffer_and_retrieve_drops_overflow);
  RUN_TEST(test_send_get_multiple_strings);

  return UNITY_END();
}
