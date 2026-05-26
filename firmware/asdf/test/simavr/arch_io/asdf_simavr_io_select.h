#ifndef ASDF_SIMAVR_IO_SELECT_H
#define ASDF_SIMAVR_IO_SELECT_H

#include <stdint.h>

#define ASDF_IO_MAX_LEDS 4

typedef struct {
    char port;
    int  bit;
    int  active_low;
} asdf_io_led_t;

typedef struct {
    const char *family_name;
    uint32_t    cpu_frequency_hz;

    char row_port;
    uint8_t row_mask;
    int row_shift;
    char row_port_hi;             /* '\0' if unused (family A) */
    int row_active_low;

    char col_port;
    int  col_parallel;            /* 1 = parallel read, 0 = serial via shift reg */
    uint8_t col_mask;             /* only meaningful if col_parallel */
    int col_active_low;           /* only meaningful if col_parallel */
    int col_bit_serial;           /* only meaningful if !col_parallel */
    char col_load_clock_port;
    int  col_load_clock_bit;
    char col_mode_port;
    int  col_mode_bit;

    char data_port;
    uint8_t data_mask;

    char strobe_port;
    int  strobe_bit;
    int  strobe_active_high;

    int led_count;
    asdf_io_led_t leds[ASDF_IO_MAX_LEDS];

    int dip_row;
    int dip_col_count;

    int scan_tick_hz;
} asdf_io_map_t;

const asdf_io_map_t *asdf_io_pick(const char *target);

#endif
