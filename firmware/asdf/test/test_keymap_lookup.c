#include <stdint.h>
#include "unity.h"
#include "asdf.h"
#include "asdf_keymaps.h"
#include "asdf_modifiers.h"
#include "asdf_arch.h"

// Tests in this file focus on validating that asdf_keymaps_get_code()
// returns the correct values for the active modifier map, regardless of the
// dimensions of other modifier maps or previously selected keyboards.

// Provide a trivial row scanner so the tests link cleanly.
asdf_cols_t asdf_arch_read_row(uint8_t row)
{
    (void) row;
    return 0;
}

// Keymap 1: Small dimensions (2x2)
static const asdf_keycode_t small_plain_matrix[2][2] = {
    { 0x01, 'a' },
    { 0x02, 'b' }
};

static const asdf_keycode_t small_shift_matrix[2][2] = {
    { 0x01, 'A' },
    { 0x02, 'B' }
};

// Keymap 2: Large dimensions (4x4)
static const asdf_keycode_t large_plain_matrix[4][4] = {
    { 0x01, 'x', 'y', 'z' },
    { 0x02, '1', '2', '3' },
    { 0x03, '4', '5', '6' },
    { 0x04, '7', '8', '9' }
};

static const asdf_keycode_t large_shift_matrix[4][4] = {
    { 0x01, 'X', 'Y', 'Z' },
    { 0x02, '!', '@', '#' },
    { 0x03, '$', '%', '^' },
    { 0x04, '&', '*', '(' }
};

static void load_keymap(const asdf_keycode_t *plain_matrix,
                        uint8_t plain_rows,
                        uint8_t plain_cols,
                        const asdf_keycode_t *shift_matrix,
                        uint8_t shift_rows,
                        uint8_t shift_cols)
{
    asdf_keymaps_init();

    // Clear modifier entries so default keymaps do not leak into the tests.
    asdf_keymaps_add_map(NULL, MOD_PLAIN_MAP, 0, 0);
    asdf_keymaps_add_map(NULL, MOD_SHIFT_MAP, 0, 0);

    if (plain_matrix) {
        asdf_keymaps_add_map(plain_matrix, MOD_PLAIN_MAP, plain_rows, plain_cols);
    }

    if (shift_matrix) {
        asdf_keymaps_add_map(shift_matrix, MOD_SHIFT_MAP, shift_rows, shift_cols);
    }
}

void setUp(void)
{
    asdf_arch_init();
}

void tearDown(void) {}

static void expect_shift_lookup(uint8_t row, uint8_t col, asdf_keycode_t expected)
{
    TEST_ASSERT_EQUAL_INT(expected, asdf_keymaps_get_code(row, col, MOD_SHIFT_MAP));
}

static void expect_plain_lookup(uint8_t row, uint8_t col, asdf_keycode_t expected)
{
    TEST_ASSERT_EQUAL_INT(expected, asdf_keymaps_get_code(row, col, MOD_PLAIN_MAP));
}

void test_plain_and_shift_maps_can_have_independent_sizes(void)
{
    load_keymap((const asdf_keycode_t *)small_plain_matrix, 2, 2,
                (const asdf_keycode_t *)large_shift_matrix, 4, 4);

    expect_shift_lookup(0, 1, 'X');
    expect_shift_lookup(3, 3, '(');

    expect_plain_lookup(0, 1, 'a');
    expect_plain_lookup(1, 1, 'b');

    // Out-of-bounds on the plain map should return 0 without affecting shift
    expect_plain_lookup(3, 3, 0);
}

void test_switching_between_keyboard_layouts_updates_dimensions(void)
{
    load_keymap((const asdf_keycode_t *)large_plain_matrix, 4, 4,
                (const asdf_keycode_t *)large_shift_matrix, 4, 4);
    expect_plain_lookup(2, 2, '5');
    expect_shift_lookup(1, 2, '@');

    load_keymap((const asdf_keycode_t *)small_plain_matrix, 2, 2,
                (const asdf_keycode_t *)small_shift_matrix, 2, 2);
    expect_plain_lookup(1, 1, 'b');
    expect_shift_lookup(1, 1, 'B');
}

void test_unconfigured_modifier_returns_zero(void)
{
    load_keymap((const asdf_keycode_t *)small_plain_matrix, 2, 2,
                NULL, 0, 0);

    expect_plain_lookup(0, 0, 0x01);
    expect_plain_lookup(1, 1, 'b');

    // SHIFT map was never configured, so lookups should return 0
    expect_shift_lookup(0, 0, 0);
    expect_shift_lookup(1, 1, 0);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_plain_and_shift_maps_can_have_independent_sizes);
    RUN_TEST(test_switching_between_keyboard_layouts_updates_dimensions);
    RUN_TEST(test_unconfigured_modifier_returns_zero);

    return UNITY_END();
}
