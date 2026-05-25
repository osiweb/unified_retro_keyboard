# simavr Integration Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Land a CI-integrated simavr harness that boots each per-target ASDF firmware ELF, drives every keymap via its DIP value, and asserts correct ASCII output for a few representative keypresses — locking in current behavior before larger architectural changes.

**Architecture:** A new host-built C test runner under `test/simavr/` links libsimavr, loads the per-target ELF, hooks AVR port pins via `avr_irq_register_notify`, injects DIP/matrix-column states via `avr_raise_irq`, captures emitted bytes off the strobe pin, and asserts via a tiny macro library. CMake enumerates 5 targets × 6 keymaps as 30 ctest cases. The harness includes no ASDF source headers — it talks only to AVR pins, so internal refactors don't break it.

**Tech Stack:** C99, libsimavr (Ubuntu `libsimavr-dev`, version 1.6+), CMake, ctest, GitHub Actions.

**Spec:** `docs/superpowers/specs/2026-05-25-simavr-integration-tests-design.md`

---

## Pre-flight assumptions

These are true at the start of Task 1:

- Working directory: `/users/dave/vsrc/unified_retro_keyboard/firmware/asdf`.
- `git status` is clean of changes from prior tasks; you commit after each task.
- The AVR firmware build directories (`build-atmega328p`, `build-atmega168p`, `build-atmega640`, `build-atmega1280`, `build-atmega2560`) already exist and contain a `src/asdf-v1.6.6-<target>.elf`. If not, run `bash make-targets.sh -a` once before starting Task 3.
- atmega88p is omitted from the test matrix (no build directory exists; not a release target).

---

## File structure

Files created or modified by this plan:

**Created:**
- `test/simavr/CMakeLists.txt`
- `test/simavr/asdf_simavr_runner.c`
- `test/simavr/README.md`
- `test/simavr/harness/sim.c`, `sim.h`
- `test/simavr/harness/io.c`, `io.h`
- `test/simavr/harness/capture.c`, `capture.h`
- `test/simavr/harness/run.c`, `run.h`
- `test/simavr/harness/assert.c`, `assert.h`
- `test/simavr/harness/vcd.c`, `vcd.h`
- `test/simavr/harness/test_types.h`
- `test/simavr/arch_io/asdf_simavr_io_familyA.h`
- `test/simavr/arch_io/asdf_simavr_io_familyB.h`
- `test/simavr/arch_io/asdf_simavr_io_select.h`
- `test/simavr/keymap_data/asdf_simavr_test_classic.h`
- `test/simavr/keymap_data/asdf_simavr_test_classic_caps.h`
- `test/simavr/keymap_data/asdf_simavr_test_apple2.h`
- `test/simavr/keymap_data/asdf_simavr_test_apple2_caps.h`
- `test/simavr/keymap_data/asdf_simavr_test_sol.h`
- `test/simavr/keymap_data/asdf_simavr_test_ace1000.h`

**Modified:**
- `CMakeLists.txt` (add `simavr_test` ARCH branch)
- `make-targets.sh` (add `simavr_test` handling)
- `../../.github/workflows/asdf-firmware.yml` (split into build/test/deploy)

---

## Task 1: Verify development environment

**Files:** none (environment check only)

- [ ] **Step 1: Verify simavr binary is on PATH**

Run: `which simavr && simavr --help 2>&1 | head -3`
Expected: prints a path and the simavr usage banner. If not installed:
- Ubuntu/Debian: `sudo apt-get install -y simavr libsimavr-dev pkg-config`
- macOS: `brew install simavr` (note: macOS lacks `libsimavr-dev` — this plan is Linux-first; Mac users will need to build libsimavr from source. CI is Linux.)

- [ ] **Step 2: Verify libsimavr headers and library are available**

Run:
```bash
test -f /usr/include/simavr/sim_avr.h && echo HEADERS-OK
test -f /usr/include/simavr/sim_elf.h && echo ELF-OK
test -f /usr/include/simavr/avr_ioport.h && echo IOPORT-OK
test -f /usr/include/simavr/sim_vcd_file.h && echo VCD-OK
ldconfig -p | grep -E "libsimavr\.so" && echo LIB-OK
```
Expected: all five "OK" lines printed.

- [ ] **Step 3: Verify the AVR firmware ELFs exist**

Run:
```bash
for t in atmega328p atmega168p atmega640 atmega1280 atmega2560; do
  ls -la build-$t/src/asdf-v1.6.6-$t.elf 2>&1 | head -1
done
```
Expected: 5 lines, each showing an existing `.elf` file with nonzero size. If any are missing, run `bash make-targets.sh -a` and re-check.

- [ ] **Step 4: No commit** (this task only verifies preconditions).

---

## Task 2: Add `simavr_test` ARCH branch + skeleton subdirectory

**Files:**
- Modify: `CMakeLists.txt` (root) lines 86-102
- Create: `test/simavr/CMakeLists.txt`

- [ ] **Step 1: Add a placeholder CMakeLists in the new subtree**

Create `test/simavr/CMakeLists.txt` with:
```cmake
cmake_minimum_required(VERSION 3.19)

# Host-built test runner — never compiled with avr-gcc.
# Built when the root CMakeLists.txt is invoked with -DARCH=simavr_test.

message(STATUS "simavr integration test runner: placeholder build")
```

- [ ] **Step 2: Add a `simavr_test` branch to the root `CMakeLists.txt`**

Change the existing block at lines 86-102 from:
```cmake
if(ARCH MATCHES test)
  add_subdirectory(test)
else()
  if(ARCH_TYPE MATCHES AVR)
    set (PROJECT_EXECUTABLE_TARGET_NAME ${PROJECT_TARGET_NAME}.elf)

    function(custom_add_library EXECUTABLE_NAME)
      add_avr_library(${EXECUTABLE_NAME} ${ARGN})
    endfunction(custom_add_library)

    function(custom_add_executable EXECUTABLE_NAME)
      add_avr_executable(${EXECUTABLE_NAME} ${ARGN})
    endfunction(custom_add_executable)
  endif()

  add_subdirectory(src)
endif()
```
to:
```cmake
if(ARCH MATCHES simavr_test)
  enable_testing()
  add_subdirectory(test/simavr)
elseif(ARCH MATCHES test)
  add_subdirectory(test)
else()
  if(ARCH_TYPE MATCHES AVR)
    set (PROJECT_EXECUTABLE_TARGET_NAME ${PROJECT_TARGET_NAME}.elf)

    function(custom_add_library EXECUTABLE_NAME)
      add_avr_library(${EXECUTABLE_NAME} ${ARGN})
    endfunction(custom_add_library)

    function(custom_add_executable EXECUTABLE_NAME)
      add_avr_executable(${EXECUTABLE_NAME} ${ARGN})
    endfunction(custom_add_executable)
  endif()

  add_subdirectory(src)
endif()
```

Also: at the top of the root `CMakeLists.txt`, the existing `ARCH MATCHES atmega...` blocks at lines 11-62 set `CMAKE_TOOLCHAIN_FILE` to the AVR toolchain. For `simavr_test`, leave `CMAKE_TOOLCHAIN_FILE` unset so the host compiler is used. No change needed — the existing branches simply don't fire for `ARCH=simavr_test`.

- [ ] **Step 3: Configure and build**

Run:
```bash
mkdir -p build-simavr-test && cd build-simavr-test
cmake .. -DARCH=simavr_test
make
```
Expected: cmake succeeds, prints the "placeholder build" message, no compile errors (nothing to compile yet).

- [ ] **Step 4: Verify `ctest` runs cleanly with zero tests**

Run: `ctest` (still inside `build-simavr-test/`)
Expected: `No tests were found!!!` (or similar) and exit code 0. This is fine for the skeleton; tests appear in Task 13.

- [ ] **Step 5: Commit**

```bash
cd ..
git add CMakeLists.txt test/simavr/CMakeLists.txt
git commit -m "scaffold simavr_test arch and test/simavr/ subtree

- new ARCH=simavr_test branch in root CMakeLists.txt routes to
  test/simavr/, host-built (no avr-gcc toolchain).
- placeholder test/simavr/CMakeLists.txt builds nothing; populated by
  later tasks."
```

---

## Task 3: Minimal runner that loads an ELF

**Files:**
- Create: `test/simavr/asdf_simavr_runner.c`
- Modify: `test/simavr/CMakeLists.txt`

- [ ] **Step 1: Create the runner stub**

Create `test/simavr/asdf_simavr_runner.c`:
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <simavr/sim_avr.h>
#include <simavr/sim_elf.h>

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

    elf_firmware_t fw = {{0}};
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
    avr_load_firmware(cpu, &fw);

    printf("OK: loaded %s into %s (frequency=%u Hz)\n",
           a.elf_path, a.target, (unsigned)cpu->frequency);
    return 0;
}
```

- [ ] **Step 2: Wire the runner into `test/simavr/CMakeLists.txt`**

Replace the file's contents with:
```cmake
cmake_minimum_required(VERSION 3.19)

# Host-built test runner; never compiled with avr-gcc.

add_executable(asdf_simavr_runner asdf_simavr_runner.c)
target_compile_options(asdf_simavr_runner PRIVATE -Wall -Wextra -Wno-unused-parameter -std=c99)
target_link_libraries(asdf_simavr_runner PRIVATE simavr elf)
```

Note on linkage: `libsimavr-dev` does not ship a `simavr.pc` on Ubuntu 24.04. Direct `-lsimavr -lelf` is the supported path.

- [ ] **Step 3: Build the runner**

Run:
```bash
cd build-simavr-test
cmake .. -DARCH=simavr_test
make
```
Expected: produces `test/simavr/asdf_simavr_runner` with no warnings beyond unused parameters.

- [ ] **Step 4: Smoke-test the runner with a real ELF**

Run:
```bash
./test/simavr/asdf_simavr_runner \
  --target atmega2560 --keymap classic \
  --elf ../build-atmega2560/src/asdf-v1.6.6-atmega2560.elf
```
Expected: exits 0 and prints `OK: loaded ... into atmega2560 (frequency=16000000 Hz)` — assuming simavr defaults the frequency from the MCU model. If frequency prints as 0, that's fine for this task; we set it explicitly in Task 5.

- [ ] **Step 5: Commit**

```bash
cd ..
git add test/simavr/asdf_simavr_runner.c test/simavr/CMakeLists.txt
git commit -m "add minimal simavr runner that loads an avr ELF and exits

- accepts --target / --keymap / --elf plus --verbose, --vcd, --gdb
  stubs that are wired in by later tasks.
- links libsimavr and libelf directly (no .pc on Ubuntu)."
```

---

## Task 4: I/O surface tables for the two arch families

**Files:**
- Create: `test/simavr/arch_io/asdf_simavr_io_familyA.h`
- Create: `test/simavr/arch_io/asdf_simavr_io_familyB.h`
- Create: `test/simavr/arch_io/asdf_simavr_io_select.h`

These tables encode where each pin lives. Values are derived from `src/Arch/asdf_arch_atmega328p.h` and `asdf_arch_atmega2560.h` but **the harness does not include those headers** — the values are duplicated here on purpose so the harness stays decoupled.

- [ ] **Step 1: Create `test/simavr/arch_io/asdf_simavr_io_familyA.h`**

```c
#ifndef ASDF_SIMAVR_IO_FAMILYA_H
#define ASDF_SIMAVR_IO_FAMILYA_H

/* Pin map for atmega328p / atmega168p / atmega88p.
 * Source of truth: src/Arch/asdf_arch_atmega328p.h.
 * Duplicated here so the harness stays decoupled from ASDF source. */

#include "asdf_simavr_io_select.h"

static const asdf_io_map_t asdf_io_familyA = {
    .family_name      = "A",
    .cpu_frequency_hz = 8000000U,

    .row_port  = 'C',
    .row_mask  = 0x0F,            /* PORTC[3:0]: 4-bit row index */
    .row_shift = 0,
    .row_active_low = 0,

    /* Family A reads one column at a time via shift register on PINB[0]. */
    .col_port  = 'B',
    .col_bit_serial = 0,          /* PINB[0] */
    .col_load_clock_port = 'B',
    .col_load_clock_bit  = 2,     /* PORTB[2]: load-then-shift clock */
    .col_mode_port = 'B',
    .col_mode_bit  = 1,           /* PORTB[1]: HIGH=shift, LOW=load */
    .col_parallel = 0,            /* serial */

    .data_port = 'D',
    .data_mask = 0xFF,

    .strobe_port = 'B',
    .strobe_bit  = 6,
    .strobe_active_high = 1,

    .led_count = 3,
    .leds = {
        { .port = 'C', .bit = 4, .active_low = 1 },
        { .port = 'B', .bit = 5, .active_low = 0 },
        { .port = 'B', .bit = 4, .active_low = 0 },
    },

    .dip_row = 8,                 /* DIPs read as matrix row 8 */
    .dip_col_count = 8,

    .scan_tick_hz = 1000,
};

#endif
```

- [ ] **Step 2: Create `test/simavr/arch_io/asdf_simavr_io_familyB.h`**

```c
#ifndef ASDF_SIMAVR_IO_FAMILYB_H
#define ASDF_SIMAVR_IO_FAMILYB_H

/* Pin map for atmega640 / atmega1280 / atmega2560.
 * Source of truth: src/Arch/asdf_arch_atmega2560.h. */

#include "asdf_simavr_io_select.h"

static const asdf_io_map_t asdf_io_familyB = {
    .family_name      = "B",
    .cpu_frequency_hz = 16000000U,

    /* 16 rows split across two ports, active-LOW strobe. */
    .row_port  = 'J',             /* PORTJ[7:0] = rows 0..7 (LOROW) */
    .row_mask  = 0xFF,
    .row_shift = 0,
    .row_port_hi = 'A',           /* PORTA[7:0] = rows 8..15 (HIROW) */
    .row_active_low = 1,

    /* Parallel column read on PINC, active-LOW (firmware inverts). */
    .col_port  = 'C',
    .col_parallel = 1,
    .col_mask  = 0xFF,
    .col_active_low = 1,

    .data_port = 'H',
    .data_mask = 0xFF,

    .strobe_port = 'B',
    .strobe_bit  = 4,
    .strobe_active_high = 1,

    .led_count = 3,
    .leds = {
        { .port = 'D', .bit = 5, .active_low = 0 },
        { .port = 'D', .bit = 6, .active_low = 0 },
        { .port = 'D', .bit = 7, .active_low = 0 },
    },

    .dip_row = 8,
    .dip_col_count = 8,

    .scan_tick_hz = 1000,
};

#endif
```

- [ ] **Step 3: Create `test/simavr/arch_io/asdf_simavr_io_select.h`**

```c
#ifndef ASDF_SIMAVR_IO_SELECT_H
#define ASDF_SIMAVR_IO_SELECT_H

#include <stdint.h>
#include <string.h>

#define ASDF_IO_MAX_LEDS 4

typedef struct {
    char port;
    int  bit;
    int  active_low;
} asdf_io_led_t;

typedef struct {
    const char *family_name;
    uint32_t    cpu_frequency_hz;

    char row_port;
    uint8_t row_mask;
    int row_shift;
    char row_port_hi;             /* '\0' if unused (family A) */
    int row_active_low;

    char col_port;
    int  col_parallel;            /* 1 = parallel read, 0 = serial via shift reg */
    uint8_t col_mask;             /* only meaningful if col_parallel */
    int col_active_low;           /* only meaningful if col_parallel */
    int col_bit_serial;           /* only meaningful if !col_parallel */
    char col_load_clock_port;
    int  col_load_clock_bit;
    char col_mode_port;
    int  col_mode_bit;

    char data_port;
    uint8_t data_mask;

    char strobe_port;
    int  strobe_bit;
    int  strobe_active_high;

    int led_count;
    asdf_io_led_t leds[ASDF_IO_MAX_LEDS];

    int dip_row;
    int dip_col_count;

    int scan_tick_hz;
} asdf_io_map_t;

/* Return the map for a given AVR target name, or NULL if unsupported. */
static inline const asdf_io_map_t *asdf_io_pick(const char *target);

#endif
```

Then create `test/simavr/arch_io/asdf_simavr_io.c`:
```c
#include "asdf_simavr_io_familyA.h"
#include "asdf_simavr_io_familyB.h"

const asdf_io_map_t *asdf_io_pick(const char *target)
{
    if (!strcmp(target, "atmega328p") ||
        !strcmp(target, "atmega168p") ||
        !strcmp(target, "atmega88p")) return &asdf_io_familyA;
    if (!strcmp(target, "atmega640") ||
        !strcmp(target, "atmega1280") ||
        !strcmp(target, "atmega2560")) return &asdf_io_familyB;
    return 0;
}
```

Remove the `static inline` line from the header and replace it with:
```c
const asdf_io_map_t *asdf_io_pick(const char *target);
```

- [ ] **Step 4: Wire it into the CMakeLists.txt and call it from the runner**

Update `test/simavr/CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.19)

add_executable(asdf_simavr_runner
  asdf_simavr_runner.c
  arch_io/asdf_simavr_io.c
)
target_include_directories(asdf_simavr_runner PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/arch_io
)
target_compile_options(asdf_simavr_runner PRIVATE -Wall -Wextra -Wno-unused-parameter -std=c99)
target_link_libraries(asdf_simavr_runner PRIVATE simavr elf)
```

In `asdf_simavr_runner.c`, add `#include "asdf_simavr_io_select.h"` near the top and after `avr_init(cpu)`, add:
```c
    const asdf_io_map_t *io = asdf_io_pick(a.target);
    if (!io) { fprintf(stderr, "FAIL: no I/O map for %s\n", a.target); return 1; }
    cpu->frequency = io->cpu_frequency_hz;
    printf("OK: %s mapped to family %s (%u Hz)\n",
           a.target, io->family_name, (unsigned)io->cpu_frequency_hz);
```
(remove the earlier `printf` that only reported frequency).

- [ ] **Step 5: Build and verify the map is selected correctly**

Run:
```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make
for t in atmega328p atmega168p atmega640 atmega1280 atmega2560; do
  ./test/simavr/asdf_simavr_runner --target $t --keymap classic \
    --elf ../build-$t/src/asdf-v1.6.6-$t.elf
done
```
Expected: 5 lines, each printing the right family ("A" for 328p/168p, "B" for 640/1280/2560) and the right clock (8 MHz / 16 MHz).

- [ ] **Step 6: Commit**

```bash
cd ..
git add test/simavr/arch_io/ test/simavr/CMakeLists.txt test/simavr/asdf_simavr_runner.c
git commit -m "add per-family I/O surface tables for simavr harness

- arch_io/ holds the port:bit map for family A (328p/168p/88p) and
  family B (640/1280/2560), duplicating values from src/Arch/* on
  purpose so the harness stays decoupled from ASDF source.
- asdf_io_pick(target) selects the right map; runner uses it to set
  the simulated CPU frequency."
```

---

## Task 5: Output capture ring buffer

**Files:**
- Create: `test/simavr/harness/capture.c`, `capture.h`

A small fixed-size ring buffer of `(cycle_timestamp, byte)` records, appended from the strobe-edge notifier (Task 6) and drained by assertions (Task 8).

- [ ] **Step 1: Create `test/simavr/harness/capture.h`**

```c
#ifndef ASDF_SIM_CAPTURE_H
#define ASDF_SIM_CAPTURE_H

#include <stdint.h>
#include <stddef.h>

#define ASDF_CAP_RING_SIZE 64

typedef struct {
    uint64_t cycle;
    uint8_t  byte;
} asdf_cap_record_t;

void cap_init(void);
void cap_push(uint64_t cycle, uint8_t byte);
int  cap_pop(asdf_cap_record_t *out);   /* 1 if a record was returned, 0 if empty */
size_t cap_count(void);
void cap_clear(void);

#endif
```

- [ ] **Step 2: Create `test/simavr/harness/capture.c`**

```c
#include "capture.h"

static asdf_cap_record_t ring[ASDF_CAP_RING_SIZE];
static size_t head = 0;   /* next write */
static size_t tail = 0;   /* next read */
static size_t count = 0;

void cap_init(void) { head = tail = count = 0; }

void cap_push(uint64_t cycle, uint8_t byte)
{
    ring[head].cycle = cycle;
    ring[head].byte  = byte;
    head = (head + 1) % ASDF_CAP_RING_SIZE;
    if (count < ASDF_CAP_RING_SIZE) count++;
    else tail = (tail + 1) % ASDF_CAP_RING_SIZE;   /* drop oldest on overflow */
}

int cap_pop(asdf_cap_record_t *out)
{
    if (count == 0) return 0;
    *out = ring[tail];
    tail = (tail + 1) % ASDF_CAP_RING_SIZE;
    count--;
    return 1;
}

size_t cap_count(void) { return count; }
void cap_clear(void) { head = tail = count = 0; }
```

- [ ] **Step 3: Write a unit test for the ring buffer**

Create `test/simavr/harness/test_capture.c`:
```c
#include <assert.h>
#include <stdio.h>
#include "capture.h"

int main(void)
{
    cap_init();
    assert(cap_count() == 0);

    cap_push(100, 'a');
    cap_push(200, 'b');
    assert(cap_count() == 2);

    asdf_cap_record_t r;
    assert(cap_pop(&r) == 1 && r.cycle == 100 && r.byte == 'a');
    assert(cap_pop(&r) == 1 && r.cycle == 200 && r.byte == 'b');
    assert(cap_pop(&r) == 0);

    /* overflow: oldest dropped */
    for (int i = 0; i < ASDF_CAP_RING_SIZE + 5; i++) cap_push(i, i & 0xFF);
    assert(cap_count() == ASDF_CAP_RING_SIZE);
    assert(cap_pop(&r) == 1 && r.cycle == 5);   /* first 5 were dropped */

    printf("capture: OK\n");
    return 0;
}
```

- [ ] **Step 4: Wire the unit test into CMakeLists.txt as a ctest case**

Append to `test/simavr/CMakeLists.txt`:
```cmake
enable_testing()

add_executable(asdf_sim_test_capture
  harness/capture.c
  harness/test_capture.c
)
target_include_directories(asdf_sim_test_capture PRIVATE harness)
target_compile_options(asdf_sim_test_capture PRIVATE -Wall -Wextra -std=c99)
add_test(NAME unit_capture COMMAND asdf_sim_test_capture)
```

Also add the capture sources to the main runner so future tasks can use it:
```cmake
add_executable(asdf_simavr_runner
  asdf_simavr_runner.c
  arch_io/asdf_simavr_io.c
  harness/capture.c
)
target_include_directories(asdf_simavr_runner PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/arch_io
  ${CMAKE_CURRENT_SOURCE_DIR}/harness
)
```
(replace the old `add_executable(asdf_simavr_runner ...)` block).

- [ ] **Step 5: Run the test and verify it passes**

Run:
```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make && ctest --output-on-failure
```
Expected: `1/1 Test #1: unit_capture .... Passed`.

- [ ] **Step 6: Commit**

```bash
cd ..
git add test/simavr/harness/capture.c test/simavr/harness/capture.h test/simavr/harness/test_capture.c test/simavr/CMakeLists.txt
git commit -m "add output capture ring buffer + unit test

- fixed 64-record ring; drops oldest on overflow.
- cap_push called from strobe-edge notifier (next task); cap_pop drained
  by SIM_EXPECT_BYTE_WITHIN assertions (later task)."
```

---

## Task 6: Sim init + strobe-edge notifier wiring

**Files:**
- Create: `test/simavr/harness/sim.c`, `sim.h`
- Create: `test/simavr/harness/io.c`, `io.h`
- Modify: `test/simavr/asdf_simavr_runner.c`, `test/simavr/CMakeLists.txt`

- [ ] **Step 1: Create `test/simavr/harness/sim.h`**

```c
#ifndef ASDF_SIM_H
#define ASDF_SIM_H

#include <simavr/sim_avr.h>
#include "asdf_simavr_io_select.h"

avr_t *sim_load(const char *target, const char *elf_path,
                const asdf_io_map_t *io);
void   sim_free(avr_t *cpu);

#endif
```

- [ ] **Step 2: Create `test/simavr/harness/sim.c`**

```c
#include <stdio.h>
#include <stdlib.h>
#include <simavr/sim_elf.h>

#include "sim.h"

avr_t *sim_load(const char *target, const char *elf_path,
                const asdf_io_map_t *io)
{
    elf_firmware_t fw = {{0}};
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
    /* libsimavr has no public destructor for avr_t in 1.6;
     * relying on process exit for cleanup is intentional. */
    (void)cpu;
}
```

- [ ] **Step 3: Create `test/simavr/harness/io.h`**

```c
#ifndef ASDF_SIM_IO_H
#define ASDF_SIM_IO_H

#include <simavr/sim_avr.h>
#include "asdf_simavr_io_select.h"

/* Wire up the harness's strobe-edge capture to the given CPU/map.
 * After this, every rising strobe edge appends a record to cap_push(). */
void io_wire_output(avr_t *cpu, const asdf_io_map_t *io);

#endif
```

- [ ] **Step 4: Create `test/simavr/harness/io.c`**

```c
#include <simavr/avr_ioport.h>

#include "io.h"
#include "capture.h"

static avr_t *g_cpu;
static const asdf_io_map_t *g_io;
static uint8_t g_data_port_value;    /* latched on every write to data port */

static void on_data_port(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq; (void)param;
    g_data_port_value = (uint8_t)(value & g_io->data_mask);
}

static void on_strobe(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq; (void)param;
    int active = g_io->strobe_active_high ? (value != 0) : (value == 0);
    static int last_active = 0;
    if (active && !last_active) {
        cap_push(g_cpu->cycle, g_data_port_value);
    }
    last_active = active;
}

void io_wire_output(avr_t *cpu, const asdf_io_map_t *io)
{
    g_cpu = cpu;
    g_io  = io;
    g_data_port_value = 0;

    /* Hook every bit of the data port so any write updates our latch.
     * AVR_IOCTL_IOPORT_GETIRQ + IOPORT_IRQ_REG_PORT fires on PORTx writes. */
    avr_irq_t *port_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->data_port), IOPORT_IRQ_REG_PORT);
    avr_irq_register_notify(port_irq, on_data_port, 0);

    /* Hook the strobe bit; AVR_IOCTL_IOPORT_GETIRQ + bit number fires on
     * any change to that bit. */
    avr_irq_t *strobe_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->strobe_port), io->strobe_bit);
    avr_irq_register_notify(strobe_irq, on_strobe, 0);
}
```

- [ ] **Step 5: Update the runner to use sim + io and run the firmware for 100 ms**

Replace the body of `main` in `asdf_simavr_runner.c` (everything after `parse_args` to the final `return 0;`) with:
```c
    const asdf_io_map_t *io = asdf_io_pick(a.target);
    if (!io) { fprintf(stderr, "FAIL: no I/O map for %s\n", a.target); return 1; }

    avr_t *cpu = sim_load(a.target, a.elf_path, io);
    if (!cpu) return 1;

    cap_init();
    io_wire_output(cpu, io);

    /* Run for 100 simulated milliseconds. No matrix inputs driven yet,
     * so we should see no output bytes. This proves the sim runs and
     * the notifier wiring is sane. */
    uint64_t target_cycle = (uint64_t)(cpu->frequency / 10);   /* 100 ms */
    while (cpu->cycle < target_cycle) {
        int state = avr_run(cpu);
        if (state == cpu_Done || state == cpu_Crashed) {
            fprintf(stderr, "FAIL: cpu halted at cycle %" PRIu64 " (state=%d)\n",
                    (uint64_t)cpu->cycle, state);
            return 1;
        }
    }

    printf("OK: %s/%s ran %" PRIu64 " cycles, captured %zu bytes\n",
           a.target, a.keymap, (uint64_t)cpu->cycle, cap_count());
    return 0;
```

Add at the top of `asdf_simavr_runner.c`:
```c
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "sim.h"
#include "io.h"
#include "capture.h"
```

- [ ] **Step 6: Add the new sources to the CMakeLists.txt runner target**

```cmake
add_executable(asdf_simavr_runner
  asdf_simavr_runner.c
  arch_io/asdf_simavr_io.c
  harness/capture.c
  harness/sim.c
  harness/io.c
)
```

- [ ] **Step 7: Build and run; verify the firmware boots without producing output**

```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make
./test/simavr/asdf_simavr_runner --target atmega2560 --keymap classic \
  --elf ../build-atmega2560/src/asdf-v1.6.6-atmega2560.elf
```
Expected: `OK: atmega2560/classic ran 1600000 cycles, captured 0 bytes` (1.6M cycles = 100 ms at 16 MHz; 0 bytes because we haven't pressed any keys).

If the cpu crashes or halts, do not paper over it — the I/O map values may be wrong. Use `--vcd` (added in Task 9) to inspect; but first re-read the arch source headers and compare port/bit values.

- [ ] **Step 8: Commit**

```bash
cd ..
git add test/simavr/harness/sim.c test/simavr/harness/sim.h test/simavr/harness/io.c test/simavr/harness/io.h test/simavr/asdf_simavr_runner.c test/simavr/CMakeLists.txt
git commit -m "boot the firmware in simavr and latch strobe-edge output

- sim.c: ELF load + MCU init + frequency override per family.
- io.c: data-port write latch + rising-strobe notifier appends to
  capture buffer.
- runner now runs the firmware for 100 ms of simulated time; should
  produce zero captured bytes because no matrix input is being driven."
```

---

## Task 7: Matrix column + DIP switch injection

**Files:**
- Modify: `test/simavr/harness/io.c`, `io.h`

The firmware strobes rows in turn and reads columns. The harness needs to (a) detect when each row is being strobed, and (b) present the right column pattern for the matrix state we want.

For family A, rows are PORTC[3:0] (a 4-bit row index), columns are serially shifted out on PINB[0] under the firmware's clock and mode-select control. For family B, rows are PORTJ[7:0] + PORTA[7:0] (active-low one-hot for the currently-scanned row), columns are read in parallel from PINC.

We support family B fully (used by the SOL-20 case the user mentioned). Family A's serial column read is implemented by tracking the load/shift clock to feed bits one at a time.

- [ ] **Step 1: Extend `io.h`**

Add after the existing function declaration:
```c
/* Wire up matrix input injection. After this, the firmware's row strobes
 * will trigger the harness to drive the column input(s) according to the
 * currently-set matrix state. */
void io_wire_input(avr_t *cpu, const asdf_io_map_t *io);

/* Set/clear a key in the simulated matrix.
 * row 0..ASDF_NUM_ROWS-1 = normal keys; row 8 = DIP switch slot. */
void matrix_press(int row, int col);
void matrix_release(int row, int col);
void matrix_clear(void);

/* Convenience: set all 8 DIP switch bits to the given value, replacing
 * any previous DIP state. */
void set_dip(uint8_t value);
```

- [ ] **Step 2: Extend `io.c` with matrix state + family-B row notifiers**

Add at top:
```c
#define MATRIX_MAX_ROWS 16
#define MATRIX_MAX_COLS 8
static uint8_t matrix[MATRIX_MAX_ROWS];   /* matrix[row] = bitmap of pressed cols */
```

Add the public mutation functions:
```c
void matrix_press(int row, int col)
{
    if (row < 0 || row >= MATRIX_MAX_ROWS) return;
    if (col < 0 || col >= MATRIX_MAX_COLS) return;
    matrix[row] |= (1u << col);
}
void matrix_release(int row, int col)
{
    if (row < 0 || row >= MATRIX_MAX_ROWS) return;
    if (col < 0 || col >= MATRIX_MAX_COLS) return;
    matrix[row] &= ~(1u << col);
}
void matrix_clear(void) { memset(matrix, 0, sizeof matrix); }
void set_dip(uint8_t value) { matrix[8] = value; }
```

Add the family-B row-strobe notifier. Family B drives a one-hot row pattern on PORTJ (rows 0-7) and PORTA (rows 8-15), active-LOW. When we see a write to PORTJ or PORTA, work out which row is being strobed, look up the column pattern for that row, and present it on PINC (active-LOW, so we invert).

```c
#include <string.h>

static int g_active_row = -1;   /* row currently being strobed, or -1 */

static void present_columns_familyB(void)
{
    if (!g_io->col_parallel) return;
    if (g_active_row < 0) return;

    uint8_t cols = matrix[g_active_row];
    uint8_t pin_value = g_io->col_active_low ? (uint8_t)~cols : cols;

    /* Drive every bit of the column port. Use IOPORT_IRQ_PIN_ALL to
     * write the full byte in one call. */
    avr_irq_t *pin_irq = avr_io_getirq(g_cpu,
        AVR_IOCTL_IOPORT_GETIRQ(g_io->col_port), IOPORT_IRQ_PIN_ALL);
    avr_raise_irq(pin_irq, pin_value);
}

static void on_row_port_familyB(struct avr_irq_t *irq, uint32_t value, void *param)
{
    (void)irq;
    int hi_port = (int)(intptr_t)param;        /* 1 if PORTA (hi rows), 0 if PORTJ (lo rows) */
    uint8_t v = (uint8_t)value;
    if (g_io->row_active_low) v = (uint8_t)~v;
    if (v == 0) { g_active_row = -1; return; }

    /* one-hot; pick the lowest set bit */
    int bit = 0;
    while ((v & 1) == 0) { v >>= 1; bit++; }
    g_active_row = hi_port ? (8 + bit) : bit;
    present_columns_familyB();
}
```

In `io_wire_input`, dispatch on family:
```c
void io_wire_input(avr_t *cpu, const asdf_io_map_t *io)
{
    g_cpu = cpu;
    g_io  = io;
    matrix_clear();
    g_active_row = -1;

    if (io->col_parallel) {
        /* Family B */
        avr_irq_t *lo = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->row_port), IOPORT_IRQ_REG_PORT);
        avr_irq_register_notify(lo, on_row_port_familyB, (void*)(intptr_t)0);

        if (io->row_port_hi) {
            avr_irq_t *hi = avr_io_getirq(cpu,
                AVR_IOCTL_IOPORT_GETIRQ(io->row_port_hi), IOPORT_IRQ_REG_PORT);
            avr_irq_register_notify(hi, on_row_port_familyB, (void*)(intptr_t)1);
        }
    } else {
        /* Family A serial-column injection — implemented in Task 12 if
         * needed. For now, family A tests skip matrix-input assertions
         * and only verify boot + scan-loop liveness. */
    }
}
```

Note: `g_cpu`, `g_io` are already defined as `static` file-scope variables from Task 6. Make sure not to redeclare them.

- [ ] **Step 3: Call `io_wire_input` from the runner**

In `asdf_simavr_runner.c`, after `io_wire_output(cpu, io);` add:
```c
    io_wire_input(cpu, io);
```

- [ ] **Step 4: Build and verify nothing regressed**

```bash
cd build-simavr-test && make && ./test/simavr/asdf_simavr_runner \
  --target atmega2560 --keymap classic \
  --elf ../build-atmega2560/src/asdf-v1.6.6-atmega2560.elf
```
Expected: same as Task 6 — `OK: ... captured 0 bytes`. The matrix state is all zero, so even though rows are now being strobed, no keys are "pressed."

- [ ] **Step 5: Commit**

```bash
cd ..
git add test/simavr/harness/io.c test/simavr/harness/io.h test/simavr/asdf_simavr_runner.c
git commit -m "inject matrix and DIP-switch state into the simulated firmware

- family B (640/1280/2560): row notifier on PORTJ + PORTA detects the
  one-hot active-LOW strobe, looks up the corresponding column bitmap,
  and drives PINC in parallel (inverted to match active-LOW columns).
- matrix_press/release/clear and set_dip helpers manage the matrix
  state the harness presents to the firmware.
- family A serial-column injection is intentionally deferred."
```

---

## Task 8: Stepping primitive + assertion API

**Files:**
- Create: `test/simavr/harness/run.c`, `run.h`
- Create: `test/simavr/harness/assert.c`, `assert.h`

- [ ] **Step 1: Create `test/simavr/harness/run.h`**

```c
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
```

- [ ] **Step 2: Create `test/simavr/harness/run.c`**

```c
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
```

- [ ] **Step 3: Create `test/simavr/harness/assert.h`**

```c
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
```

- [ ] **Step 4: Create `test/simavr/harness/assert.c`**

```c
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
```

- [ ] **Step 5: Add the new sources to CMakeLists.txt runner target**

```cmake
add_executable(asdf_simavr_runner
  asdf_simavr_runner.c
  arch_io/asdf_simavr_io.c
  harness/capture.c
  harness/sim.c
  harness/io.c
  harness/run.c
  harness/assert.c
)
```

- [ ] **Step 6: Build to confirm no warnings**

```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make
```
Expected: clean build. No runtime test yet — assertions are exercised by the first keymap case in Task 10.

- [ ] **Step 7: Commit**

```bash
cd ..
git add test/simavr/harness/run.c test/simavr/harness/run.h test/simavr/harness/assert.c test/simavr/harness/assert.h test/simavr/CMakeLists.txt
git commit -m "add sim stepping primitive and byte-expectation assertion

- sim_run_until / sim_run_for advance the AVR with bounded cycle budget.
- sim_expect_byte_within drains the next captured byte and compares;
  failure messages include sim-cycle, expected vs. actual, both as hex
  and printable ASCII where applicable."
```

---

## Task 9: VCD dump support

**Files:**
- Create: `test/simavr/harness/vcd.c`, `vcd.h`
- Modify: `test/simavr/asdf_simavr_runner.c`, `test/simavr/CMakeLists.txt`

- [ ] **Step 1: Create `test/simavr/harness/vcd.h`**

```c
#ifndef ASDF_SIM_VCD_H
#define ASDF_SIM_VCD_H

#include <simavr/sim_avr.h>
#include "asdf_simavr_io_select.h"

/* Begin VCD recording of all watched pins. Records data-port byte,
 * strobe, LEDs, and the first row port. Returns 0 on success. */
int vcd_begin(avr_t *cpu, const asdf_io_map_t *io, const char *path);
void vcd_end(void);

#endif
```

- [ ] **Step 2: Create `test/simavr/harness/vcd.c`**

```c
#include <stdio.h>
#include <simavr/avr_ioport.h>
#include <simavr/sim_vcd_file.h>

#include "vcd.h"

static avr_vcd_t g_vcd;
static int g_vcd_active = 0;

int vcd_begin(avr_t *cpu, const asdf_io_map_t *io, const char *path)
{
    if (avr_vcd_init(cpu, path, &g_vcd, 100 /* sample every 100us */) != 0) {
        fprintf(stderr, "WARN: could not init VCD %s\n", path);
        return 1;
    }

    /* Data port: 8 bits */
    avr_irq_t *port_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->data_port), IOPORT_IRQ_REG_PORT);
    avr_vcd_add_signal(&g_vcd, port_irq, 8, "data");

    /* Strobe: 1 bit */
    avr_irq_t *strobe_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->strobe_port), io->strobe_bit);
    avr_vcd_add_signal(&g_vcd, strobe_irq, 1, "strobe");

    /* LEDs */
    for (int i = 0; i < io->led_count; i++) {
        avr_irq_t *led = avr_io_getirq(cpu,
            AVR_IOCTL_IOPORT_GETIRQ(io->leds[i].port), io->leds[i].bit);
        char name[8]; snprintf(name, sizeof name, "led%d", i + 1);
        avr_vcd_add_signal(&g_vcd, led, 1, name);
    }

    /* Row port (lo for family B, the only row port for family A) */
    avr_irq_t *row_irq = avr_io_getirq(cpu,
        AVR_IOCTL_IOPORT_GETIRQ(io->row_port), IOPORT_IRQ_REG_PORT);
    avr_vcd_add_signal(&g_vcd, row_irq, 8, "row_lo");

    avr_vcd_start(&g_vcd);
    g_vcd_active = 1;
    return 0;
}

void vcd_end(void)
{
    if (g_vcd_active) {
        avr_vcd_stop(&g_vcd);
        g_vcd_active = 0;
    }
}
```

- [ ] **Step 3: Wire `--vcd` in the runner**

In `asdf_simavr_runner.c`, after `io_wire_input(cpu, io);` add:
```c
    if (a.vcd_path) {
        if (vcd_begin(cpu, io, a.vcd_path) != 0)
            fprintf(stderr, "WARN: VCD recording disabled\n");
    }
```
And before the final `return 0;`:
```c
    vcd_end();
```
Add `#include "vcd.h"` at the top.

- [ ] **Step 4: Add to CMakeLists.txt runner target**

Append `harness/vcd.c` to the runner's source list.

- [ ] **Step 5: Build and verify VCD is produced**

```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make
./test/simavr/asdf_simavr_runner --target atmega2560 --keymap classic \
  --elf ../build-atmega2560/src/asdf-v1.6.6-atmega2560.elf \
  --vcd /tmp/run.vcd
test -s /tmp/run.vcd && head -20 /tmp/run.vcd
```
Expected: `/tmp/run.vcd` exists, is nonzero, and starts with `$version` / `$timescale` / `$scope` lines. If `gtkwave` is installed, `gtkwave /tmp/run.vcd` should open it and show the watched signals.

- [ ] **Step 6: Commit**

```bash
cd ..
git add test/simavr/harness/vcd.c test/simavr/harness/vcd.h test/simavr/asdf_simavr_runner.c test/simavr/CMakeLists.txt
git commit -m "record optional VCD trace of watched pins

- --vcd PATH triggers libsimavr avr_vcd_init/start/stop with the data
  port, strobe, LEDs, and lo row port wired as signals.
- on test failure in CI, this trace is uploaded as an artifact for
  offline inspection in gtkwave."
```

---

## Task 10: Test types + first keymap test (classic, atmega2560)

**Files:**
- Create: `test/simavr/harness/test_types.h`
- Create: `test/simavr/keymap_data/asdf_simavr_test_classic.h`
- Modify: `test/simavr/asdf_simavr_runner.c`, `test/simavr/CMakeLists.txt`

This is where we go from "harness runs" to "harness asserts something concrete." We do it for ONE (target, keymap) pair only — classic on atmega2560 — then roll out in Tasks 11-12.

- [ ] **Step 1: Create `test/simavr/harness/test_types.h`**

```c
#ifndef ASDF_SIM_TEST_TYPES_H
#define ASDF_SIM_TEST_TYPES_H

#include <stdint.h>

#define SIM_MOD_NONE  0
#define SIM_MOD_SHIFT 1
#define SIM_MOD_CTRL  2

typedef struct {
    int row;
    int col;
} sim_coord_t;

typedef struct {
    int      row;
    int      col;
    uint32_t hold_cycles;        /* how long to hold the key down before releasing */
    uint8_t  expected;           /* expected output byte */
    int      with_modifier;      /* SIM_MOD_NONE | SIM_MOD_SHIFT | SIM_MOD_CTRL */
} sim_event_t;

typedef struct {
    const char        *name;
    uint8_t            dip_value;
    uint32_t           boot_scan_ticks;   /* simulated ms to wait before driving input */
    sim_coord_t        modifier_shift;    /* matrix coord of SHIFT for this keymap */
    sim_coord_t        modifier_ctrl;     /* matrix coord of CTRL for this keymap */
    const sim_event_t *events;
    int                num_events;
} sim_keymap_test_t;

#endif
```

- [ ] **Step 2: Read the classic keymap source to choose three concrete events**

This step is a brief research step performed by the implementer; do not write code in this step. Read these files:
- `src/Keymaps/asdf_keymap_classic.c`
- `src/Keymaps/asdf_keymap_classic.h`

Identify:
1. The matrix coordinate of one alphabetic key in the plain-modifier table — e.g., the cell that produces `'a'`. ASCII codes appear as character literals in the matrix tables. Record `(row, col)`.
2. The matrix coordinate of the SHIFT key. Look for the key whose action selects the SHIFT modifier (commonly `ACTION_SHIFT` or similar) — record its `(row, col)` for `modifier_shift`.
3. The matrix coordinate of one symbol/punctuation key in plain state, e.g. `'\r'` (Enter) or `' '` (Space). Record `(row, col)`.
4. The DIP value for classic. From `keymap_list.cmake`, `classic = 0`.

If a coordinate can't be confidently identified from the source, leave a comment in the header explaining which coordinate is uncertain, set it to a best-guess, and the runtime failure in Step 5 will narrow it down via VCD inspection.

- [ ] **Step 3: Create `test/simavr/keymap_data/asdf_simavr_test_classic.h`**

Using the coordinates identified in Step 2 (the values below are illustrative; the implementer fills in actuals):

```c
#ifndef ASDF_SIMAVR_TEST_CLASSIC_H
#define ASDF_SIMAVR_TEST_CLASSIC_H

#include "test_types.h"

/* Coordinates derived from src/Keymaps/asdf_keymap_classic.c — see
 * Step 2 of Task 10 in the implementation plan for the recipe. */
static const sim_event_t classic_events[] = {
    { .row = ROW_A,  .col = COL_A,  .hold_cycles = 200000, .expected = 'a',  .with_modifier = SIM_MOD_NONE  },
    { .row = ROW_A,  .col = COL_A,  .hold_cycles = 200000, .expected = 'A',  .with_modifier = SIM_MOD_SHIFT },
    { .row = ROW_CR, .col = COL_CR, .hold_cycles = 200000, .expected = '\r', .with_modifier = SIM_MOD_NONE  },
};

static const sim_keymap_test_t classic_test = {
    .name            = "classic",
    .dip_value       = 0,
    .boot_scan_ticks = 100,                            /* 100 ms */
    .modifier_shift  = { .row = ROW_SHIFT, .col = COL_SHIFT },
    .modifier_ctrl   = { .row = ROW_CTRL,  .col = COL_CTRL  },
    .events          = classic_events,
    .num_events      = sizeof(classic_events) / sizeof(classic_events[0]),
};

#endif
```

Replace the `ROW_*`/`COL_*` placeholders with the actual integers from Step 2. They are direct integers (e.g., `.row = 2, .col = 3`), not `#define` symbols — the header is self-contained.

- [ ] **Step 4: Update the runner to dispatch by keymap and run the events**

In `asdf_simavr_runner.c`:

Add includes:
```c
#include "test_types.h"
#include "keymap_data/asdf_simavr_test_classic.h"
```

Add a dispatch helper above `main`:
```c
static const sim_keymap_test_t *pick_keymap(const char *name)
{
    if (!strcmp(name, "classic")) return &classic_test;
    /* Other keymaps added by later tasks. */
    return 0;
}
```

Replace the "Run for 100 simulated milliseconds" loop and the `printf("OK: ...")` line at the end of `main` with:
```c
    const sim_keymap_test_t *km = pick_keymap(a.keymap);
    if (!km) { fprintf(stderr, "FAIL: no test data for keymap %s\n", a.keymap); return 1; }

    set_dip(km->dip_value);

    /* Let the firmware boot and run a few scan cycles to settle. */
    if (sim_wait_ms(cpu, km->boot_scan_ticks, io->cpu_frequency_hz) < 0) {
        fprintf(stderr, "FAIL: cpu halted during boot\n");
        return 1;
    }

    /* Drain anything emitted during boot. */
    cap_clear();

    for (int i = 0; i < km->num_events; i++) {
        const sim_event_t *e = &km->events[i];
        char what[64];
        snprintf(what, sizeof what, "%s/event[%d]@(%d,%d)", a.keymap, i, e->row, e->col);

        if (e->with_modifier == SIM_MOD_SHIFT)
            matrix_press(km->modifier_shift.row, km->modifier_shift.col);
        else if (e->with_modifier == SIM_MOD_CTRL)
            matrix_press(km->modifier_ctrl.row, km->modifier_ctrl.col);

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

        /* Wait for debounce before the next event. */
        sim_wait_ms(cpu, 50, io->cpu_frequency_hz);
        cap_clear();
    }

    vcd_end();
    printf("OK: %s/%s passed %d events at cycle %" PRIu64 "\n",
           a.target, a.keymap, km->num_events, (uint64_t)cpu->cycle);
    return 0;
```

- [ ] **Step 5: Add the single ctest case**

Append to `test/simavr/CMakeLists.txt`:
```cmake
add_test(
  NAME simavr_atmega2560_classic
  COMMAND asdf_simavr_runner
          --target atmega2560
          --keymap classic
          --elf ${CMAKE_SOURCE_DIR}/build-atmega2560/src/asdf-v1.6.6-atmega2560.elf
          --vcd ${CMAKE_CURRENT_BINARY_DIR}/simavr_atmega2560_classic.vcd
)
set_tests_properties(simavr_atmega2560_classic PROPERTIES TIMEOUT 10)
```

- [ ] **Step 6: Run the test**

```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make && ctest --output-on-failure
```
Expected (success case): `2/2 Test #2: simavr_atmega2560_classic .... Passed` (Test #1 is `unit_capture` from Task 5).

If it fails: open `build-simavr-test/test/simavr/simavr_atmega2560_classic.vcd` in gtkwave. The most common cause is wrong matrix coordinates picked in Step 2; revisit those by reading the keymap source again. The second most common cause is the DIP value not selecting the keymap as expected — verify against `keymap_list.cmake`.

- [ ] **Step 7: Commit**

```bash
cd ..
git add test/simavr/harness/test_types.h test/simavr/keymap_data/ test/simavr/asdf_simavr_runner.c test/simavr/CMakeLists.txt
git commit -m "add first integration test: classic keymap on atmega2560

- test_types.h: sim_event_t / sim_keymap_test_t structs.
- keymap_data/asdf_simavr_test_classic.h: three events (plain letter,
  shifted letter, carriage return) chosen by reading classic's matrix.
- runner now dispatches by --keymap, drives the events with proper
  press/release + modifier handling, and asserts via
  sim_expect_byte_within.
- one ctest case wired: simavr_atmega2560_classic."
```

---

## Task 11: Expand classic to all 5 targets

**Files:**
- Modify: `test/simavr/CMakeLists.txt`

- [ ] **Step 1: Replace the single hand-rolled `add_test` with a loop over targets**

Replace the `add_test(NAME simavr_atmega2560_classic ...)` block from Task 10 with:
```cmake
set(SIMAVR_TARGETS atmega328p atmega168p atmega640 atmega1280 atmega2560)
set(SIMAVR_KEYMAPS classic)   # full list filled in by Task 12

foreach(tgt ${SIMAVR_TARGETS})
  foreach(km ${SIMAVR_KEYMAPS})
    set(elf_path ${CMAKE_SOURCE_DIR}/build-${tgt}/src/asdf-v1.6.6-${tgt}.elf)
    add_test(
      NAME simavr_${tgt}_${km}
      COMMAND asdf_simavr_runner
              --target ${tgt}
              --keymap ${km}
              --elf ${elf_path}
              --vcd ${CMAKE_CURRENT_BINARY_DIR}/simavr_${tgt}_${km}.vcd
    )
    set_tests_properties(simavr_${tgt}_${km} PROPERTIES TIMEOUT 10)
  endforeach()
endforeach()
```

- [ ] **Step 2: Run all 5 classic cases**

```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make && ctest --output-on-failure
```
Expected: `6/6 tests passed` (`unit_capture` + 5 simavr_* cases).

Family A targets (atmega328p, atmega168p) will likely **fail** here unless the harness has family-A matrix-input support, because their column injection was deferred in Task 7. Treat that failure as expected for now: if family A cases fail and family B cases pass, move to Step 3. If family B cases fail too, fix before continuing.

- [ ] **Step 3: Decide family-A path**

Choose one:

(a) **Implement family-A serial column injection now.** Read `src/Arch/asdf_arch_atmega328p.c` for the shift-register clock/load sequence (`asdf_arch_read_row` and friends). In `harness/io.c`, add notifiers on `PORTB[2]` (load/shift clock) and `PORTB[1]` (mode select) that track which of the 8 bits the firmware is currently expecting on `PINB[0]`, and present that bit via `avr_raise_irq`. Estimated effort: 1-2 hours.

(b) **Mark family-A cases as expected-skip for now** by guarding them in CMake:
```cmake
foreach(tgt ${SIMAVR_TARGETS})
  foreach(km ${SIMAVR_KEYMAPS})
    set(elf_path ${CMAKE_SOURCE_DIR}/build-${tgt}/src/asdf-v1.6.6-${tgt}.elf)
    if(${tgt} STREQUAL "atmega328p" OR ${tgt} STREQUAL "atmega168p")
      # Family A serial column injection not implemented yet — boot-only smoke.
      add_test(
        NAME simavr_${tgt}_${km}
        COMMAND asdf_simavr_runner
                --target ${tgt} --keymap ${km} --elf ${elf_path}
                --boot-only
                --vcd ${CMAKE_CURRENT_BINARY_DIR}/simavr_${tgt}_${km}.vcd
      )
    else()
      add_test(NAME simavr_${tgt}_${km} ... )   # as above
    endif()
    set_tests_properties(simavr_${tgt}_${km} PROPERTIES TIMEOUT 10)
  endforeach()
endforeach()
```
And add `--boot-only` to the runner: when set, it boots, waits 200 ms, and asserts the cpu is still running (no event injection). This still catches "the firmware doesn't boot on this chip" regressions.

**Recommended: (a)** for the SOL-20-bug-class coverage the user actually wants. Time-box at 2 hours; if blocked, fall back to (b).

- [ ] **Step 4: Verify all 5 cases pass (or 3 + 2 boot-only if (b) was chosen)**

```bash
ctest --output-on-failure
```
Expected: all green.

- [ ] **Step 5: Commit**

```bash
cd ..
git add test/simavr/CMakeLists.txt test/simavr/harness/io.c test/simavr/harness/io.h test/simavr/asdf_simavr_runner.c
git commit -m "enumerate classic test across all 5 AVR targets

- generated add_test loop over (target, keymap); currently only classic
  is in the keymap list. Other keymaps follow in next task.
- family A serial-column injection [implemented | boot-only fallback]
  — see plan task 11 step 3."
```
(Choose the bracketed phrase that matches the path taken.)

---

## Task 12: Add remaining 5 keymaps

**Files:**
- Create: `test/simavr/keymap_data/asdf_simavr_test_classic_caps.h`
- Create: `test/simavr/keymap_data/asdf_simavr_test_apple2.h`
- Create: `test/simavr/keymap_data/asdf_simavr_test_apple2_caps.h`
- Create: `test/simavr/keymap_data/asdf_simavr_test_sol.h`
- Create: `test/simavr/keymap_data/asdf_simavr_test_ace1000.h`
- Modify: `test/simavr/asdf_simavr_runner.c`, `test/simavr/CMakeLists.txt`

Per keymap, repeat what Task 10 did for classic. The recipe is the same; only the inputs change.

- [ ] **Step 1: For each remaining keymap, create its test header**

For each `<keymap>` in {`classic_caps`, `apple2`, `apple2_caps`, `sol`, `ace1000`}:

1. Read `src/Keymaps/asdf_keymap_<keymap>.c` and `.h`.
2. Identify the matrix coordinate of: one plain alphabetic key, one shifted key, one symbol/control key. Identify SHIFT (and CTRL if present) coordinates for the keymap.
3. Look up the DIP value from `keymap_list.cmake`:
   - `classic_caps` → 1, `apple2` → 2, `apple2_caps` → 3, `sol` → 4, `ace1000` → 5.
4. Create `test/simavr/keymap_data/asdf_simavr_test_<keymap>.h` modeled exactly on `asdf_simavr_test_classic.h` (Task 10 Step 3), with the struct named `<keymap>_test` and the events array named `<keymap>_events`.

For the SOL-20 case specifically: pick at least one event that exercises the code path the recent bug-fix repaired. If the implementer doesn't know which path that was, look at the most recent commits touching `src/Keymaps/asdf_keymap_sol.*` for guidance (`git log -p src/Keymaps/asdf_keymap_sol.*`).

- [ ] **Step 2: Update the runner's dispatch**

In `asdf_simavr_runner.c`, replace `pick_keymap` with:
```c
#include "keymap_data/asdf_simavr_test_classic.h"
#include "keymap_data/asdf_simavr_test_classic_caps.h"
#include "keymap_data/asdf_simavr_test_apple2.h"
#include "keymap_data/asdf_simavr_test_apple2_caps.h"
#include "keymap_data/asdf_simavr_test_sol.h"
#include "keymap_data/asdf_simavr_test_ace1000.h"

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
```

- [ ] **Step 3: Expand the CMakeLists.txt keymap list**

```cmake
set(SIMAVR_KEYMAPS classic classic_caps apple2 apple2_caps sol ace1000)
```

- [ ] **Step 4: Run the full matrix**

```bash
cd build-simavr-test && cmake .. -DARCH=simavr_test && make && ctest --output-on-failure
```
Expected: `31/31 tests passed` (`unit_capture` + 30 simavr_* cases). If any are red, inspect the per-case VCD (`simavr_<target>_<keymap>.vcd`) and revisit the coordinates in the corresponding header.

- [ ] **Step 5: Commit**

```bash
cd ..
git add test/simavr/keymap_data/ test/simavr/asdf_simavr_runner.c test/simavr/CMakeLists.txt
git commit -m "add per-keymap integration tests for all 6 keymaps

- one .h per keymap with three event records: plain letter, shifted
  letter, and one symbol/control key.
- runner dispatches by --keymap; full ctest matrix is now 5 targets
  x 6 keymaps = 30 cases."
```

---

## Task 13: `make-targets.sh -t simavr_test` integration

**Files:**
- Modify: `make-targets.sh`

- [ ] **Step 1: Add `simavr_test` to the valid-targets list**

After the existing `add_valid_target atmega640` line, add:
```bash
add_valid_target simavr_test
```

- [ ] **Step 2: Add a pre-build check helper**

Read the script to find the function that handles per-target build (`build_arch`). Add a helper above it:

```bash
preflight_simavr_test() {
    local missing=0
    for t in atmega328p atmega168p atmega640 atmega1280 atmega2560; do
        local elf="build-$t/src/asdf-v1.6.6-$t.elf"
        if [[ ! -f $elf ]]; then
            echo "ERROR: missing $elf"
            missing=1
        fi
    done
    if [[ $missing -ne 0 ]]; then
        echo
        echo "Run: bash make-targets.sh -a"
        echo "to build the AVR firmware before running integration tests."
        return 1
    fi

    if ! command -v simavr >/dev/null 2>&1; then
        echo "ERROR: simavr not found on PATH."
        echo "Install with: sudo apt-get install simavr libsimavr-dev pkg-config"
        return 1
    fi
    if [[ ! -f /usr/include/simavr/sim_avr.h ]]; then
        echo "ERROR: libsimavr-dev headers not found."
        echo "Install with: sudo apt-get install libsimavr-dev"
        return 1
    fi
    return 0
}
```

- [ ] **Step 3: Make `build_arch` short-circuit to `preflight_simavr_test` for that target**

Modify `build_arch`:
```bash
build_arch() {
    local target_arch="$1"
    local hardware_sig="$2"

    if [[ $target_arch == simavr_test ]]; then
        preflight_simavr_test || exit 1
    fi

    cmake -S . -B "build-$target_arch" -G "$GENERATOR" \
        -DCMAKE_INSTALL_PREFIX="." -DARCH="$target_arch" \
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
}
```

The existing make-targets.sh path then runs `make` and (where applicable) ctest in the build directory. If the script doesn't already run ctest for `test` targets, add the equivalent for `simavr_test`. Read the script to confirm — if it currently does only `cmake + make`, then add at the end of `build_arch`:
```bash
    if [[ $target_arch == simavr_test || $target_arch == test ]]; then
        (cd "build-$target_arch" && make && ctest --output-on-failure)
    fi
```

- [ ] **Step 4: Verify**

```bash
git stash    # to test from a clean tree
bash make-targets.sh -t simavr_test
git stash pop
```
Expected: pre-flight passes, cmake configures, make builds the runner, ctest runs all 30 cases green.

Then test the failure path:
```bash
mv build-atmega2560 /tmp/.bak-build-2560
bash make-targets.sh -t simavr_test
mv /tmp/.bak-build-2560 build-atmega2560
```
Expected: exits nonzero with the "missing ELF" message and the suggested `-a` command.

- [ ] **Step 5: Commit**

```bash
git add make-targets.sh
git commit -m "add make-targets.sh -t simavr_test support

- preflight checks all 5 AVR ELFs exist and that libsimavr/headers
  are installed; prints actionable install / build commands on failure.
- after the cmake configure, runs make + ctest in build-simavr-test/
  the same way -t test does for the host unit tests."
```

---

## Task 14: README authoring guide

**Files:**
- Create: `test/simavr/README.md`

- [ ] **Step 1: Write the recipe**

Create `test/simavr/README.md`:
```markdown
# simavr integration tests

These tests run each per-target ASDF firmware ELF through simavr,
drive matrix inputs, and assert correct ASCII output for a few
representative keypresses per keymap.

## Run locally

```bash
bash make-targets.sh -a              # build AVR firmware (one-time)
bash make-targets.sh -t simavr_test  # build runner, run ctest matrix
```

## Iterate on a single case

```bash
cd build-simavr-test
ctest -R simavr_atmega2560_sol -V    # one case, verbose
./test/simavr/asdf_simavr_runner \
    --target atmega2560 --keymap sol \
    --elf ../build-atmega2560/src/asdf-v1.6.6-atmega2560.elf \
    --verbose --vcd /tmp/sol.vcd
gtkwave /tmp/sol.vcd
```

## Add a new keymap test

1. Build the firmware: `bash make-targets.sh -a`.
2. Copy `keymap_data/asdf_simavr_test_classic.h` to
   `keymap_data/asdf_simavr_test_<new>.h`. Rename the struct
   (`<new>_test`, `<new>_events`).
3. Set `dip_value` to match the entry in `keymap_list.cmake`.
4. Set `modifier_shift` and `modifier_ctrl` to the new keymap's matrix
   coords for those keys (read `src/Keymaps/asdf_keymap_<new>.c`).
5. Add `<new>` to `SIMAVR_KEYMAPS` in `test/simavr/CMakeLists.txt`.
6. Add a `case` to `pick_keymap` in `asdf_simavr_runner.c` (with the
   matching `#include`).
7. Pick 3 matrix coordinates from the new keymap's matrix and the
   expected ASCII byte each produces; fill in the `events` array.
8. `bash make-targets.sh -t simavr_test`. New cases appear as
   `simavr_<each-target>_<new>`.
9. If a case fails, re-run with `--verbose --vcd` and inspect.

## Architecture

The harness lives entirely under `test/simavr/` and links libsimavr.
It never includes ASDF source headers — it talks only to AVR port
pins, so refactors to the firmware internals don't break tests.
Pin port:bit values are duplicated in `arch_io/asdf_simavr_io_family*.h`
from `src/Arch/asdf_arch_*.h`; if those source pin assignments change,
update the arch_io headers in lockstep.

See `docs/superpowers/specs/2026-05-25-simavr-integration-tests-design.md`
for the full design.
```

- [ ] **Step 2: Commit**

```bash
git add test/simavr/README.md
git commit -m "add README with author recipe for simavr integration tests

- local run, single-case iteration loop with gtkwave, and the
  step-by-step recipe for adding a new keymap test.
- points back to the spec for the why and the harness architecture."
```

---

## Task 15: CI workflow update

**Files:**
- Modify: `../../.github/workflows/asdf-firmware.yml` (full path:
  `/users/dave/vsrc/unified_retro_keyboard/.github/workflows/asdf-firmware.yml`)

- [ ] **Step 1: Replace the workflow file**

Read the current file once to confirm its structure matches what the spec captured, then overwrite with:
```yaml
name: asdf-firmware
on:
  push:
    branches:
      - main
      - asdf-release
      - asdf-build-test
  pull_request:
    branches:
      - main

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
        uses: actions/checkout@v4
      - run: apk add gcc-avr binutils-avr avr-libc
      - run: apk add cmake make
      - run: cd firmware/asdf; /bin/bash ./make-targets.sh -a -i -s
      - name: Upload built ELFs
        uses: actions/upload-artifact@v4
        with:
          name: asdf-elfs
          path: firmware/asdf/build-atmega*/src/asdf-v1.6.6-*.elf
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
      - uses: actions/checkout@v4
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

Note the `download-artifact@v4` step puts the ELFs back into a path that — depending on how `upload-artifact` flattens paths — may not exactly match the original `build-<target>/src/` layout. After downloading, the CI step may need a `find firmware/asdf -name 'asdf-v1.6.6-*.elf'` to confirm placement, and a small reshuffle. Verify behavior empirically in Step 2.

- [ ] **Step 2: Test the workflow in a feature branch**

```bash
cd /users/dave/vsrc/unified_retro_keyboard
git checkout -b ci/simavr-test
git add .github/workflows/asdf-firmware.yml
git commit -m "wire simavr integration tests into CI

- new integration_test job runs on ubuntu-latest, depends on
  build_firmware via artifact handoff of the ELFs.
- deploy moved to a separate job gated on asdf-release; preserves
  existing release behavior.
- triggers expanded to include main pushes + PRs to main so
  regressions surface before release-cut time."
git push -u origin ci/simavr-test
```

Watch the run in GitHub Actions. If the `Run integration tests` step fails due to download-artifact path layout, add a reshuffling step before "Configure":
```yaml
      - name: Re-layout downloaded ELFs
        run: |
          cd firmware/asdf
          for t in atmega328p atmega168p atmega640 atmega1280 atmega2560; do
            mkdir -p build-$t/src
            mv asdf-v1.6.6-$t.elf build-$t/src/  2>/dev/null || \
              find . -name "asdf-v1.6.6-$t.elf" -exec mv {} build-$t/src/ \;
          done
```
Adjust to whatever placement the actual download produces — `ls -R firmware/asdf` early in the step is a good first diagnostic.

- [ ] **Step 3: Once green, merge the feature branch into main**

```bash
git checkout main
git merge --no-ff ci/simavr-test -m "wire simavr integration tests into CI"
```
(or via a GitHub PR — same effect.)

- [ ] **Step 4: No additional commit** (the branch and merge are the commits).

---

## Self-review

After the plan was written, the following checks were performed and the plan was patched in place:

- **Spec coverage**: every section of the design doc maps to one or more tasks. Architecture → Tasks 2-12; harness components → Tasks 5-9; per-keymap data format → Tasks 10, 12; CMake/ctest → Tasks 2-3, 11; local build story → Tasks 13-14; CI → Task 15.
- **Placeholder scan**: the `ROW_A/COL_A` etc. tokens in Task 10 Step 3 are explicitly flagged as "implementer fills in actuals" with a recipe (Step 2) for how — this is research the implementer must do, not a placeholder for the plan author.
- **Type consistency**: `sim_event_t`, `sim_keymap_test_t`, `sim_coord_t`, `asdf_io_map_t`, `asdf_cap_record_t` all match across tasks. Function names (`cap_push`, `cap_pop`, `sim_run_until`, `sim_expect_byte_within`, `io_wire_output`, `io_wire_input`, `matrix_press`, `set_dip`, `pick_keymap`, `asdf_io_pick`, `vcd_begin`, `vcd_end`) used consistently.
- **Family A**: Task 7 defers family A's serial column injection; Task 11 Step 3 forces the decision (implement now vs. boot-only fallback) before claiming the full matrix is green.
