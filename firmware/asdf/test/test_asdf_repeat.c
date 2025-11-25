#include <stdio.h>
#include <stdint.h>
#include "unity.h"
#include "asdf_repeat.h"

#define REPEAT_TIMED_OUT 10000
#define NUM_REPETITIONS 10

uint32_t count_repeat_ticks(uint32_t timeout)
{
  uint32_t count = 0;
  uint32_t test;

  do {
    test = asdf_repeat();
    count++;
  } while (!test && count < timeout);

  return count;
}


void setUp(void)
{
  asdf_repeat_init();
}
void tearDown(void) {}


// On initialization, autorepeat should be enabled by default.
void test_asdf_repeat_init_resets_to_autorepeat_default(void)
{

  uint32_t delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);
}

// If autorepeat is turned off, then holding down a simulated key should not
// cause a repeat event.
void test_asdf_repeat_no_repeat_if_auto_turned_off(void)
{
  uint32_t delay;
  asdf_repeat_auto_off(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(REPEAT_TIMED_OUT, delay);
}

// If autorepeat is turned on, then holding down a simulated key should cause a
// repeat event after the autorepeat interval.
void test_asdf_repeat_autorepeat_if_auto_turned_on(void)
{
  uint32_t delay;
  asdf_repeat_auto_off(0);
  asdf_repeat_auto_on(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);
}

// After the autorepeat interval, subsequent repeat events should occur at the
// regular repeat interval.
void test_asf_repeat_autorepeat_fast_repeat_after_delay(void)
{
  uint32_t delay;

  // wait out the autorepeat delay
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);


  // now verify the next repeat interval is short:
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS, delay);
}


// If autorepeat is turned on, then holding down a key should cause a repeat
// event at the autorepeat interval. This should be true if autorepeat was
// previously off, or if it was already on, so test both cases here.
void test_asdf_repeat_auto_repeat_if_auto_turned_on(void)
{
  uint32_t delay;
  asdf_repeat_auto_on(0);
  asdf_repeat_auto_on(0);
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);

  asdf_repeat_auto_off(0);
  asdf_repeat_auto_on(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);
}

// When in autorepeat mode, calling asdf_repeat_reset_count() should reset the
// repeat timer to the autorepeat interval.
void test_asdf_repeat_reset_count_works_in_autorepeat_mode(void)
{
  uint32_t delay;
  // wait 1/2 of autorepeat time and release a key
  delay = count_repeat_ticks(ASDF_AUTOREPEAT_TIME_MS / 2);

  TEST_ASSERT_EQUAL_INT((ASDF_AUTOREPEAT_TIME_MS / 2), delay);

  asdf_repeat_reset_count();

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);
}

// When in repeat mode (repeat key held down), calling asdf_repeat_reset_count()
// should reset the repeat timer to the repeat interval.
void test_asdf_repeat_reset_count_works_in_repeat_mode(void)
{
  uint32_t delay;
  // wait 1/2 of autorepeat time and release a key

  asdf_repeat_activate(0);

  delay = count_repeat_ticks(ASDF_REPEAT_TIME_MS / 2);

  TEST_ASSERT_EQUAL_INT((ASDF_REPEAT_TIME_MS / 2), delay);

  asdf_repeat_reset_count();

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS, delay);
}


// When Autoreat is enabled, activating repeat mode (pressing the repeat key)
// should cause repeat events to occur at the fast repeat rate, skipping the
// autorepeat interval.
void test_asdf_repeat_activate_with_auto_on(void)
{
  uint32_t delay;
  asdf_repeat_auto_on(0);

  asdf_repeat_activate(0);
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS, delay);
}

// When Autoreat is off, activating repeat mode (pressing the repeat key)
// should cause repeat events to occur at the fast repeat rate
void test_asdf_repeat_activate_with_auto_off(void)
{
  uint32_t delay;
  asdf_repeat_auto_off(0);
  asdf_repeat_activate(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS, delay);
}

// If autorepeat is disabled, then activating and deactivating repeat mode
// (pressing and releasing the repeat key) should return to the autorepeat
// disabled mode.
void test_asdf_repeat_deactivate_returns_to_baseline_no_repeat(void)
{
  uint32_t delay;

  asdf_repeat_auto_off(0);

  // simulate a brief REPEAT key press (3 repeat cycles)


  asdf_repeat_activate(0);

  delay = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    delay += count_repeat_ticks(REPEAT_TIMED_OUT);
  }

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS * NUM_REPETITIONS, delay);

  asdf_repeat_deactivate(0);

  // now that repeat is deactivated, we should time out before hitting a repeat
  // event:
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(REPEAT_TIMED_OUT, delay);
}

// If autorepeat is enabled, then activating and deactivating repeat mode
// (pressing and releasing the repeat key) should return to the autorepeat
// enabled mode.
void test_asdf_repeat_deactivate_returns_to_baseline_autorepeat(void)
{
  uint32_t delay;

  // simulate a brief REPEAT key press (1/2 autorepeat time)
  asdf_repeat_activate(0);

  delay = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    delay += count_repeat_ticks(REPEAT_TIMED_OUT);
  }

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS * NUM_REPETITIONS, delay);

  asdf_repeat_deactivate(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);
}

// When Autoreat is enabled, and the autorepeat timer is activated by holding
// down a key, then activating repeat (pressing the repeat key) should skip the
// rest of the autorepeat interval, and cause repeat events to occur at the fast
// repeat rate.
void test_asdf_repeat_repeat_key_circumvents_initial_autorepeat_delay(void)
{
  uint32_t delay;

  // simulate a brief keypress (1/2 autorepeat time)
  delay = count_repeat_ticks(ASDF_AUTOREPEAT_TIME_MS / 2);

  TEST_ASSERT_EQUAL_INT((ASDF_AUTOREPEAT_TIME_MS / 2), delay);

  // simulate pressing the REPEAT key in the middle of an autorepeat interval
  asdf_repeat_activate(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS, delay);
}

// If autorepeat is on, and a key is being held down to start the autorepeat
// interval, then turning off autorepeat mode should prevent the key from
// repeating.
void test_asdf_repeat_turning_off_auto_cancels_autorepeat_delay_in_progress(void)
{
  uint32_t delay;
  asdf_repeat_auto_on(0);
  // simulate a brief keypress (1/2 autorepeat time)
  delay = count_repeat_ticks(ASDF_AUTOREPEAT_TIME_MS / 2);

  TEST_ASSERT_EQUAL_INT((ASDF_AUTOREPEAT_TIME_MS / 2), delay);

  asdf_repeat_auto_off(0);

  // simulate continued holding down key
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(REPEAT_TIMED_OUT, delay);
}

// If a key is autorepeating (held down until it repeats, without the repeat key
// being held down), then turning off autorepeat mode should stop the key from
// repeating.
void test_asdf_repeat_turning_off_auto_cancels_autorepeating_keypress(void)
{
  uint32_t delay;

  asdf_repeat_auto_on(0);
  // simulate an autorepeating key.  Wait out entire autorepeat delay.
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);

  // wait NUM_REPETITIONS repeat cycles:
  delay = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    delay += count_repeat_ticks(REPEAT_TIMED_OUT);
  }
  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS * NUM_REPETITIONS, delay);

  asdf_repeat_auto_off(0);

  for (delay = 0; !asdf_repeat() && (delay < REPEAT_TIMED_OUT); delay++) {
  }

  TEST_ASSERT_EQUAL_INT(REPEAT_TIMED_OUT, delay);
}


// If you press the REPEAT key while a key is already autorepeating (i.e., after
// the autorepeat delay interval), then the repeat timing shall not be affected.
void test_asdf_repeat_activate_while_autorepeating_wont_affect_timing(void)
{
  uint32_t delay;

  asdf_repeat_auto_on(0);
  // simulate an autorepeating key.  Wait out entire autorepeat delay.
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);

  // wait 1/2 fast repeat cycle:
  // simulate an autorepeating key.  Wait out entire autorepeat delay.
  delay = count_repeat_ticks(ASDF_REPEAT_TIME_MS / 2);

  TEST_ASSERT_EQUAL_INT((ASDF_REPEAT_TIME_MS / 2), delay);

  // turn on repeat mode (press REPEAT key)
  asdf_repeat_activate(0);

  // now verify the repeat interval was not affected. Finish the current repeat
  // interval
  delay += count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS, delay);
}

//  If in autorepeat mode and the repeat key is released while a key is
// repeating, the next repeat event should occur after a new autorepeat delay
// interval.
void test_asdf_repeat_deactivate_while_repeating_resets_autorepeat_counter(void)
{
  uint32_t delay;

  asdf_repeat_auto_on(0);
  asdf_repeat_activate(0);

  // wait NUM_REPETITIONS repeat cycles:
  delay = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    delay += count_repeat_ticks(REPEAT_TIMED_OUT);
  }
  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS * NUM_REPETITIONS, delay);

  // releast REPEAT key:
  asdf_repeat_deactivate(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  // should have waited entire autorepeat delay interval
  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);
}

//  If autorepeat is disabled and the repeat key is released while a key is
// repeating, then the key should stop repeating.
void test_asdf_repeat_deactivate_while_repeating_stops_repeating(void)
{
  uint32_t delay;

  asdf_repeat_auto_off(0);
  asdf_repeat_activate(0);

  // wait NUM_REPETITIONS repeat cycles:
  delay = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    delay += count_repeat_ticks(REPEAT_TIMED_OUT);
  }
  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS * NUM_REPETITIONS, delay);

  // releast REPEAT key:
  asdf_repeat_deactivate(0);

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  // should have waited entire autorepeat delay interval
  TEST_ASSERT_EQUAL_INT(REPEAT_TIMED_OUT, delay);
}

// pressing a new value key when REPEAT is active should start repeating right
// away.
void test_asdf_repeat_new_key_while_repeat_active_keeps_repeating(void)
{
  uint32_t delay;

  asdf_repeat_activate(0);

  // wait NUM_REPETITIONS repeat cycles:
  delay = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    delay += count_repeat_ticks(REPEAT_TIMED_OUT);
  }
  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS * NUM_REPETITIONS, delay);

  // simulate half a repeat interval
  delay = count_repeat_ticks(ASDF_REPEAT_TIME_MS / 2);

  // simulate a new key press:
  asdf_repeat_reset_count();

  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  // should have waited the key repeat interval
  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS, delay);
}

// pressing a new value key when autorepeating should start new autorepeat
// delay.
void test_asdf_repeat_new_key_while_autorepeating_starts_new_autorepeat(void)
{
  uint32_t delay;

  asdf_repeat_auto_on(0);

  // simulate an autorepeating key.  Wait out entire autorepeat delay.
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);

  // wait NUM_REPETITIONS repeat cycles:
  delay = 0;
  for (uint32_t i = 0; i < NUM_REPETITIONS; i++) {
    delay += count_repeat_ticks(REPEAT_TIMED_OUT);
  }
  TEST_ASSERT_EQUAL_INT(ASDF_REPEAT_TIME_MS * NUM_REPETITIONS, delay);

  // simulate new keypress:
  asdf_repeat_reset_count();

  // now measure interval until next repeat event.
  delay = count_repeat_ticks(REPEAT_TIMED_OUT);

  TEST_ASSERT_EQUAL_INT(ASDF_AUTOREPEAT_TIME_MS, delay);
}
int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_asdf_repeat_init_resets_to_autorepeat_default);
  RUN_TEST(test_asdf_repeat_no_repeat_if_auto_turned_off);
  RUN_TEST(test_asdf_repeat_auto_repeat_if_auto_turned_on);
  RUN_TEST(test_asf_repeat_autorepeat_fast_repeat_after_delay);
  RUN_TEST(test_asdf_repeat_reset_count_works_in_autorepeat_mode);
  RUN_TEST(test_asdf_repeat_reset_count_works_in_repeat_mode);
  RUN_TEST(test_asdf_repeat_activate_with_auto_on);
  RUN_TEST(test_asdf_repeat_activate_with_auto_off);
  RUN_TEST(test_asdf_repeat_deactivate_returns_to_baseline_autorepeat);
  RUN_TEST(test_asdf_repeat_deactivate_returns_to_baseline_no_repeat);
  RUN_TEST(test_asdf_repeat_repeat_key_circumvents_initial_autorepeat_delay);
  RUN_TEST(test_asdf_repeat_activate_while_autorepeating_wont_affect_timing);
  RUN_TEST(test_asdf_repeat_turning_off_auto_cancels_autorepeating_keypress);
  RUN_TEST(test_asdf_repeat_turning_off_auto_cancels_autorepeat_delay_in_progress);
  RUN_TEST(test_asdf_repeat_deactivate_while_repeating_resets_autorepeat_counter);
  RUN_TEST(test_asdf_repeat_deactivate_while_repeating_stops_repeating);
  RUN_TEST(test_asdf_repeat_new_key_while_repeat_active_keeps_repeating);
  RUN_TEST(test_asdf_repeat_new_key_while_autorepeating_starts_new_autorepeat);
  return UNITY_END();
}
