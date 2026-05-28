#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <simavr/sim_avr.h>

#include "asdf_simavr_io_select.h"
#include "sim.h"
#include "io.h"
#include "capture.h"
#include "sim_assert.h"
#include "vcd.h"
#include "test_types.h"
#include "keymap_data/asdf_simavr_test_classic.h"
#include "keymap_data/asdf_simavr_test_classic_caps.h"
#include "keymap_data/asdf_simavr_test_apple2.h"
#include "keymap_data/asdf_simavr_test_apple2_caps.h"
#include "keymap_data/asdf_simavr_test_sol.h"
#include "keymap_data/asdf_simavr_test_ace1000.h"

static void usage(const char *argv0)
{
    fprintf(stderr,
        "usage: %s --target <chip> --keymap <name> --elf <path>\n"
        "  --target    atmega328p | atmega168p | atmega1280 | atmega2560\n"
        "              (atmega640 is built but unsupported by simavr 1.6)\n"
        "  --keymap    classic | classic_caps | apple2 | apple2_caps | sol | ace1000\n"
        "  --elf       path to the .elf produced by build-<chip>/\n"
        "  --boot-only boot and run a brief idle period; skip keypress events\n"
        "  --verbose   log every captured output byte\n"
        "  --vcd PATH  dump VCD of watched pins to PATH\n"
        "  --gdb PORT  start simavr gdb stub on PORT and wait for attach\n"
        "  --mode M    events (default) | identity | string\n",
        argv0);
    exit(2);
}

typedef struct {
    const char *target;
    const char *keymap;
    const char *elf_path;
    const char *vcd_path;
    const char *mode;
    int gdb_port;
    int verbose;
    int boot_only;
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
        else if (!strcmp(argv[i], "--mode") && i + 1 < argc) a.mode = argv[++i];
        else if (!strcmp(argv[i], "--verbose")) a.verbose = 1;
        else if (!strcmp(argv[i], "--boot-only")) a.boot_only = 1;
        else { fprintf(stderr, "unknown arg: %s\n", argv[i]); usage(argv[0]); }
    }
    if (!a.target || !a.keymap || !a.elf_path) usage(argv[0]);
    if (!a.mode) a.mode = "events";
    if (strcmp(a.mode, "events") && strcmp(a.mode, "identity") && strcmp(a.mode, "string")) {
        fprintf(stderr, "unknown mode: %s\n", a.mode);
        usage(argv[0]);
    }
    return a;
}

static const sim_keymap_test_t *pick_keymap(const char *name)
{
    if (!strcmp(name, "classic"))      return &classic_test;
    if (!strcmp(name, "classic_caps")) return &classic_caps_test;
    if (!strcmp(name, "apple2"))       return &apple2_test;
    if (!strcmp(name, "apple2_caps"))  return &apple2_caps_test;
    if (!strcmp(name, "sol"))          return &sol_test;
    if (!strcmp(name, "ace1000"))      return &ace1000_test;
    return 0;
}

static const sim_identity_test_t *pick_identity(const char *name)
{
    (void)name;
    /* Populated per-keymap in subsequent tasks. */
    return 0;
}

int main(int argc, char **argv)
{
    args_t a = parse_args(argc, argv);

    const asdf_io_map_t *io = asdf_io_pick(a.target);
    if (!io) { fprintf(stderr, "FAIL: no I/O map for %s\n", a.target); return 1; }

    avr_t *cpu = sim_load(a.target, a.elf_path, io);
    if (!cpu) return 1;

    cap_init();
    io_wire_output(cpu, io);
    io_wire_input(cpu, io);

    if (a.vcd_path) {
        if (vcd_begin(cpu, io, a.vcd_path) != 0)
            fprintf(stderr, "WARN: VCD recording disabled\n");
    }

    if (!strcmp(a.mode, "events")) {
        const sim_keymap_test_t *km = pick_keymap(a.keymap);
        if (!km) { fprintf(stderr, "FAIL: no test data for keymap %s\n", a.keymap); return 1; }

        set_dip(km->dip_value);

        /* Let the firmware boot and run a few scan cycles to settle. */
        if (sim_wait_ms(cpu, km->boot_scan_ticks, io->cpu_frequency_hz) < 0) {
            fprintf(stderr, "FAIL: cpu halted during boot\n");
            return 1;
        }

        /* Boot-only mode: confirm the CPU survived boot, then exit.
         * Run an extra 200 ms of idle time to confirm the scan loop is alive. */
        if (a.boot_only) {
            if (sim_wait_ms(cpu, 200, io->cpu_frequency_hz) < 0) {
                fprintf(stderr, "FAIL: %s/%s cpu halted after boot\n", a.target, a.keymap);
                vcd_end();
                return 1;
            }
            vcd_end();
            printf("OK: %s/%s boot-only smoke passed at cycle %" PRIu64 "\n",
                   a.target, a.keymap, (uint64_t)cpu->cycle);
            return 0;
        }

        /* Drain anything emitted during boot. */
        cap_clear();

        for (int i = 0; i < km->num_events; i++) {
            const sim_event_t *e = &km->events[i];
            char what[64];
            snprintf(what, sizeof what, "%s/event[%d]@(%d,%d)", a.keymap, i, e->row, e->col);

            if (e->with_modifier == SIM_MOD_SHIFT) {
                matrix_press(km->modifier_shift.row, km->modifier_shift.col);
                /* Let the modifier key debounce fully before pressing the main key.
                 * 15 ms = 1.5× the 10 ms debounce period covers worst-case scan
                 * alignment.  SHIFT must be stable before the key lookup runs. */
                sim_wait_ms(cpu, 15, io->cpu_frequency_hz);
                cap_clear();
            } else if (e->with_modifier == SIM_MOD_CTRL) {
                matrix_press(km->modifier_ctrl.row, km->modifier_ctrl.col);
                sim_wait_ms(cpu, 15, io->cpu_frequency_hz);
                cap_clear();
            }

            matrix_press(e->row, e->col);
            if (sim_expect_byte_within(cpu, e->expected, e->hold_cycles, what) != 0) {
                vcd_end();
                return 1;
            }
            matrix_release(e->row, e->col);

            if (e->with_modifier == SIM_MOD_SHIFT)
                matrix_release(km->modifier_shift.row, km->modifier_shift.col);
            else if (e->with_modifier == SIM_MOD_CTRL)
                matrix_release(km->modifier_ctrl.row, km->modifier_ctrl.col);

            /* Wait for debounce + repeat-delay guard before the next event. */
            sim_wait_ms(cpu, 50, io->cpu_frequency_hz);
            cap_clear();
        }

        vcd_end();
        printf("OK: %s/%s passed %d events at cycle %" PRIu64 "\n",
               a.target, a.keymap, km->num_events, (uint64_t)cpu->cycle);
        return 0;
    }

    if (!strcmp(a.mode, "identity")) {
        const sim_identity_test_t *id = pick_identity(a.keymap);
        if (!id) {
            fprintf(stderr, "FAIL: no identity test data for keymap %s\n", a.keymap);
            return 1;
        }

        set_dip(id->dip_value);

        if (sim_wait_ms(cpu, id->boot_scan_ticks, io->cpu_frequency_hz) < 0) {
            fprintf(stderr, "FAIL: cpu halted during identity boot wait\n");
            return 1;
        }

        size_t captured = cap_count();
        if ((int)captured != id->expected_len) {
            fprintf(stderr, "FAIL: %s/%s identity length mismatch: captured %zu, expected %d\n",
                    a.target, a.keymap, captured, id->expected_len);
            for (size_t i = 0; i < captured; i++) {
                asdf_cap_record_t r;
                cap_pop(&r);
                fprintf(stderr, "  [%zu] cycle=%" PRIu64 " byte=0x%02x %c\n",
                        i, r.cycle, r.byte,
                        (r.byte >= 0x20 && r.byte < 0x7f) ? (char)r.byte : '.');
            }
            vcd_end();
            return 1;
        }

        for (int i = 0; i < id->expected_len; i++) {
            asdf_cap_record_t r;
            cap_pop(&r);
            if (r.byte != (uint8_t)id->expected[i]) {
                fprintf(stderr, "FAIL: %s/%s identity byte[%d] = 0x%02x, expected 0x%02x\n",
                        a.target, a.keymap, i, r.byte, (uint8_t)id->expected[i]);
                vcd_end();
                return 1;
            }
        }

        vcd_end();
        printf("OK: %s/%s identity %d bytes at cycle %" PRIu64 "\n",
               a.target, a.keymap, id->expected_len, (uint64_t)cpu->cycle);
        return 0;
    }

    if (!strcmp(a.mode, "string")) {
        fprintf(stderr, "FAIL: string mode not yet implemented for keymap %s\n", a.keymap);
        return 1;
    }

    fprintf(stderr, "FAIL: unreachable\n");
    return 1;
}
