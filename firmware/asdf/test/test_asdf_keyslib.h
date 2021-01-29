#if !defined(TEST_ASDF_LIB_H)

#include "asdf_keymaps.h"

// struct to define keymap row,col pairs
typedef struct {
  int32_t row;
  int32_t col;
} coord_t;


void keyscan_delay(int32_t ticks);
void press_no_debounce(asdf_keycode_t code);
void release_no_debounce(asdf_keycode_t code);
void press(asdf_keycode_t code);
void release(asdf_keycode_t code);
asdf_cols_t asdf_arch_read_row(uint8_t row);
coord_t *find_code(asdf_keycode_t code);



#define TEST_ASDF_LIB_H
#endif // if !defined(TEST_ASDF_LIB_H)
