#include<stdint.h>
#include "asdf.h"
#include "asdf_keymaps.h"
#include "asdf_keymap_defs.h"
#include "test_asdf_lib.h"
#include "asdf_arch.h"

static uint32_t key_matrix[ASDF_NUM_ROWS] = {};

ASDF_KEYMAP_DECLARATIONS;


coord_t *find_code(asdf_keycode_t code)
{
  uint32_t done = 0;
  static coord_t location = { .row = -1, .col = -1 };

  for (uint32_t row = 0; !done && (row < ASDF_NUM_ROWS); row++) {
    for (uint32_t col = 0; !done && (col < ASDF_NUM_COLS); col++) {
      if (test_PLAIN_matrix[row][col] == code) {
        done = 1;
        location.row = row;
        location.col = col;
      }
    }
  }
  return &location;
}


void keyscan_delay(int32_t ticks)
{
  for (; ticks; ticks--) {
    asdf_keyscan();
  }
}
 
void press_no_debounce(asdf_keycode_t code)
{
  coord_t *location = find_code(code);
  key_matrix[location->row] |= (1 << location->col);
}

void release_no_debounce(asdf_keycode_t code)
{
  coord_t *location = find_code(code);
  key_matrix[location->row] &= ~(1 << location->col);
}

void press(asdf_keycode_t code)
{
  press_no_debounce(code);
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS);
}

void release(asdf_keycode_t code)
{
  release_no_debounce(code);
  keyscan_delay(ASDF_DEBOUNCE_TIME_MS);
}


asdf_cols_t asdf_arch_read_row(uint8_t row)
{
  return key_matrix[row];
}


