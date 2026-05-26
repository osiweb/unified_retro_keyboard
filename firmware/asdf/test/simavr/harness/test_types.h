#ifndef ASDF_SIM_TEST_TYPES_H
#define ASDF_SIM_TEST_TYPES_H

#include <stdint.h>

#define SIM_MOD_NONE  0
#define SIM_MOD_SHIFT 1
#define SIM_MOD_CTRL  2

typedef struct {
    int row;
    int col;
} sim_coord_t;

typedef struct {
    int      row;
    int      col;
    uint32_t hold_cycles;        /* how long to hold the key down before releasing */
    uint8_t  expected;           /* expected output byte */
    int      with_modifier;      /* SIM_MOD_NONE | SIM_MOD_SHIFT | SIM_MOD_CTRL */
} sim_event_t;

typedef struct {
    const char        *name;
    uint8_t            dip_value;
    uint32_t           boot_scan_ticks;   /* simulated ms to wait before driving input */
    sim_coord_t        modifier_shift;    /* matrix coord of SHIFT for this keymap */
    sim_coord_t        modifier_ctrl;     /* matrix coord of CTRL for this keymap */
    const sim_event_t *events;
    int                num_events;
} sim_keymap_test_t;

#endif
