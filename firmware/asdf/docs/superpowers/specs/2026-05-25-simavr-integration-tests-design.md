# simavr-based integration tests for ASDF firmware

## Background and motivation

A latent bug in the SOL-20 keymap went undetected for an extended period
because the existing host-side Unity tests exercise the firmware modules in
isolation but never run the actual AVR-compiled binary end-to-end. The host
tests cannot catch a class of regressions in which the right keymap is
selected at boot, the scan loop runs, but the output produced for a
keypress is wrong (or absent) due to dispatch, table, or arch-layer issues
that only manifest on the target binary.

This spec proposes an integration test stage, run after the AVR firmware
build and before any release/deploy, that drives each per-target ELF
through `simavr` and verifies that each supported keymap is reachable via
its DIP-switch selector and emits correct output for a small set of
representative keypresses.

The work is intentionally being landed before a planned set of larger
architectural changes, so that current behavior is locked in as a
regression baseline before any refactoring begins.

## Goals

- For each (chip target × keymap) pair, prove that booting the firmware
  with the keymap's DIP value selected results in a live scan loop and
  correct ASCII output for 3-6 representative key events.
- Integrate as a CI stage between build and deploy, gated on every push
  and PR targeting `main`.
- Establish a clean authoring pattern so that adding a new keymap test —
  by either a human or an AI coding agent — is a five-step recipe with no
  hidden machinery.
- Test exclusively through the external AVR I/O surface (port pins), so
  that internal refactors do not invalidate the tests.

## Non-goals

- Exhaustive per-cell verification of every key in every modifier state.
  Tests are smoke-grade; they catch keymap-wide regressions, not
  individual table-cell typos.
- Replacing the existing host-side Unity tests. Those remain unchanged.
- Cycle-exact timing verification. Tests assert correct outputs within
  generous cycle budgets.
- Hardware-in-the-loop testing. simavr only.

## Design principle

The test harness never `#include`s any ASDF source header and never calls
any ASDF function. It links only against `libsimavr` and the standard C
library. It observes and stimulates the firmware exclusively through AVR
port pins. This is what lets the tests survive the upcoming architectural
churn.

## Architecture

A new top-level `test/simavr/` tree, parallel to the existing host-test
`test/` tree, containing:

```
test/simavr/
  asdf_simavr_runner.c           # main, ~100 lines
  CMakeLists.txt
  README.md                      # authoring recipe (Section: Authoring)
  harness/
    sim.c sim.h                  # simavr boot, MCU instantiation, ELF load
    io.c io.h                    # pin notifier wiring, column injection
    run.c run.h                  # avr_run loop, predicates, timeout
    capture.c capture.h          # output-byte ring buffer
    assert.c assert.h            # SIM_EXPECT_* macros, failure reporting
    vcd.c vcd.h                  # optional VCD dump
    test_types.h                 # sim_keymap_test_t, sim_event_t definitions
  arch_io/
    asdf_simavr_io_familyA.h     # 328p/168p/88p port:bit map + clock
    asdf_simavr_io_familyB.h     # 2560/1280/640 port:bit map + clock
  keymap_data/
    asdf_simavr_test_classic.h
    asdf_simavr_test_classic_caps.h
    asdf_simavr_test_apple2.h
    asdf_simavr_test_apple2_caps.h
    asdf_simavr_test_sol.h
    asdf_simavr_test_ace1000.h
```

The full harness is approximately 300-500 lines of C, no dependencies
beyond `libsimavr` and `libelf` (the latter transitively via libsimavr).

A new CMake architecture configuration `simavr_test` builds the runner as
a host executable independently of any AVR target build. It is invoked
via:

```bash
mkdir build-simavr-test
cd build-simavr-test
cmake .. -DARCH=simavr_test
make
ctest
```

The runner takes `--target <chip> --keymap <name> --elf <path>` and exits
0 on pass, nonzero on the first failed assertion. CMake generates one
`add_test` per (target, keymap) pair, so ctest reports cases as
`simavr_atmega2560_sol`, `simavr_atmega328p_classic`, etc.

## Harness components

### libsimavr boot (`harness/sim.c`)

1. `avr_make_mcu_by_name(target)` instantiates the correct MCU model.
2. `elf_read_firmware(elf_path, &fw)` parses the ELF (debug symbols
   present — the existing build emits them).
3. `avr_load_firmware(cpu, &fw)`.
4. Set `cpu->frequency` from the family I/O table (8 MHz family A, 16 MHz
   family B).
5. `avr_init(cpu)`.

### Pin wiring (`harness/io.c`)

For each pin of interest, get the IRQ handle via
`avr_io_getirq(cpu, AVR_IOCTL_IOPORT_GETIRQ('X'), bit)`. Two directions:

- **Output observation** — register `avr_irq_register_notify()` callbacks
  on every bit of the data port (PORTD on family A, PORTH on family B)
  and on the strobe pin (PINB[6] on family A, PINB[4] on family B). The
  strobe-edge callback latches the current data-port byte into the
  capture buffer.
- **Input injection** — use `avr_raise_irq()` to drive the matrix column
  inputs and DIP-switch reads. The harness watches for each row strobe
  and presents the configured column pattern for that row in response.

DIP switches are read by the firmware as matrix row 8 across all 8
columns. The harness intercepts the row-8 strobe and presents the
configured DIP value on the columns.

The two `arch_io/asdf_simavr_io_family*.h` headers encode the port:bit
map and CPU frequency for each family. The runner picks the right one
based on `--target`. The map values are derived from
`src/Arch/asdf_arch_atmega328p.h` and `src/Arch/asdf_arch_atmega2560.h`
respectively, but the harness never includes those headers — the values
are duplicated by hand and protected by an at-startup sanity check that
the first observed strobe arrives at the expected interval (proves clock
and timer configuration match the harness's assumptions).

### Stepping model (`harness/run.c`)

Single primitive: `sim_run_until(predicate, timeout_cycles)`. Calls
`avr_run(cpu)` in a loop until the predicate returns true, the cpu
enters a crashed or sleeping state, or `timeout_cycles` elapse.

Predicates used by tests:

- `cap_has_byte` — at least one byte in the output capture buffer.
- `scan_ticks_geq(n)` — proves the timer/scan loop is alive.
- `wall_time_geq(ms)` — bounded fallback when the harness needs to wait
  out a debounce window before the next event.

### Output capture (`harness/capture.c`)

A fixed-size ring buffer of `(cycle_timestamp, data_byte)` records,
appended from inside the strobe-edge notifier. `capture_pop()` and
`capture_drain()` consume entries for assertions.

### Assertion API (`harness/assert.c`)

- `SIM_EXPECT_BYTE_WITHIN(byte, max_cycles)` — runs the sim until either
  the next captured byte equals `byte` (pass), `max_cycles` elapse
  without a match (fail), or the cpu crashes (fail). On failure, prints
  expected byte, actual captured bytes since last assertion, sim-time at
  failure, and the configured event description.
- `SIM_EXPECT_SCAN_TICKS(n, max_cycles)` — proves the scan loop is
  running.

### VCD dump (`harness/vcd.c`)

When `--vcd <path>` is passed, the harness uses libsimavr's
`avr_vcd_init` / `avr_vcd_add_signal` / `avr_vcd_start` API to record
the data port (8 bits), strobe, LED1/2/3, the DIP column bits, and the
first four row strobes for the entire run. The CI workflow uploads VCDs
as artifacts on test failure.

## Per-keymap test data format

Each keymap has its own header in `test/simavr/keymap_data/`. A
representative example:

```c
#ifndef ASDF_SIMAVR_TEST_SOL_H
#define ASDF_SIMAVR_TEST_SOL_H
#include "../harness/test_types.h"

static const sim_keymap_test_t sol_test = {
    .name      = "sol",
    .dip_value = 0x04,                   /* matches <sol:4> in keymap_list.cmake */
    .boot_scan_ticks = 50,               /* >=50 timer interrupts before driving input */
    .modifier_shift  = { .row = 6, .col = 7 },   /* per-keymap SHIFT matrix coord */
    .modifier_ctrl   = { .row = 3, .col = 0 },
    .events = (const sim_event_t[]){
        { .row = 2, .col = 3, .hold_cycles = 20000, .expected = 'a' },
        { .row = 2, .col = 3, .hold_cycles = 20000, .expected = 'A',
          .with_modifier = SIM_MOD_SHIFT },
        { .row = 5, .col = 1, .hold_cycles = 20000, .expected = '\r' },
    },
    .num_events = 3,
};

#endif
```

The runner selects the struct via a small `switch` on `--keymap` in
`asdf_simavr_runner.c`, with each case `#include`-ing the matching
header. No string-to-symbol lookup, no parser, no codegen.

**Coordinate semantics**: `row` and `col` are physical matrix
coordinates, not key labels. A future matrix-shuffle in the keymap source
would require updating the test header — this is the cost of decoupling
tests from keymap internals, and is judged acceptable.

**Modifier handling**: `with_modifier` is resolved by the runner into
"also hold the configured `modifier_shift` (or `modifier_ctrl`) coord
during this keypress." The per-keymap modifier coordinates live in the
same header alongside the events.

**Authoring rules**:

- Test data is checked against the *current behavior* of the keymap, not
  against the keymap source. The question being answered is "does row 2
  col 3 still emit `a`?", not "does the keymap table say `a` at row 2
  col 3?".
- Each keymap gets 3-6 events: at minimum one plain key, one shifted
  key, and one symbol or control key.
- The DIP value in the header must match the entry in
  `keymap_list.cmake`. A runtime self-check guards against drift:
  immediately after `boot_scan_ticks`, the harness drives the first
  configured event and fails with a clear message if no output appears
  at all within a generous window (typically symptomatic of the wrong
  keymap being selected).

## CMake / ctest integration

A new arch configuration file `cmake/arch/simavr_test.cmake`:

- Sets the host compiler (not `avr-gcc`).
- Declares libsimavr via `find_package(PkgConfig); pkg_check_modules(SIMAVR REQUIRED simavr)`.
- Excludes the entire `src/` tree from the build.

`test/simavr/CMakeLists.txt` builds the runner and enumerates the
matrix:

```cmake
set(simavr_targets atmega328p atmega168p atmega640 atmega1280 atmega2560)
include(${CMAKE_SOURCE_DIR}/keymap_list.cmake)  /* populates keymap_list */

foreach(tgt ${simavr_targets})
  foreach(km_entry ${keymap_list})
    string(REGEX REPLACE "[<>]" "" km_clean ${km_entry})
    string(REPLACE ":" ";" km_pair ${km_clean})
    list(GET km_pair 0 km_name)
    set(elf_path ${CMAKE_SOURCE_DIR}/build-${tgt}/src/asdf-v${ASDF_VERSION}-${tgt}.elf)
    add_test(
      NAME simavr_${tgt}_${km_name}
      COMMAND asdf_simavr_runner --target ${tgt} --keymap ${km_name} --elf ${elf_path}
    )
    set_tests_properties(simavr_${tgt}_${km_name} PROPERTIES TIMEOUT 10)
  endforeach()
endforeach()
```

Total cases: 5 targets × 6 keymaps = 30. Each case runs in tens of
milliseconds of wall time in simavr.

The `simavr_test` configuration depends on the per-target `build-<tgt>/`
directories already containing `.elf` outputs. It does not trigger the
AVR builds itself; sequencing is the caller's responsibility (in CI: the
`build_firmware` job; locally: `make-targets.sh -t simavr_test` performs
a pre-flight check).

## Local build story

The existing one-command UX is extended:

```bash
bash make-targets.sh -t simavr_test
```

This script step performs, in order:

1. Verify `simavr` and `libsimavr-dev` are installed (probe for the
   pkg-config entry). On failure print a one-liner install command for
   Ubuntu/Debian and macOS Homebrew, then exit nonzero.
2. Verify each `build-<chip>/src/*.elf` exists. On failure print
   `Missing ELFs. Run: bash make-targets.sh -a` and exit nonzero. Do not
   trigger the AVR build implicitly.
3. `mkdir -p build-simavr-test && cd build-simavr-test && cmake .. -DARCH=simavr_test && make && ctest --output-on-failure`.

**One-case iteration loop** (the typical loop while writing a new test
or fixing a regression):

```bash
cd build-simavr-test
ctest -R simavr_atmega2560_sol -V
./test/simavr/asdf_simavr_runner \
  --target atmega2560 --keymap sol \
  --elf ../build-atmega2560/src/asdf-v1.6.6-atmega2560.elf \
  --verbose --vcd run.vcd
gtkwave run.vcd
```

Runner flags:

- `--verbose` — log every captured output byte with sim-time and
  associated configured event.
- `--vcd <path>` — write a VCD of all watched pins for the full run.
- `--gdb <port>` — start the simavr GDB stub on the given port and
  block waiting for an attach. Then:
  `avr-gdb build-atmega2560/src/asdf-v1.6.6-atmega2560.elf -ex 'target remote :1234'`.

## CI workflow changes

The existing `.github/workflows/asdf-firmware.yml` is extended. The
existing `build_firmware` job is unchanged except for adding an artifact
upload of the per-target ELFs. A new `integration_test` job runs on
`ubuntu-latest` (clean apt access to `simavr` / `libsimavr-dev`,
avoiding Alpine packaging differences) and depends on `build_firmware`.
A `deploy` job, lifted from the current job's sphinx + pages-deploy
steps, runs only on `asdf-release` pushes.

```yaml
name: asdf-firmware
on:
  push:
    branches: [main, asdf-release, asdf-build-test]
  pull_request:
    branches: [main]

jobs:
  build_firmware:
    runs-on: ubuntu-latest
    container: { image: alpine }
    defaults:
      run:
        shell: sh
    steps:
      - name: install_git_and_bash
        run: apk add bash git rsync
      - name: checkout
        uses: actions/checkout@v2
      - run: apk add gcc-avr binutils-avr avr-libc
      - run: apk add cmake make
      - run: cd firmware/asdf; /bin/bash ./make-targets.sh -a -i -s
      - name: Upload built ELFs
        uses: actions/upload-artifact@v4
        with:
          name: asdf-elfs
          path: firmware/asdf/build-atmega*/src/*.elf
          retention-days: 7
      - name: Upload docs/dist for deploy
        uses: actions/upload-artifact@v4
        with:
          name: asdf-docs-dist
          path: |
            firmware/asdf/docs/source/
            firmware/asdf/dist/
          retention-days: 7

  integration_test:
    needs: build_firmware
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - name: Install deps
        run: |
          sudo apt-get update
          sudo apt-get install -y cmake build-essential simavr libsimavr-dev pkg-config
      - name: Download ELFs
        uses: actions/download-artifact@v4
        with:
          name: asdf-elfs
          path: firmware/asdf/
      - name: Configure
        run: |
          cd firmware/asdf
          mkdir build-simavr-test
          cd build-simavr-test
          cmake .. -DARCH=simavr_test
      - name: Build runner
        run: cd firmware/asdf/build-simavr-test && make
      - name: Run integration tests
        run: cd firmware/asdf/build-simavr-test && ctest --output-on-failure
      - name: Upload VCD on failure
        if: failure()
        uses: actions/upload-artifact@v4
        with:
          name: simavr-vcd-traces
          path: firmware/asdf/build-simavr-test/test/simavr/*.vcd
          retention-days: 14

  deploy:
    needs: integration_test
    if: github.ref == 'refs/heads/asdf-release'
    runs-on: ubuntu-latest
    container: { image: alpine }
    defaults:
      run:
        shell: sh
    steps:
      - name: install_git_and_bash
        run: apk add bash git rsync
      - uses: actions/checkout@v2
      - run: apk add python3 py3-pip
      - run: pip install -U sphinx sphinx-rtd-theme sphinx-autodoc-typehints
      - run: pip install -U sphinxcontrib-napoleon
      - run: pip install -U toml
      - name: Download docs/dist
        uses: actions/download-artifact@v4
        with:
          name: asdf-docs-dist
          path: firmware/asdf/
      - run: mkdir public; touch public/.nojekyll
      - run: sphinx-build -b html firmware/asdf/docs/source public
      - name: Deploy
        uses: JamesIves/github-pages-deploy-action@v4
        with:
          folder: public
```

Three explicit changes to call out:

1. `on:` is broadened to include `main` (push + PR). The release/deploy
   behavior is preserved by the `deploy` job's
   `if: github.ref == 'refs/heads/asdf-release'` gate.
2. ELFs and docs are passed between jobs via artifacts so the AVR build
   does not have to run twice.
3. On test failure, VCD traces from the harness are uploaded as
   artifacts for offline inspection.

## Authoring a new keymap test

The recipe lives in `test/simavr/README.md`:

1. Build the firmware: `bash make-targets.sh -a`.
2. Copy `keymap_data/asdf_simavr_test_classic.h` to
   `asdf_simavr_test_<new>.h`. Rename the struct. Set `dip_value` to
   match the entry in `keymap_list.cmake`. Set `modifier_shift` and
   `modifier_ctrl` to the new keymap's matrix coords for those keys.
3. Add `<new>` to `simavr_keymap_list` in
   `test/simavr/CMakeLists.txt`.
4. Add a `case "<new>":` entry to the keymap dispatch switch in
   `asdf_simavr_runner.c` (it `#include`s the new header and returns a
   pointer to the new struct).
5. Pick three matrix coordinates from the new keymap's matrix source.
   For each, decide the expected ASCII byte for plain, shifted, and (if
   exercised) control. Add them as events in the new header.
6. `bash make-targets.sh -t simavr_test`. New cases appear
   automatically (`simavr_<each-target>_<new>`).
7. On failure, re-run the one case with `--verbose --vcd run.vcd` and
   inspect.

All steps reference concrete file paths. No parser, no codegen, no
magic — the pattern is friendly to both human authors and AI coding
agents.

## Out-of-scope follow-ups (not part of this work)

- Cycle-accurate measurement of debounce intervals.
- Coverage tracking across the keymap tables.
- Replacing host-side Unity tests with simavr equivalents.
- Adding USB / serial output testing (no current keymap exercises a
  UART path under normal operation).
