#ifndef ASDF_SIM_H
#define ASDF_SIM_H

#include <simavr/sim_avr.h>
#include "asdf_simavr_io_select.h"

avr_t *sim_load(const char *target, const char *elf_path,
                const asdf_io_map_t *io);
void   sim_free(avr_t *cpu);

#endif
