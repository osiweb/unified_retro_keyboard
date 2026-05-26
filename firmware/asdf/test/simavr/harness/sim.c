#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <simavr/sim_elf.h>

#include "sim.h"

avr_t *sim_load(const char *target, const char *elf_path,
                const asdf_io_map_t *io)
{
    elf_firmware_t fw;
    memset(&fw, 0, sizeof(fw));
    if (elf_read_firmware(elf_path, &fw) != 0) {
        fprintf(stderr, "FAIL: could not read ELF %s\n", elf_path);
        return 0;
    }

    avr_t *cpu = avr_make_mcu_by_name(target);
    if (!cpu) {
        fprintf(stderr, "FAIL: unknown MCU %s\n", target);
        return 0;
    }

    avr_init(cpu);
    avr_load_firmware(cpu, &fw);
    cpu->frequency = io->cpu_frequency_hz;
    return cpu;
}

void sim_free(avr_t *cpu)
{
    /* libsimavr 1.6 has no public destructor for avr_t;
     * relying on process exit for cleanup is intentional. */
    (void)cpu;
}
