#include "run.h"

int sim_run_until(avr_t *cpu, sim_predicate_t pred, void *ctx,
                  uint64_t max_cycles)
{
    uint64_t start = cpu->cycle;
    while (cpu->cycle - start < max_cycles) {
        if (pred(ctx)) return 1;
        int state = avr_run(cpu);
        if (state == cpu_Done || state == cpu_Crashed) return -1;
    }
    return 0;
}

int sim_run_for(avr_t *cpu, uint64_t n_cycles)
{
    uint64_t end = cpu->cycle + n_cycles;
    while (cpu->cycle < end) {
        int state = avr_run(cpu);
        if (state == cpu_Done || state == cpu_Crashed) return -1;
    }
    return 0;
}
