#ifndef ASDF_SIM_VCD_H
#define ASDF_SIM_VCD_H

#include <simavr/sim_avr.h>
#include "asdf_simavr_io_select.h"

/* Begin VCD recording of all watched pins. Records data-port byte,
 * strobe, LEDs, and the first row port. Returns 0 on success. */
int vcd_begin(avr_t *cpu, const asdf_io_map_t *io, const char *path);
void vcd_end(void);

#endif
