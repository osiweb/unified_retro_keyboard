#ifndef ASDF_SIM_IO_H
#define ASDF_SIM_IO_H

#include <stdint.h>
#include <simavr/sim_avr.h>
#include "asdf_simavr_io_select.h"

/* Wire up the harness's strobe-edge capture to the given CPU/map.
 * After this, every strobe transition appends a record via cap_push().
 * Both edges are captured (not just the active edge) because keymaps
 * can flip strobe polarity at runtime via asdf_arch_set_neg_strobe. */
void io_wire_output(avr_t *cpu, const asdf_io_map_t *io);

/* Wire up matrix input injection. After this, the firmware's row strobes
 * will trigger the harness to drive the column input(s) according to the
 * currently-set matrix state. */
void io_wire_input(avr_t *cpu, const asdf_io_map_t *io);

/* Set/clear a key in the simulated matrix.
 * row 0..ASDF_NUM_ROWS-1 = normal keys; row 8 = DIP switch slot. */
void matrix_press(int row, int col);
void matrix_release(int row, int col);
void matrix_clear(void);

/* Convenience: set all 8 DIP switch bits to the given value, replacing
 * any previous DIP state. */
void set_dip(uint8_t value);

#endif
