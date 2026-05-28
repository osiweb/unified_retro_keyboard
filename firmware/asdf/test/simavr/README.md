# simavr integration tests

These tests run each per-target ASDF firmware ELF through simavr, drive
matrix inputs via port-pin IRQs, and assert correct ASCII output for a few
representative keypresses per keymap.

## Run locally

```bash
bash make-targets.sh -a              # build AVR firmware (one-time)
bash make-targets.sh -t simavr_test  # build runner, run ctest matrix
```

`make-targets.sh -t simavr_test` checks that `simavr` and
`libsimavr-dev` headers are installed and that all five AVR ELFs exist
before invoking cmake and ctest. If either check fails it prints the
relevant install or build command and exits nonzero.

### Supported targets

```
atmega328p  atmega168p  atmega1280  atmega2560
```

atmega640 is built by `make-targets.sh -a` but simavr 1.6 on Ubuntu does
not support that core; its cases are not registered in the ctest matrix.

All four supported targets run the full event-driven sequence (matrix
press, modifier handling, byte-level output assertion). Family A's
serial-shift-register column read is emulated by the harness in
`io.c::on_col_clock_familyA`, which tracks COLMODE / COLCLK transitions
and feeds bits onto PINB[0] one at a time.

## Iterate on a single case

```bash
cd build-simavr-test
ctest -R simavr_atmega2560_sol -V    # one case, verbose ctest output
./test/simavr/asdf_simavr_runner \
    --target atmega2560 --keymap sol \
    --elf ../build-atmega2560/src/asdf-v1.7.0-atmega2560.elf \
    --verbose --vcd /tmp/sol.vcd
gtkwave /tmp/sol.vcd
```

Runner flags:

- `--verbose` — log every captured output byte with sim-cycle timestamp.
- `--vcd <path>` — write a VCD of all watched pins for the full run.
  On CI, VCDs are uploaded as artifacts on test failure so they can be
  fetched and opened in gtkwave locally.
- `--boot-only` — skip keypress events; confirm only that the CPU survives
  the boot period without halting. Useful when bringing up a new target
  before its column-injection wiring is in place.
- `--gdb <port>` — start the simavr GDB stub on the given port and wait
  for a debugger attach. Then connect with:
  `avr-gdb build-atmega2560/src/asdf-v1.7.0-atmega2560.elf -ex 'target remote :1234'`

## Add a new keymap test

1. Build the firmware: `bash make-targets.sh -a`.

2. Copy `keymap_data/asdf_simavr_test_classic.h` to
   `keymap_data/asdf_simavr_test_<new>.h`. Rename the struct and events
   array (`<new>_test`, `<new>_events`).

3. Set `dip_value` to match the entry in `keymap_list.cmake`.

4. Set `modifier_shift` and `modifier_ctrl` to the new keymap's matrix
   row/col coordinates for those keys. Read
   `src/Keymaps/asdf_keymap_<new>.c` to find them.

5. Add `<new>` to `SIMAVR_KEYMAPS` in `test/simavr/CMakeLists.txt`. The
   ctest matrix automatically generates one case per (target, keymap).

6. Add a `case` to `pick_keymap` in `asdf_simavr_runner.c`: add an
   `#include "keymap_data/asdf_simavr_test_<new>.h"` near the top of
   the file and a `if (!strcmp(name, "<new>")) return &<new>_test;` line
   in `pick_keymap`. There is no auto-dispatch; the function must be
   updated explicitly.

7. Pick 3-6 matrix coordinates from the new keymap's matrix source.
   For each entry in the `events` array, record the `(row, col)` of a
   physical key and the expected ASCII byte it should produce in the
   given modifier state (plain, shift, or ctrl).

   Check whether the keymap activates CAPS lock at boot. Keymaps such as
   `apple2`, `sol`, and `ace1000` call `asdf_modifier_capslock_activate()`
   in their setup function (`src/Keymaps/asdf_keymap_<name>.c`), which
   means alphabetic keys produce uppercase by default. Adjust the
   `expected` bytes in the events array accordingly — a plain `a` press
   on a boot-CAPS keymap should expect `'A'`, not `'a'`.

8. Run `bash make-targets.sh -t simavr_test`. New ctest cases appear as
   `simavr_<each-target>_<new>` and run automatically.

9. If a case fails, re-run with `--verbose --vcd /tmp/debug.vcd` and
   inspect in gtkwave. The most common causes are wrong matrix
   coordinates (re-read the keymap source), a wrong DIP value (check
   `keymap_list.cmake`), or a boot-CAPS mismatch in the expected bytes.

## Architecture

The harness lives entirely under `test/simavr/` and links `libsimavr`.
It never includes ASDF source headers — it communicates with the firmware
exclusively via AVR port pins, so internal refactors to the firmware do
not break these tests.

Key components:

- `harness/sim.{c,h}` — ELF load, MCU instantiation, frequency override.
- `harness/io.{c,h}` — strobe-edge capture notifier, matrix column
  injection, DIP-switch state.
- `harness/run.{c,h}` — bounded `avr_run` loop with predicate support.
- `harness/capture.{c,h}` — fixed ring buffer of `(cycle, byte)` records.
- `harness/sim_assert.{c,h}` — `sim_expect_byte_within`, failure
  diagnostics with hex + ASCII display.
- `harness/vcd.{c,h}` — optional VCD dump of data port, strobe, LEDs,
  and row port.
- `arch_io/asdf_simavr_io_family{A,B}.h` — port:bit maps and CPU
  frequency for the two AVR families, derived by hand from
  `src/Arch/asdf_arch_atmega328p.h` and `src/Arch/asdf_arch_atmega2560.h`.
  If those source pin assignments ever change, update the `arch_io`
  headers in lockstep.
- `keymap_data/asdf_simavr_test_<name>.h` — per-keymap DIP value,
  modifier coordinates, and event list.

See `docs/superpowers/specs/2026-05-25-simavr-integration-tests-design.md`
for the full design rationale.
