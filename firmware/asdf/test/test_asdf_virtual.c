#include <stdint.h>
#include <stdarg.h>
#include "asdf_arch.h"
#include "unity.h"
#include "asdf.h"
#include "asdf_ascii.h"
#include "asdf_modifiers.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"
#include "asdf_config.h"



uint32_t max(uint8_t first, uint8_t second)
{
  uint32_t max = first;
  if (second > max) {
    max = second;
  }
  return max;
}

void setUp(void)
{
  asdf_arch_init();
  asdf_keymaps_init();
}

void tearDown(void) {}


// check to see that the longest keymap initializer sequence initia is detected.
void test_inizializer_length_is_max_length(void)
{
  TEST_ASSERT_EQUAL_INT32(max(ASDF_TEST_KEYMAP_INITIALIZER_LENGTH,
                              ASDF_TEST2_KEYMAP_INITIALIZER_LENGTH), ASDF_KEYMAP_INITIALIZER_LENGTH);
}

void test_single_virtual_output_is_initialized(void)
{
  // initially on keymap 0.  Test to see that OUT1 has been initialized to 0.
  TEST_ASSERT_EQUAL_INT32(asdf_arch_check_output(PHYSICAL_OUT1), 0);
  // and verify that this is not just the default value
  TEST_ASSERT_NOT_EQUAL(ASDF_VIRTUAL_OUT_DEFAULT_VALUE, asdf_arch_check_output(PHYSICAL_OUT1));
}

void test_uninitialized_virtual_out_is_default(void)
{
  TEST_ASSERT_EQUAL_INT32(ASDF_VIRTUAL_OUT_DEFAULT_VALUE, asdf_arch_check_output(PHYSICAL_LED2));
}

void test_set_virtual_output(void)
{
  asdf_virtual_action(VOUT1, V_SET_LO);
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));

  asdf_virtual_action(VOUT1, V_SET_HI);
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT1));
}

void test_toggle_virtual_output(void)
{
  // start by setting vout1 to 0
  asdf_virtual_action(VOUT1, V_SET_LO);
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));

  // toggle high
  asdf_virtual_action(VOUT1, V_TOGGLE);
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT1));

  // toggle back low.
  asdf_virtual_action(VOUT1, V_TOGGLE);
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));

}

void test_pulse_high_virtual_output(void)
{
  asdf_virtual_action(VOUT1, V_SET_LO);
  TEST_ASSERT_EQUAL_INT32(PD_ST_STABLE_LOW, asdf_arch_check_pulse(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));

  asdf_virtual_action(VOUT1, V_PULSE_SHORT);

  // output should be low
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));
  // high pulse should be detected.
  TEST_ASSERT_EQUAL_INT32(PD_ST_PULSE_HIGH_DETECTED, asdf_arch_check_pulse(PHYSICAL_OUT1));
}

void test_pulse_low_virtual_output(void)
{
  asdf_virtual_action(VOUT1, V_SET_HI);
  asdf_virtual_action(VOUT1, V_SET_HI);
  TEST_ASSERT_EQUAL_INT32(PD_ST_STABLE_HIGH, asdf_arch_check_pulse(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT1));

  asdf_virtual_action(VOUT1, V_PULSE_SHORT);

  // output should be high
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT1));
  // low pulse should be detected.
  TEST_ASSERT_EQUAL_INT32(PD_ST_PULSE_LOW_DETECTED, asdf_arch_check_pulse(PHYSICAL_OUT1));
}

// This test ties three real outputs to a virtual output and toggles the virtual
// output.
void test_toggle_triple_output(void)
{
  asdf_keymaps_select_keymap(TRIPLE_TESTS_KEYMAP);

  // check that initial values have been set:
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT3));

  asdf_virtual_activate(VOUT1); // funtion is set to toggle
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT3));

  asdf_virtual_action(VOUT1, V_TOGGLE);
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT3));
}

// This test ties three real outputs to a virtual output and sets the virtual
// output high and low
void test_set_triple_output(void)
{
  asdf_keymaps_select_keymap(TRIPLE_TESTS_KEYMAP);

  // check that initial values have been set:
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT3));

  asdf_virtual_action(VOUT1, V_SET_HI);
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT3));

  asdf_virtual_action(VOUT1, V_SET_LO);
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT3));
}

// This test ties three real outputs to a virtual output and pulses the virtual
// output high and low
void test_pulse_triple_output(void)
{
  asdf_keymaps_select_keymap(TRIPLE_TESTS_KEYMAP);
  // check that initial values have been set:
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT3));

  asdf_virtual_action(VOUT1, V_SET_HI);
  asdf_virtual_action(VOUT1, V_SET_HI);
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_OUT3));

  TEST_ASSERT_EQUAL_INT32(PD_ST_STABLE_HIGH, asdf_arch_check_pulse(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(PD_ST_STABLE_HIGH, asdf_arch_check_pulse(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(PD_ST_STABLE_HIGH, asdf_arch_check_pulse(PHYSICAL_OUT3));

  asdf_virtual_action(VOUT1, V_SET_LO);
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_OUT3));

  TEST_ASSERT_EQUAL_INT32(PD_ST_TRANSITION_LOW, asdf_arch_check_pulse(PHYSICAL_OUT1));
  TEST_ASSERT_EQUAL_INT32(PD_ST_TRANSITION_LOW, asdf_arch_check_pulse(PHYSICAL_OUT2));
  TEST_ASSERT_EQUAL_INT32(PD_ST_TRANSITION_LOW, asdf_arch_check_pulse(PHYSICAL_OUT3));
}

uint8_t *output_array(void)
{
  static uint8_t outputs[ASDF_PHYSICAL_NUM_RESOURCES] = {};
  for (uint8_t i = 0; i < ASDF_PHYSICAL_NUM_RESOURCES; i++) {
    outputs[i] = asdf_arch_check_output(i);
    printf("output %d: %d\n", i, outputs[i]);
  }
  return outputs;
}

uint8_t *all_set_array(void)
{
  static uint8_t outputs[ASDF_PHYSICAL_NUM_RESOURCES] = {};
  for (uint8_t i = 0; i < ASDF_PHYSICAL_NUM_RESOURCES; i++) {
    outputs[i] = 1;
  }
  return outputs;
}

uint8_t *all_zero_array(void)
{
  static uint8_t outputs[ASDF_PHYSICAL_NUM_RESOURCES] = {};
  for (uint8_t i = 0; i < ASDF_PHYSICAL_NUM_RESOURCES; i++) {
    outputs[i] = 0;
  }
  return outputs;
}

uint8_t *single_zero_array(asdf_physical_dev_t set_element)
{
  static uint8_t outputs[ASDF_PHYSICAL_NUM_RESOURCES] = {};
  for (uint8_t i = 0; i < ASDF_PHYSICAL_NUM_RESOURCES; i++) {
    outputs[i] = 1;
  }
  outputs[set_element] = 0;
  return outputs;
}


void test_virtual_capslock_indicator(void)
{

  asdf_keymaps_select_keymap(VCAPS_TEST_KEYMAP);

  // CAPS LED output should be initialized to zero:
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_LED1));

  // emulate capslock press and release.  Should set LED1
  asdf_modifier_capslock_activate();

  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_LED1));


  // emulate capslock press and release.  clear LED1
  asdf_modifier_capslock_activate();

  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_LED1));
}

void test_virtual_shiftlock_indicator(void)
{

  asdf_keymaps_select_keymap(VSHIFT_TEST_KEYMAP);

  // CAPS LED output should be initialized to zero:
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_LED2));

  // emulate shiftlock press and release.  Should set LED2
  asdf_modifier_shiftlock_on_activate();

  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_LED2));


  // emulate shift press and release.  clear LED2
  asdf_modifier_shift_activate();
  asdf_modifier_shift_deactivate();

  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_LED2));
}


void test_cant_assign_real_output_twice(void)
{
  asdf_keymaps_select_keymap(DOUBLE_ASSIGN_TEST_KEYMAP);

  // initial value should be set to 0:
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_LED1));

  // set LED1 high from valid VOUT4
  asdf_virtual_action(VOUT4, V_SET_HI);
  TEST_ASSERT_EQUAL_INT32(1, asdf_arch_check_output(PHYSICAL_LED1));

  // set LED1 low from valid VOUT4
  asdf_virtual_action(VOUT4, V_SET_LO);
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_LED1));

  // set LED1 high from invalid VOUT5
  asdf_virtual_action(VOUT5, V_SET_HI);
  // Should not have changed.
  TEST_ASSERT_EQUAL_INT32(0, asdf_arch_check_output(PHYSICAL_LED1));
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_inizializer_length_is_max_length);
  RUN_TEST(test_single_virtual_output_is_initialized);
  RUN_TEST(test_uninitialized_virtual_out_is_default);
  RUN_TEST(test_set_virtual_output);
  RUN_TEST(test_toggle_virtual_output);
  RUN_TEST(test_pulse_high_virtual_output);
  RUN_TEST(test_pulse_low_virtual_output);
  RUN_TEST(test_toggle_triple_output);
  RUN_TEST(test_set_triple_output);
  RUN_TEST(test_pulse_triple_output);
  RUN_TEST(test_virtual_capslock_indicator);
  RUN_TEST(test_virtual_shiftlock_indicator);
  RUN_TEST(test_cant_assign_real_output_twice);
  return UNITY_END();
}
