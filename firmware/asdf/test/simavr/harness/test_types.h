#ifndef ASDF_SIM_TEST_TYPES_H
#define ASDF_SIM_TEST_TYPES_H

#include <stdint.h>

#define SIM_MOD_NONE  0
#define SIM_MOD_SHIFT 1
#define SIM_MOD_CTRL  2
#define SIM_MOD_CAPS  3

typedef struct {
    int row;
    int col;
} sim_coord_t;

typedef enum {
    SIM_STEP_KEY,          /* press+release a key, expect one output byte */
    SIM_STEP_MOD_DOWN,     /* press a modifier and hold */
    SIM_STEP_MOD_UP,       /* release the held modifier */
    SIM_STEP_MOD_TAP       /* press+release (used for the sticky caps toggle) */
} sim_step_type_t;

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

typedef struct {
    sim_step_type_t type;
    int row;               /* SIM_STEP_KEY: key coord */
    int col;
    int modifier;          /* SIM_STEP_MOD_*: one of SIM_MOD_SHIFT, SIM_MOD_CAPS, SIM_MOD_CTRL */
    uint8_t expected;      /* SIM_STEP_KEY: expected output byte (0 for mod steps) */
} sim_string_step_t;

typedef struct {
    uint8_t                  dip_value;
    uint32_t                 boot_scan_ticks;
    sim_coord_t              modifier_shift;
    sim_coord_t              modifier_caps_toggle;   /* shiftlock or capslock — keymap-specific */
    sim_coord_t              modifier_ctrl;
    const sim_string_step_t *steps;
    int                      num_steps;
} sim_string_test_t;

typedef struct {
    uint8_t             dip_value;
    uint32_t            boot_scan_ticks;   /* capture window */
    const char         *expected;          /* exact bytes the firmware should print */
    int                 expected_len;
} sim_identity_test_t;

#endif
