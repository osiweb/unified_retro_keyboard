#ifndef ASDF_SIM_RUN_H
#define ASDF_SIM_RUN_H

#include <simavr/sim_avr.h>

typedef int (*sim_predicate_t)(void *ctx);

/* Run the sim until predicate(ctx) returns 1, the cpu halts/crashes,
 * or max_cycles elapse. Returns:
 *   1 if predicate succeeded
 *   0 if max_cycles elapsed without predicate succeeding
 *  -1 if cpu halted or crashed */
int sim_run_until(avr_t *cpu, sim_predicate_t pred, void *ctx,
                  uint64_t max_cycles);

/* Run the sim for exactly n_cycles more cycles. Halts/crashes return -1. */
int sim_run_for(avr_t *cpu, uint64_t n_cycles);

#endif
