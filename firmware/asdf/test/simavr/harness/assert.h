#ifndef ASDF_SIM_ASSERT_H
#define ASDF_SIM_ASSERT_H

#include <simavr/sim_avr.h>
#include <stdint.h>

/* Run the sim until the next captured byte equals `expected`, or
 * max_cycles elapse without a match. Returns 0 on success, nonzero
 * on failure (and prints a diagnostic to stderr). */
int sim_expect_byte_within(avr_t *cpu, uint8_t expected, uint64_t max_cycles,
                           const char *what);

/* Run the sim for n simulated milliseconds. */
int sim_wait_ms(avr_t *cpu, unsigned ms, uint32_t cpu_hz);

#endif
