#include<stdint.h>
#include "asdf.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"
#include "asdf_arch.h"
#include "asdf_hook.h"
#include "test_asdf_lib.h"

uint32_t hook_register;

uint32_t max(uint8_t first, uint8_t second)
{
  uint32_t max = first;
  if (second > max) {
    max = second;
  }
  return max;
}

void test_hook_clear(void)
{
  hook_register = 0;
}

uint32_t test_hook_readback(void)
{
  return hook_register;
}

void test_hook_1(void)
{
  hook_register |= TEST_HOOK_VAL1;
}

void test_hook_2(void)
{
  hook_register |= TEST_HOOK_VAL2;
}

void test_hook_3(void)
{
  hook_register |= TEST_HOOK_VAL3;
}

void test_hook_4(void)
{
  hook_register |= TEST_HOOK_VAL4;
}

void test_hook_5(void)
{
  hook_register |= TEST_HOOK_VAL5;
}

uint8_t test_hook_read_row(uint8_t val)
{
  return (uint8_t) val+2;
}

void test_hook_output(uint8_t val)
{
  hook_register = val;
}

void test_hook_each_scan(void)
{
  hook_register++;
}
