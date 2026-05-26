#include <stdio.h>
#include <inttypes.h>

#include "assert.h"
#include "run.h"
#include "capture.h"

static int pred_has_byte(void *ctx) { (void)ctx; return cap_count() > 0; }

int sim_expect_byte_within(avr_t *cpu, uint8_t expected, uint64_t max_cycles,
                           const char *what)
{
    int rc = sim_run_until(cpu, pred_has_byte, 0, max_cycles);
    if (rc < 0) {
        fprintf(stderr, "FAIL [%s]: cpu halted while waiting for 0x%02x ('%c')\n",
                what, expected, (expected >= 0x20 && expected < 0x7f) ? expected : '?');
        return 1;
    }
    if (rc == 0) {
        fprintf(stderr, "FAIL [%s]: no output within %" PRIu64 " cycles (expected 0x%02x)\n",
                what, max_cycles, expected);
        return 1;
    }

    asdf_cap_record_t r;
    cap_pop(&r);
    if (r.byte != expected) {
        fprintf(stderr, "FAIL [%s]: expected 0x%02x ('%c'), got 0x%02x ('%c') at cycle %" PRIu64 "\n",
                what,
                expected, (expected >= 0x20 && expected < 0x7f) ? expected : '?',
                r.byte, (r.byte >= 0x20 && r.byte < 0x7f) ? r.byte : '?',
                r.cycle);
        return 1;
    }
    return 0;
}

int sim_wait_ms(avr_t *cpu, unsigned ms, uint32_t cpu_hz)
{
    uint64_t cycles = ((uint64_t)cpu_hz / 1000) * ms;
    return sim_run_for(cpu, cycles);
}
