#ifndef ASDF_SIM_IO_H
#define ASDF_SIM_IO_H

#include <simavr/sim_avr.h>
#include "asdf_simavr_io_select.h"

/* Wire up the harness's strobe-edge capture to the given CPU/map.
 * After this, every strobe transition appends a record via cap_push().
 * Both edges are captured (not just the active edge) because keymaps
 * can flip strobe polarity at runtime via asdf_arch_set_neg_strobe. */
void io_wire_output(avr_t *cpu, const asdf_io_map_t *io);

#endif
