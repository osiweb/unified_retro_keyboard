#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>

#include "asdf_simavr_io_select.h"

static void usage(const char *argv0)
{
    fprintf(stderr,
        "usage: %s --target <chip> --keymap <name> --elf <path>\n"
        "  --target   atmega328p | atmega168p | atmega640 | atmega1280 | atmega2560\n"
        "  --keymap   classic | classic_caps | apple2 | apple2_caps | sol | ace1000\n"
        "  --elf      path to the .elf produced by build-<chip>/\n"
        "  --verbose  log every captured output byte\n"
        "  --vcd PATH dump VCD of watched pins to PATH\n"
        "  --gdb PORT start simavr gdb stub on PORT and wait for attach\n",
        argv0);
    exit(2);
}

typedef struct {
    const char *target;
    const char *keymap;
    const char *elf_path;
    const char *vcd_path;
    int gdb_port;
    int verbose;
} args_t;

static args_t parse_args(int argc, char **argv)
{
    args_t a = {0};
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--target") && i + 1 < argc) a.target = argv[++i];
        else if (!strcmp(argv[i], "--keymap") && i + 1 < argc) a.keymap = argv[++i];
        else if (!strcmp(argv[i], "--elf") && i + 1 < argc) a.elf_path = argv[++i];
        else if (!strcmp(argv[i], "--vcd") && i + 1 < argc) a.vcd_path = argv[++i];
        else if (!strcmp(argv[i], "--gdb") && i + 1 < argc) a.gdb_port = atoi(argv[++i]);
        else if (!strcmp(argv[i], "--verbose")) a.verbose = 1;
        else { fprintf(stderr, "unknown arg: %s\n", argv[i]); usage(argv[0]); }
    }
    if (!a.target || !a.keymap || !a.elf_path) usage(argv[0]);
    return a;
}

int main(int argc, char **argv)
{
    args_t a = parse_args(argc, argv);

    elf_firmware_t fw;
    memset(&fw, 0, sizeof(fw));
    if (elf_read_firmware(a.elf_path, &fw) != 0) {
        fprintf(stderr, "FAIL: could not read ELF %s\n", a.elf_path);
        return 1;
    }

    avr_t *cpu = avr_make_mcu_by_name(a.target);
    if (!cpu) {
        fprintf(stderr, "FAIL: unknown MCU %s\n", a.target);
        return 1;
    }

    avr_init(cpu);

    const asdf_io_map_t *io = asdf_io_pick(a.target);
    if (!io) { fprintf(stderr, "FAIL: no I/O map for %s\n", a.target); return 1; }
    cpu->frequency = io->cpu_frequency_hz;

    avr_load_firmware(cpu, &fw);

    printf("OK: %s mapped to family %s (%u Hz)\n",
           a.target, io->family_name, (unsigned)io->cpu_frequency_hz);
    return 0;
}
