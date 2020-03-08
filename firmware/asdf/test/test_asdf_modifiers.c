#include <stdint.h>

#include "unity.h"
#include "asdf_modifiers.h"


#define TESTMAP(a)                                                                                 \
  do {                                                                                             \
    uint32_t map = (uint32_t) asdf_modifier_index();                                               \
    TEST_ASSERT_EQUAL_INT((a), map);                                                               \
  } while (0);

void setUp(void)
{
  asdf_modifiers_init();
}
void tearDown(void) {}


// initial map is plain
void initial_map_is_plain(void)
{
  TESTMAP(MOD_PLAIN_MAP);
}


// SHIFT gives shift map
void shift_gives_shiftmap(void)
{
  asdf_modifier_shift_activate();
  TESTMAP(MOD_SHIFT_MAP);
}

// SHIFT press & release gives plain map
void shift_and_release_gives_plain(void)
{
  asdf_modifier_shift_activate();
  TESTMAP(MOD_SHIFT_MAP);

  asdf_modifier_shift_deactivate();
  TESTMAP(MOD_PLAIN_MAP);
}

// CAPSLOCK gives caps map
void capslock_gives_caps(void)
{
  asdf_modifier_capslock_activate();
  TESTMAP(MOD_CAPS_MAP);
}

// CAPLOCK press and release gives caps map
void capslock_and_release_gives_caps(void)
{
  asdf_modifier_capslock_activate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);
}

// CAPS-release-CAPS give plain
void caps_release_caps_gives_plain(void)
{
  asdf_modifier_capslock_activate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_capslock_activate();
  TESTMAP(MOD_PLAIN_MAP);
}

// CAPS-release-CAPS-release will first activate CAPS mode then deactivation,
// resulting in final plain map.
void caps_release_caps_release_gives_plain(void)
{
  asdf_modifier_capslock_activate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_capslock_activate();
  TESTMAP(MOD_PLAIN_MAP);

  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_PLAIN_MAP);
}

// If SHIFT and CAPS are activated, the SHIFT map results
void shift_and_caps_gives_shift(void)
{
  asdf_modifier_capslock_activate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_shift_activate();
  TESTMAP(MOD_SHIFT_MAP);
}

// IF CAPS map is active, pressing and releasing SHIFT reverts to CAPS
void caps_shift_unshift_gives_caps(void)
{
  asdf_modifier_capslock_activate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_shift_activate();
  TESTMAP(MOD_SHIFT_MAP);

  asdf_modifier_shift_deactivate();
  TESTMAP(MOD_CAPS_MAP);
}

// Capslock and SHiftlock gives SHIFT
void capslock_shiftlock_gives_shift(void)
{
  asdf_modifier_capslock_activate();
  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_SHIFT_MAP);
}

// Pressing CAPSLOCK and SHIFTLOCK, then CAPSLOCK again gives shift map.
void capslock_shiftlock_capslock_gives_shift(void)
{
  asdf_modifier_capslock_activate();
  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_SHIFT_MAP);

  asdf_modifier_capslock_activate();
  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_SHIFT_MAP);
}

// Pressing CAPSLOCK and SHIFTLOCK, then press and releast SHIFT (to deactivate
// the shiftlock) again gives shift map.
void capslock_shiftlock_shift_gives_caps(void)
{
  asdf_modifier_capslock_activate();
  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CAPS_MAP);

  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_SHIFT_MAP);

  asdf_modifier_shift_activate();
  asdf_modifier_shift_deactivate();
  TESTMAP(MOD_CAPS_MAP);
}

// SHIFTLOCK press gives shift map
void shiftlock_gives_shift(void)
{
  asdf_modifier_shiftlock_activate();
  TESTMAP(MOD_SHIFT_MAP);
}

// SHIFTLOCK press and release gives shift map
void shiftlock_and_release_gives_shift(void)
{
  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_SHIFT_MAP);
}


// SHIFTLOCK and SHIFT gives shift map
void shiftlock_shift_gives_shift(void)
{
  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_SHIFT_MAP);

  asdf_modifier_shift_activate();
  TESTMAP(MOD_SHIFT_MAP);
}

// SHIFTLOCK and SHIFT press and release gives plain map
void shiftlock_shift_release_gives_plain(void)
{
  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_SHIFT_MAP);

  asdf_modifier_shift_activate();
  asdf_modifier_shift_deactivate();
  TESTMAP(MOD_PLAIN_MAP);
}

// CTRL gives ctrl map
void ctrl_gives_ctrl_map(void)
{
  asdf_modifier_ctrl_activate();
  TESTMAP(MOD_CTRL_MAP);
}

// CTRL press and release gives plain map
void ctrl_release_gives_plain_map(void)
{
  asdf_modifier_ctrl_activate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_ctrl_activate();
  asdf_modifier_ctrl_deactivate();
  TESTMAP(MOD_PLAIN_MAP);
}


// SHIFT + CTRL is ctrl map
void ctrl_shift_gives_ctrl_map(void)
{
  asdf_modifier_ctrl_activate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_shift_activate();
  TESTMAP(MOD_CTRL_MAP);
}

// CAPSLOCK and CTRL is ctrl map
void ctrl_caps_gives_ctrl_map(void)
{
  asdf_modifier_ctrl_activate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_capslock_activate();
  TESTMAP(MOD_CTRL_MAP);
}


// SHIFTLOCK and CTRL is ctrl map
void ctrl_shiftlock_gives_ctrl_map(void)
{
  asdf_modifier_ctrl_activate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_shiftlock_activate();
  TESTMAP(MOD_CTRL_MAP);
}

void ctrl_double_caps_returns_to_ctrl_map(void)
{
  asdf_modifier_ctrl_activate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_capslock_activate();
  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_capslock_activate();
  asdf_modifier_capslock_deactivate();
  TESTMAP(MOD_CTRL_MAP);
}

void ctrl_double_shiftlock_returns_to_ctrl_map(void)
{
  asdf_modifier_ctrl_activate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_CTRL_MAP);

  asdf_modifier_shiftlock_activate();
  asdf_modifier_shiftlock_deactivate();
  TESTMAP(MOD_CTRL_MAP);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(initial_map_is_plain);
  RUN_TEST(shift_gives_shiftmap);
  RUN_TEST(shift_and_release_gives_plain);
  RUN_TEST(capslock_gives_caps);
  RUN_TEST(capslock_and_release_gives_caps);
  RUN_TEST(caps_release_caps_gives_plain);
  RUN_TEST(caps_release_caps_release_gives_plain);
  RUN_TEST(shift_and_caps_gives_shift);
  RUN_TEST(caps_shift_unshift_gives_caps);
  RUN_TEST(capslock_shiftlock_gives_shift);
  RUN_TEST(capslock_shiftlock_capslock_gives_shift);
  RUN_TEST(capslock_shiftlock_shift_gives_caps);
  RUN_TEST(shiftlock_gives_shift);
  RUN_TEST(shiftlock_and_release_gives_shift);
  RUN_TEST(shiftlock_shift_gives_shift);
  RUN_TEST(shiftlock_shift_release_gives_plain);
  RUN_TEST(ctrl_gives_ctrl_map);
  RUN_TEST(ctrl_release_gives_plain_map);
  RUN_TEST(ctrl_shift_gives_ctrl_map);
  RUN_TEST(ctrl_caps_gives_ctrl_map);
  RUN_TEST(ctrl_shiftlock_gives_ctrl_map);
  RUN_TEST(ctrl_double_caps_returns_to_ctrl_map);
  RUN_TEST(ctrl_double_shiftlock_returns_to_ctrl_map);
  // toggle shiftlock_mode switches the shiftlock behavior to toggle_mode
  // calling toggle_shiftlock_mode twice leaves shiftlock behavior in hold mode
  // calling toggle_shiftlock_mode three times leaves shiftlock behavior in toggle mode

  return UNITY_END();
}
