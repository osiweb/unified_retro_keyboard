# simavr typed-string and identity tests — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Extend the existing simavr integration test suite with two new per-keymap test modes — an identity-string assertion (boot output) and a typed-sentence assertion (shift/caps-toggle/ctrl transitions) — while preserving every existing event-based test case unchanged.

**Architecture:** Three coexisting test modes selected via a new `--mode events|identity|string` flag on the existing `asdf_simavr_runner` binary. The harness (`harness/*.c`), CI workflow, capture machinery, and existing test data are unchanged. Each per-keymap data file (`test/simavr/keymap_data/asdf_simavr_test_<name>.h`) grows two new static structs alongside the current `<name>_test`. CMake replaces its double `foreach` over (target, keymap) with a triple-loop adding a `mode` dimension.

**Tech Stack:** C99, simavr, CMake, ctest. Test data is plain-C static initializers; no codegen.

**Spec reference:** [`firmware/asdf/docs/superpowers/specs/2026-05-28-simavr-string-and-identity-tests-design.md`](../specs/2026-05-28-simavr-string-and-identity-tests-design.md)

---

## Pre-flight check

Before starting any task, verify the existing test suite passes on this branch:

```bash
cd firmware/asdf
bash make-targets.sh -a              # build AVR firmware
bash make-targets.sh -t simavr_test  # build runner, run ctest matrix
```

Expected: 25/25 tests pass. If any fail, stop and fix the existing breakage before extending the suite. Do not proceed to Task 1 while the baseline is red.

---

### Task 1: Add new struct types to `test_types.h`

**Files:**
- Modify: `firmware/asdf/test/simavr/harness/test_types.h`

This task adds type definitions only. No behavior change — the runner doesn't reference these types yet. Verification is that the test suite still builds.

- [ ] **Step 1: Add the new modifier constant and step-type enum**

Edit `firmware/asdf/test/simavr/harness/test_types.h`. After the existing `#define SIM_MOD_CTRL  2` line, add:

```c
#define SIM_MOD_CAPS  3
```

After the `sim_coord_t` typedef, add:

```c
typedef enum {
    SIM_STEP_KEY,          /* press+release a key, expect one output byte */
    SIM_STEP_MOD_DOWN,     /* press a modifier and hold */
    SIM_STEP_MOD_UP,       /* release the held modifier */
    SIM_STEP_MOD_TAP       /* press+release (used for the sticky caps toggle) */
} sim_step_type_t;
```

- [ ] **Step 2: Add the string-test structs**

After the existing `sim_keymap_test_t` definition, add:

```c
typedef struct {
    sim_step_type_t type;
    int row;               /* SIM_STEP_KEY: key coord */
    int col;
    int modifier;          /* SIM_STEP_MOD_*: SIM_MOD_SHIFT | SIM_MOD_CAPS | SIM_MOD_CTRL */
    uint8_t expected;      /* SIM_STEP_KEY: expected output byte (0 for mod steps) */
} sim_string_step_t;

typedef struct {
    uint8_t                  dip_value;
    uint32_t                 boot_scan_ticks;
    sim_coord_t              modifier_shift;
    sim_coord_t              modifier_caps_toggle;   /* shiftlock or capslock — keymap-specific */
    sim_coord_t              modifier_ctrl;
    const sim_string_step_t *steps;
    int                      num_steps;
} sim_string_test_t;
```

- [ ] **Step 3: Add the identity-test struct**

After `sim_string_test_t`, add:

```c
typedef struct {
    uint8_t             dip_value;
    uint32_t            boot_scan_ticks;   /* capture window */
    const char         *expected;          /* exact bytes the firmware should print */
    int                 expected_len;
} sim_identity_test_t;
```

- [ ] **Step 4: Verify the suite still builds and existing tests still pass**

Run:

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test
```

Expected: 25/25 tests pass (no new tests yet; existing matrix unchanged).

- [ ] **Step 5: Commit**

```bash
git add firmware/asdf/test/simavr/harness/test_types.h
git commit -m "add type definitions for simavr identity and string tests

- new SIM_MOD_CAPS modifier constant joining SHIFT/CTRL
- new sim_step_type_t enum (KEY, MOD_DOWN, MOD_UP, MOD_TAP) for
  step-driven typed-sentence tests
- new sim_string_step_t and sim_string_test_t for the typed-string
  mode; sim_identity_test_t for the identity mode
- types only; runner does not yet reference them"
```

---

### Task 2: Add `--mode` flag and dispatch scaffolding to the runner

**Files:**
- Modify: `firmware/asdf/test/simavr/asdf_simavr_runner.c`

This task extends the runner's CLI but does not yet implement identity or string mode. Unknown modes error out cleanly; `--mode events` (the default) behaves identically to today.

- [ ] **Step 1: Add `mode` to `args_t`**

In `firmware/asdf/test/simavr/asdf_simavr_runner.c`, change the `args_t` struct to add a `mode` field at the end:

```c
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
```

- [ ] **Step 2: Parse `--mode` in `parse_args`**

In `parse_args`, after the `--gdb` branch, add:

```c
        else if (!strcmp(argv[i], "--mode") && i + 1 < argc) a.mode = argv[++i];
```

After the `if (!a.target || !a.keymap || !a.elf_path) usage(argv[0]);` line, add a default:

```c
    if (!a.mode) a.mode = "events";
    if (strcmp(a.mode, "events") && strcmp(a.mode, "identity") && strcmp(a.mode, "string")) {
        fprintf(stderr, "unknown mode: %s\n", a.mode);
        usage(argv[0]);
    }
```

- [ ] **Step 3: Document `--mode` in `usage`**

In the `usage()` function's `fprintf` block, replace:

```c
        "  --gdb PORT  start simavr gdb stub on PORT and wait for attach\n",
```

with:

```c
        "  --gdb PORT  start simavr gdb stub on PORT and wait for attach\n"
        "  --mode M    events (default) | identity | string\n",
```

- [ ] **Step 4: Branch on `a.mode` in `main`**

Replace the body of `main` after `set_dip(km->dip_value);` is called. Currently the runner calls `pick_keymap`, then `set_dip(km->dip_value)`, then enters the events loop. Restructure so the events mode is wrapped in an `if (!strcmp(a.mode, "events"))` block, and add a placeholder for the other two modes that errors cleanly.

Specifically, locate this region in `main`:

```c
    const sim_keymap_test_t *km = pick_keymap(a.keymap);
    if (!km) { fprintf(stderr, "FAIL: no test data for keymap %s\n", a.keymap); return 1; }

    set_dip(km->dip_value);

    /* Let the firmware boot ... */
    if (sim_wait_ms(cpu, km->boot_scan_ticks, io->cpu_frequency_hz) < 0) {
```

…and all the way down to the final `printf("OK: %s/%s passed %d events ...", ...); return 0;`. Wrap this entire block in `if (!strcmp(a.mode, "events")) { ... }` and after the closing brace add:

```c
    if (!strcmp(a.mode, "identity")) {
        fprintf(stderr, "FAIL: identity mode not yet implemented for keymap %s\n", a.keymap);
        return 1;
    }

    if (!strcmp(a.mode, "string")) {
        fprintf(stderr, "FAIL: string mode not yet implemented for keymap %s\n", a.keymap);
        return 1;
    }

    fprintf(stderr, "FAIL: unreachable\n");
    return 1;
}
```

- [ ] **Step 5: Verify the suite still builds and existing tests still pass**

Run:

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test
```

Expected: 25/25 tests pass.

- [ ] **Step 6: Spot-check the new flag**

```bash
cd firmware/asdf/build-simavr_test/test/simavr
./asdf_simavr_runner --target atmega2560 --keymap classic --elf ../../../build-atmega2560/src/asdf-v1.7.0-atmega2560.elf --mode identity
```

Expected stderr: `FAIL: identity mode not yet implemented for keymap classic`. Exit code 1.

- [ ] **Step 7: Commit**

```bash
git add firmware/asdf/test/simavr/asdf_simavr_runner.c
git commit -m "add --mode flag and dispatch scaffolding to simavr runner

- new --mode events|identity|string flag, default 'events'
- 'events' branch preserves existing behavior verbatim
- 'identity' and 'string' branches error cleanly with a not-yet-
  implemented message; subsequent commits will land each mode"
```

---

### Task 3: Extend the CMake matrix to (target × keymap × mode)

**Files:**
- Modify: `firmware/asdf/test/simavr/CMakeLists.txt:59-74`

This task triple-loops the ctest matrix and renames the case suffix scheme. Existing case names (no suffix for `events`) are preserved so historical ctest filters keep working.

- [ ] **Step 1: Replace the double-foreach with a triple-foreach**

In `firmware/asdf/test/simavr/CMakeLists.txt`, replace lines 59-74:

```cmake
set(SIMAVR_TARGETS atmega328p atmega168p atmega1280 atmega2560)
set(SIMAVR_KEYMAPS classic classic_caps apple2 apple2_caps sol ace1000)

foreach(tgt ${SIMAVR_TARGETS})
  foreach(km ${SIMAVR_KEYMAPS})
    set(elf_path ${CMAKE_SOURCE_DIR}/build-${tgt}/src/asdf-v${PROJECT_VERSION}-${tgt}.elf)
    add_test(
      NAME simavr_${tgt}_${km}
      COMMAND asdf_simavr_runner
              --target ${tgt} --keymap ${km}
              --elf ${elf_path}
              --vcd ${CMAKE_CURRENT_BINARY_DIR}/simavr_${tgt}_${km}.vcd
    )
    set_tests_properties(simavr_${tgt}_${km} PROPERTIES TIMEOUT 15)
  endforeach()
endforeach()
```

with:

```cmake
set(SIMAVR_TARGETS atmega328p atmega168p atmega1280 atmega2560)
set(SIMAVR_KEYMAPS classic classic_caps apple2 apple2_caps sol ace1000)
set(SIMAVR_MODES   events identity string)

foreach(tgt ${SIMAVR_TARGETS})
  foreach(km ${SIMAVR_KEYMAPS})
    foreach(mode ${SIMAVR_MODES})
      set(elf_path ${CMAKE_SOURCE_DIR}/build-${tgt}/src/asdf-v${PROJECT_VERSION}-${tgt}.elf)
      if(mode STREQUAL events)
        set(suffix "")
      else()
        set(suffix "_${mode}")
      endif()
      add_test(
        NAME simavr_${tgt}_${km}${suffix}
        COMMAND asdf_simavr_runner
                --target ${tgt} --keymap ${km}
                --mode ${mode}
                --elf ${elf_path}
                --vcd ${CMAKE_CURRENT_BINARY_DIR}/simavr_${tgt}_${km}${suffix}.vcd
      )
      set_tests_properties(simavr_${tgt}_${km}${suffix} PROPERTIES TIMEOUT 30)
    endforeach()
  endforeach()
endforeach()
```

The timeout is bumped from 15 s to 30 s so string-mode cases (50+ steps) have headroom on slow targets.

- [ ] **Step 2: Verify the matrix now lists 73 tests, with all `_identity` and `_string` cases failing**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test 2>&1 | tail -10
```

Expected: ctest reports 73 tests total (1 unit_capture + 24 events + 24 identity + 24 string). The 24 events cases pass. The 48 new cases (identity and string) fail with the not-yet-implemented messages from Task 2.

- [ ] **Step 3: Commit**

```bash
git add firmware/asdf/test/simavr/CMakeLists.txt
git commit -m "extend simavr ctest matrix to (target x keymap x mode)

- adds SIMAVR_MODES = events identity string and triples the inner
  loop so each (target, keymap) pair gets three ctest cases
- 'events' produces no suffix so historical case names are preserved;
  'identity' and 'string' get _identity / _string suffixes
- timeout per case bumped from 15s to 30s to give string-mode runs
  headroom on slow targets
- the 48 newly-registered identity / string cases fail until later
  tasks land their dispatch and data"
```

---

### Task 4: Implement identity mode in the runner

**Files:**
- Modify: `firmware/asdf/test/simavr/asdf_simavr_runner.c`

This task lands the identity-mode logic and a `pick_identity` lookup function. The function returns NULL for every keymap until Task 5 populates the first identity test data. So at the end of this task all 24 identity cases still fail, but now with a "no identity test data for keymap X" error from `pick_identity`, not from the Task-2 stub.

- [ ] **Step 1: Add `pick_identity` stub above `main`**

In `firmware/asdf/test/simavr/asdf_simavr_runner.c`, after the existing `pick_keymap` function, add:

```c
static const sim_identity_test_t *pick_identity(const char *name)
{
    (void)name;
    /* Populated per-keymap in subsequent tasks. */
    return 0;
}
```

- [ ] **Step 2: Replace the identity-mode stub in `main` with the real dispatch**

In `main`, replace the block:

```c
    if (!strcmp(a.mode, "identity")) {
        fprintf(stderr, "FAIL: identity mode not yet implemented for keymap %s\n", a.keymap);
        return 1;
    }
```

with:

```c
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
```

- [ ] **Step 3: Verify the suite still builds and identity cases now fail with the new message**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test 2>&1 | grep -E "Failed|Passed" | tail -10
```

Expected: 25 pass (24 events + unit_capture), 48 fail (identity + string). The identity-case failures should mention "no identity test data for keymap" (not "identity mode not yet implemented").

- [ ] **Step 4: Commit**

```bash
git add firmware/asdf/test/simavr/asdf_simavr_runner.c
git commit -m "implement identity mode dispatch in simavr runner

- pick_identity() stub returns NULL for now; per-keymap data populates
  it in subsequent commits
- main()'s identity branch boots the firmware, runs sim_wait_ms for
  the configured capture window, then asserts the captured byte
  buffer matches the expected identity string exactly (length + each
  byte).  Failure prints byte-offset diagnostics."
```

---

### Task 5: Author identity test data for `classic` and wire into `pick_identity`

**Files:**
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic.h`
- Modify: `firmware/asdf/test/simavr/asdf_simavr_runner.c`

This task adds the first real identity test, validating the dispatch path end-to-end. The expected string for `classic` is `"[Keymap: classic]\n"` (18 bytes), which is documented in the existing test data file's comment.

- [ ] **Step 1: Capture the actual identity bytes to confirm**

Run the runner once with a deliberately-wrong placeholder so the failure prints the captured bytes. Temporarily edit `pick_identity` in the runner to return a dummy struct, OR (simpler) skip this step if you trust the existing comment in `asdf_simavr_test_classic.h:30` documenting `"[Keymap: classic]\n"` = 18 chars. The expected bytes per keymap are also visible by running the existing event-mode test with `--verbose` and observing the boot-time bytes captured before `cap_clear()` drains them.

For classic specifically, the expected bytes are: `[Keymap: classic]\n` (a 6-char prefix `[Keymap`, then `:`, space, the keymap name, `]`, newline).

- [ ] **Step 2: Add `classic_identity_test` to the data file**

In `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic.h`, before the closing `#endif`, add:

```c
/* Boot identity message printed by setup_classic_keymap() / classic ID hook.
 * 18 bytes at ~40 ms/char ≈ 720 ms; 1200 ms capture window covers it with
 * margin. */
static const sim_identity_test_t classic_identity_test = {
    .dip_value       = 0,
    .boot_scan_ticks = 1200,
    .expected        = "[Keymap: classic]\n",
    .expected_len    = 18,
};
```

- [ ] **Step 3: Wire `classic_identity_test` into `pick_identity`**

In `firmware/asdf/test/simavr/asdf_simavr_runner.c`, replace the body of `pick_identity` so it dispatches like `pick_keymap`:

```c
static const sim_identity_test_t *pick_identity(const char *name)
{
    if (!strcmp(name, "classic"))      return &classic_identity_test;
    return 0;
}
```

The `#include "keymap_data/asdf_simavr_test_classic.h"` directive at the top of the file already pulls in the new symbol; no additional include needed.

- [ ] **Step 4: Build and run only the classic identity cases**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test
cd build-simavr_test/test/simavr
ctest -R "simavr_.+_classic_identity" -V
```

Expected: 4 cases (one per target) all pass. Each prints `OK: <target>/classic identity 18 bytes at cycle ...`.

- [ ] **Step 5: Verify the rest of the suite**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test 2>&1 | tail -5
```

Expected: 29 pass (24 events + unit_capture + 4 classic_identity), 44 fail (20 remaining identity + 24 string).

- [ ] **Step 6: Commit**

```bash
git add firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic.h \
        firmware/asdf/test/simavr/asdf_simavr_runner.c
git commit -m "add classic keymap identity test data

- classic_identity_test asserts the 18-byte '[Keymap: classic]\\n'
  boot message
- pick_identity() now dispatches classic; remaining keymaps follow
  in the next commit"
```

---

### Task 6: Author identity test data for the remaining keymaps

**Files:**
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic_caps.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2_caps.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_sol.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_ace1000.h`
- Modify: `firmware/asdf/test/simavr/asdf_simavr_runner.c`

Each keymap's identity bytes can be captured by temporarily setting an empty expected string for that keymap, running the runner, and reading the captured bytes from the failure output. Or by reading the keymap's setup code in `src/Keymaps/asdf_keymap_<name>.c` to find the ID hook configuration.

For each of the five remaining keymaps, repeat the same recipe used for `classic` in Task 5.

- [ ] **Step 1: Discover the identity string for each keymap**

For each keymap, run the runner with a known-bad expected string to make the test fail and print the captured bytes:

```bash
cd firmware/asdf/build-simavr_test/test/simavr
# Temporarily add a dummy identity entry for the keymap you're discovering.
# Run the runner with --mode identity for that (target, keymap) pair.
# Read the captured bytes from stderr.  Copy them into the real data file.
```

Alternatively, grep `src/Keymaps/asdf_keymap_<name>.c` for the setup function's ID message — it's typically passed to `asdf_print_set_message` or similar.

Discover identity strings for: `classic_caps`, `apple2`, `apple2_caps`, `sol`, `ace1000`. Each will be a similar `[Keymap: <name>]\n` or analogous fixed string. The exact bytes and length depend on the keymap.

- [ ] **Step 2: Add `<name>_identity_test` to each data file**

For each of the five keymaps, add a struct like the classic example, with the discovered bytes:

```c
/* asdf_simavr_test_<name>.h, before the closing #endif */
static const sim_identity_test_t <name>_identity_test = {
    .dip_value       = <copy from existing <name>_test.dip_value>,
    .boot_scan_ticks = 1200,                /* extend if the print train is longer */
    .expected        = "...",               /* exact captured bytes */
    .expected_len    = <length>,
};
```

`dip_value` must match the value already used in the keymap's `<name>_test` struct (don't recompute it; copy).

- [ ] **Step 3: Extend `pick_identity` to dispatch every keymap**

In `firmware/asdf/test/simavr/asdf_simavr_runner.c`, replace `pick_identity` with:

```c
static const sim_identity_test_t *pick_identity(const char *name)
{
    if (!strcmp(name, "classic"))      return &classic_identity_test;
    if (!strcmp(name, "classic_caps")) return &classic_caps_identity_test;
    if (!strcmp(name, "apple2"))       return &apple2_identity_test;
    if (!strcmp(name, "apple2_caps"))  return &apple2_caps_identity_test;
    if (!strcmp(name, "sol"))          return &sol_identity_test;
    if (!strcmp(name, "ace1000"))      return &ace1000_identity_test;
    return 0;
}
```

- [ ] **Step 4: Run all identity cases**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test
cd build-simavr_test/test/simavr
ctest -R "_identity$" -V
```

Expected: 24 cases (4 targets × 6 keymaps) all pass.

- [ ] **Step 5: Full suite check**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test 2>&1 | tail -5
```

Expected: 49 pass (24 events + unit_capture + 24 identity), 24 fail (string).

- [ ] **Step 6: Commit**

```bash
git add firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic_caps.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2_caps.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_sol.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_ace1000.h \
        firmware/asdf/test/simavr/asdf_simavr_runner.c
git commit -m "add identity test data for remaining five keymaps

- per-keymap sim_identity_test_t records the exact boot identity
  bytes for classic_caps, apple2, apple2_caps, sol, ace1000
- pick_identity() now dispatches all six keymaps; all 24 identity
  ctest cases (4 targets x 6 keymaps) pass"
```

---

### Task 7: Implement string mode in the runner

**Files:**
- Modify: `firmware/asdf/test/simavr/asdf_simavr_runner.c`

This task lands the step-walker for string mode. It adds a `pick_string_test` stub returning NULL; the first real string test is wired in Task 8. After this task, all 24 string cases fail with "no string test data for keymap X".

- [ ] **Step 1: Add `pick_string_test` stub above `main`**

In `firmware/asdf/test/simavr/asdf_simavr_runner.c`, after `pick_identity`, add:

```c
static const sim_string_test_t *pick_string_test(const char *name)
{
    (void)name;
    /* Populated per-keymap in subsequent tasks. */
    return 0;
}
```

- [ ] **Step 2: Add a modifier-coord helper**

After `pick_string_test`, add:

```c
static sim_coord_t string_mod_coord(const sim_string_test_t *st, int mod)
{
    switch (mod) {
        case SIM_MOD_SHIFT: return st->modifier_shift;
        case SIM_MOD_CAPS:  return st->modifier_caps_toggle;
        case SIM_MOD_CTRL:  return st->modifier_ctrl;
        default: { sim_coord_t z = { -1, -1 }; return z; }
    }
}
```

- [ ] **Step 3: Replace the string-mode stub in `main` with the step walker**

Replace the block:

```c
    if (!strcmp(a.mode, "string")) {
        fprintf(stderr, "FAIL: string mode not yet implemented for keymap %s\n", a.keymap);
        return 1;
    }
```

with:

```c
    if (!strcmp(a.mode, "string")) {
        const sim_string_test_t *st = pick_string_test(a.keymap);
        if (!st) {
            fprintf(stderr, "FAIL: no string test data for keymap %s\n", a.keymap);
            return 1;
        }

        set_dip(st->dip_value);

        if (sim_wait_ms(cpu, st->boot_scan_ticks, io->cpu_frequency_hz) < 0) {
            fprintf(stderr, "FAIL: cpu halted during string boot wait\n");
            return 1;
        }
        cap_clear();   /* drain boot identity output */

        for (int i = 0; i < st->num_steps; i++) {
            const sim_string_step_t *step = &st->steps[i];
            char what[64];

            switch (step->type) {
                case SIM_STEP_KEY: {
                    snprintf(what, sizeof what, "%s/step[%d]@(%d,%d)",
                             a.keymap, i, step->row, step->col);
                    matrix_press(step->row, step->col);
                    if (sim_expect_byte_within(cpu, step->expected, 400000, what) != 0) {
                        vcd_end();
                        return 1;
                    }
                    matrix_release(step->row, step->col);
                    sim_wait_ms(cpu, 50, io->cpu_frequency_hz);
                    cap_clear();
                    break;
                }
                case SIM_STEP_MOD_DOWN: {
                    sim_coord_t c = string_mod_coord(st, step->modifier);
                    matrix_press(c.row, c.col);
                    sim_wait_ms(cpu, 15, io->cpu_frequency_hz);
                    cap_clear();
                    break;
                }
                case SIM_STEP_MOD_UP: {
                    sim_coord_t c = string_mod_coord(st, step->modifier);
                    matrix_release(c.row, c.col);
                    sim_wait_ms(cpu, 15, io->cpu_frequency_hz);
                    cap_clear();
                    break;
                }
                case SIM_STEP_MOD_TAP: {
                    sim_coord_t c = string_mod_coord(st, step->modifier);
                    matrix_press(c.row, c.col);
                    sim_wait_ms(cpu, 15, io->cpu_frequency_hz);
                    matrix_release(c.row, c.col);
                    sim_wait_ms(cpu, 15, io->cpu_frequency_hz);
                    cap_clear();
                    break;
                }
            }
        }

        vcd_end();
        printf("OK: %s/%s passed %d string steps at cycle %" PRIu64 "\n",
               a.target, a.keymap, st->num_steps, (uint64_t)cpu->cycle);
        return 0;
    }
```

- [ ] **Step 4: Verify the suite still builds and string cases now fail with the new message**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test 2>&1 | grep -E "Failed|Passed" | tail -10
```

Expected: 49 pass, 24 fail. String-case failures now report "no string test data for keymap" (from the `pick_string_test` lookup), not the Task-2 stub.

- [ ] **Step 5: Commit**

```bash
git add firmware/asdf/test/simavr/asdf_simavr_runner.c
git commit -m "implement string mode dispatch in simavr runner

- pick_string_test() stub returns NULL; per-keymap data populates it
  in subsequent commits
- string_mod_coord() picks the right modifier coord for SHIFT, CAPS,
  or CTRL from the test struct
- main()'s string branch walks the step array: KEY presses do a press
  / expect_byte / release / 50ms guard; MOD_DOWN/UP do press or release
  + 15ms settle; MOD_TAP does press / 15ms / release / 15ms.  Capture
  drained between every step."
```

---

### Task 8: Author string test data for `classic` and wire into `pick_string_test`

**Files:**
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic.h`
- Modify: `firmware/asdf/test/simavr/asdf_simavr_runner.c`

This is the most involved per-keymap authoring task. For `classic` (lowercase-default), the typed sentence is:

```
<shift>t</shift>his is a <caps tap>test<caps tap> of the classic keymap.<ctrl>m</ctrl>
```

Expected output: `This is a TEST of the classic keymap.\r` (39 bytes).

- [ ] **Step 1: Locate the caps-toggle coord for `classic`**

Read `src/Keymaps/asdf_keymap_classic.c` and `src/Keymaps/asdf_keymap_defs_classic.h`. Find the `(row, col)` in the plain matrix mapped to the shiftlock action (look for `SHIFTLOCK`, `SHIFT_LOCK`, or `CAPSLOCK` action tokens in the matrix initializer). Record the coord — it'll be e.g. `{ .row = 0, .col = 5 }`.

- [ ] **Step 2: Locate the matrix coord for every key used in the script**

The script types the following key chars (each is one physical key, regardless of case): `t h i s a e o f k y m p` plus space, period, and the key used for Ctrl-M.

Read the `classic_plain_matrix` definition in `src/Keymaps/asdf_keymap_classic.c`. For each char in the list above, find the `(row, col)` whose plain-matrix value matches that character. Note: matrices in this codebase are declared `[NUM_ROWS][NUM_COLS]`, so a literal `'t'` at `plain_matrix[1][6]` means row=1, col=6.

The key used for Ctrl-M is whichever key sits where `'m'` is in the plain matrix — the same physical key, just pressed with Ctrl held to produce `\r` (per the firmware's standard ctrl-decode).

Make a small notes table for yourself, e.g.:

```
't' -> (1, 6)
'h' -> (R, C)
... etc
```

- [ ] **Step 3: Author `classic_string_steps[]`**

In `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic.h`, before the closing `#endif`, add:

```c
/* Typed sentence per the spec:
 *   <shift>t</shift>his is a <caps>test<caps> of the classic keymap.<ctrl>m</ctrl>
 * For classic (lowercase default), the expected output is:
 *   "This is a TEST of the classic keymap.\r"   (39 bytes)
 *
 * Coordinates come from src/Keymaps/asdf_keymap_classic.c plain matrix.
 * Fill in the (R, C) blanks per the matrix table you noted above. */
static const sim_string_step_t classic_string_steps[] = {
    /* <shift>t</shift> -> 'T' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY, .row = 1, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_SHIFT },

    /* "his is a " */
    { .type = SIM_STEP_KEY, .row = <h_R>, .col = <h_C>, .expected = 'h' },
    { .type = SIM_STEP_KEY, .row = <i_R>, .col = <i_C>, .expected = 'i' },
    { .type = SIM_STEP_KEY, .row = <s_R>, .col = <s_C>, .expected = 's' },
    { .type = SIM_STEP_KEY, .row = <sp_R>, .col = <sp_C>, .expected = ' ' },
    { .type = SIM_STEP_KEY, .row = <i_R>, .col = <i_C>, .expected = 'i' },
    { .type = SIM_STEP_KEY, .row = <s_R>, .col = <s_C>, .expected = 's' },
    { .type = SIM_STEP_KEY, .row = <sp_R>, .col = <sp_C>, .expected = ' ' },
    { .type = SIM_STEP_KEY, .row = <a_R>, .col = <a_C>, .expected = 'a' },
    { .type = SIM_STEP_KEY, .row = <sp_R>, .col = <sp_C>, .expected = ' ' },

    /* <caps>test<caps> -> "TEST" */
    { .type = SIM_STEP_MOD_TAP, .modifier = SIM_MOD_CAPS },
    { .type = SIM_STEP_KEY, .row = 1, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_KEY, .row = <e_R>, .col = <e_C>, .expected = 'E' },
    { .type = SIM_STEP_KEY, .row = <s_R>, .col = <s_C>, .expected = 'S' },
    { .type = SIM_STEP_KEY, .row = 1, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_MOD_TAP, .modifier = SIM_MOD_CAPS },

    /* " of the classic keymap." */
    { .type = SIM_STEP_KEY, .row = <sp_R>, .col = <sp_C>, .expected = ' ' },
    { .type = SIM_STEP_KEY, .row = <o_R>, .col = <o_C>, .expected = 'o' },
    { .type = SIM_STEP_KEY, .row = <f_R>, .col = <f_C>, .expected = 'f' },
    { .type = SIM_STEP_KEY, .row = <sp_R>, .col = <sp_C>, .expected = ' ' },
    { .type = SIM_STEP_KEY, .row = <t_R>, .col = <t_C>, .expected = 't' },
    { .type = SIM_STEP_KEY, .row = <h_R>, .col = <h_C>, .expected = 'h' },
    { .type = SIM_STEP_KEY, .row = <e_R>, .col = <e_C>, .expected = 'e' },
    { .type = SIM_STEP_KEY, .row = <sp_R>, .col = <sp_C>, .expected = ' ' },
    { .type = SIM_STEP_KEY, .row = <c_R>, .col = <c_C>, .expected = 'c' },
    { .type = SIM_STEP_KEY, .row = <l_R>, .col = <l_C>, .expected = 'l' },
    { .type = SIM_STEP_KEY, .row = <a_R>, .col = <a_C>, .expected = 'a' },
    { .type = SIM_STEP_KEY, .row = <s_R>, .col = <s_C>, .expected = 's' },
    { .type = SIM_STEP_KEY, .row = <s_R>, .col = <s_C>, .expected = 's' },
    { .type = SIM_STEP_KEY, .row = <i_R>, .col = <i_C>, .expected = 'i' },
    { .type = SIM_STEP_KEY, .row = <c_R>, .col = <c_C>, .expected = 'c' },
    { .type = SIM_STEP_KEY, .row = <sp_R>, .col = <sp_C>, .expected = ' ' },
    { .type = SIM_STEP_KEY, .row = <k_R>, .col = <k_C>, .expected = 'k' },
    { .type = SIM_STEP_KEY, .row = <e_R>, .col = <e_C>, .expected = 'e' },
    { .type = SIM_STEP_KEY, .row = <y_R>, .col = <y_C>, .expected = 'y' },
    { .type = SIM_STEP_KEY, .row = <m_R>, .col = <m_C>, .expected = 'm' },
    { .type = SIM_STEP_KEY, .row = <a_R>, .col = <a_C>, .expected = 'a' },
    { .type = SIM_STEP_KEY, .row = <p_R>, .col = <p_C>, .expected = 'p' },
    { .type = SIM_STEP_KEY, .row = <dot_R>, .col = <dot_C>, .expected = '.' },

    /* <ctrl>m</ctrl> -> '\r' */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_CTRL },
    { .type = SIM_STEP_KEY, .row = <m_R>, .col = <m_C>, .expected = '\r' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_CTRL },
};

static const sim_string_test_t classic_string_test = {
    .dip_value             = 0,
    .boot_scan_ticks       = 1200,
    .modifier_shift        = { .row = 0, .col = 2 },     /* from classic_test */
    .modifier_caps_toggle  = { .row = <caps_R>, .col = <caps_C> },   /* from step 1 */
    .modifier_ctrl         = { .row = 0, .col = 6 },     /* from classic_test */
    .steps     = classic_string_steps,
    .num_steps = sizeof(classic_string_steps) / sizeof(classic_string_steps[0]),
};
```

Replace each `<x_R>` / `<x_C>` placeholder with the coord you recorded in step 2.

- [ ] **Step 4: Wire `classic_string_test` into `pick_string_test`**

In `firmware/asdf/test/simavr/asdf_simavr_runner.c`, replace `pick_string_test` with:

```c
static const sim_string_test_t *pick_string_test(const char *name)
{
    if (!strcmp(name, "classic"))      return &classic_string_test;
    return 0;
}
```

- [ ] **Step 5: Run only the classic string cases**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test
cd build-simavr_test/test/simavr
ctest -R "simavr_.+_classic_string" -V
```

Expected: 4 cases pass. Each prints `OK: <target>/classic passed 47 string steps at cycle ...` (step count may differ slightly depending on exact script length).

If a case fails, the failure prints the diverging step index. Re-run that one case with `--verbose --vcd /tmp/classic_string.vcd` and inspect:

```bash
./asdf_simavr_runner --target atmega2560 --keymap classic \
    --elf ../../../build-atmega2560/src/asdf-v1.7.0-atmega2560.elf \
    --mode string --verbose --vcd /tmp/classic_string.vcd
gtkwave /tmp/classic_string.vcd
```

Common causes: wrong matrix coord (re-check step 2), wrong modifier coord (re-check step 1), missing `\r` row/col for the m-key.

- [ ] **Step 6: Full suite check**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test 2>&1 | tail -5
```

Expected: 53 pass (49 + 4 classic_string), 20 fail (string cases for other 5 keymaps).

- [ ] **Step 7: Commit**

```bash
git add firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic.h \
        firmware/asdf/test/simavr/asdf_simavr_runner.c
git commit -m "add classic keymap typed-string test

- classic_string_steps walks <shift>t</shift>his is a <caps>test<caps>
  of the classic keymap.<ctrl>m</ctrl>, expecting
  'This is a TEST of the classic keymap.\\r'
- pick_string_test() now dispatches classic; remaining keymaps follow
  in the next commit"
```

---

### Task 9: Author string test data for the remaining keymaps

**Files:**
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic_caps.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2_caps.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_sol.h`
- Modify: `firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_ace1000.h`
- Modify: `firmware/asdf/test/simavr/asdf_simavr_runner.c`

For each remaining keymap, follow the same recipe as Task 8 (steps 1-4). The differences are per-keymap matrix coords, the choice of `<mapname>` expansion, and the expected byte for each KEY step — which depends on the keymap's plain/shift/caps semantics.

Recommended order: `classic_caps` first (closest to classic, mostly identical coords); then `apple2`, `apple2_caps`, `sol`, `ace1000`.

- [ ] **Step 1: Per-keymap authoring loop**

For each keymap in {`classic_caps`, `apple2`, `apple2_caps`, `sol`, `ace1000`}:

  1. **Locate the caps-toggle coord** by reading `src/Keymaps/asdf_keymap_<name>.c` and its `*_add_map.c` partner. For Sol-20 the relevant token is `SOL_KBD_SHIFTLOCK_ACTION`; for boot-CAPS keymaps it'll be `ACTION_CAPS` or `ACTION_CAPSLOCK`.

  2. **Choose a `<mapname>` expansion.** It can be the literal keymap name, the name with underscores replaced by spaces, or anything else identifying. If the chosen name has chars not on the plain matrix (e.g., `_` requires shift on some keymaps), pick an alternative.

  3. **Locate each key coord** in `src/Keymaps/asdf_keymap_<name>.c` for every char in the typed script + the `<mapname>` expansion. For boot-CAPS keymaps (apple2, sol, ace1000), the plain matrix is the *caps* matrix, so letters appear as uppercase there.

  4. **Compute the expected byte per KEY step** based on the current modifier state and the keymap's matrices:
     - For boot-CAPS keymaps: caps is on at start. Plain key presses produce uppercase. The first `<caps tap>` *disables* caps; mid-sentence letters then come out lowercase. The second `<caps tap>` re-enables caps.
     - For `classic_caps`: caps is on at start; the caps-toggle key may be a no-op (matrix always uppercase). Verify by reading the keymap.
     - Shift behavior varies: many keymaps' shift matrix inverts case for letters; some leave it unchanged. Read the relevant matrix.

  5. **Add `<name>_string_steps[]` and `<name>_string_test`** to the data file, modeled on classic's. The expected byte sequence overall should be a sensible English-looking string with case variations consistent with the keymap's matrix semantics.

  6. **Run that keymap's string cases**:

     ```bash
     cd firmware/asdf
     bash make-targets.sh -t simavr_test
     cd build-simavr_test/test/simavr
     ctest -R "simavr_.+_<name>_string" -V
     ```

     Iterate (read the diverging-step diagnostic, fix coords or expected bytes) until 4/4 targets pass for this keymap.

- [ ] **Step 2: Update `pick_string_test` to dispatch all keymaps**

Replace `pick_string_test` in `firmware/asdf/test/simavr/asdf_simavr_runner.c` with:

```c
static const sim_string_test_t *pick_string_test(const char *name)
{
    if (!strcmp(name, "classic"))      return &classic_string_test;
    if (!strcmp(name, "classic_caps")) return &classic_caps_string_test;
    if (!strcmp(name, "apple2"))       return &apple2_string_test;
    if (!strcmp(name, "apple2_caps"))  return &apple2_caps_string_test;
    if (!strcmp(name, "sol"))          return &sol_string_test;
    if (!strcmp(name, "ace1000"))      return &ace1000_string_test;
    return 0;
}
```

You may edit `pick_string_test` incrementally as you finish each keymap rather than waiting for the end.

- [ ] **Step 3: Final full-suite check**

```bash
cd firmware/asdf
bash make-targets.sh -t simavr_test 2>&1 | tail -5
```

Expected: 73 pass, 0 fail. Total runtime around 60–90 s.

- [ ] **Step 4: Commit**

You may either commit per-keymap or batch them. A single batched commit is fine if the per-keymap iteration didn't introduce surprises:

```bash
git add firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_classic_caps.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_apple2_caps.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_sol.h \
        firmware/asdf/test/simavr/keymap_data/asdf_simavr_test_ace1000.h \
        firmware/asdf/test/simavr/asdf_simavr_runner.c
git commit -m "add typed-string tests for remaining five keymaps

- per-keymap step arrays and sim_string_test_t records exercise the
  shared shift / caps-toggle / ctrl sentence on classic_caps, apple2,
  apple2_caps, sol, and ace1000
- expected output bytes computed per each keymap's plain/shift/caps
  matrix semantics (boot-CAPS keymaps drop to lowercase between caps
  taps; classic_caps stays uppercase throughout)
- pick_string_test() now dispatches all six keymaps; all 24 string
  ctest cases (4 targets x 6 keymaps) pass"
```

---

### Task 10: Update the simavr test README

**Files:**
- Modify: `firmware/asdf/test/simavr/README.md`

Document the three test modes and the per-keymap authoring story for identity and string tests, alongside the existing event-test recipe.

- [ ] **Step 1: Add a section describing the three test modes**

In `firmware/asdf/test/simavr/README.md`, after the existing "Iterate on a single case" section (line 34) and before "Add a new keymap test" (line 59), insert:

```markdown
## Test modes

Each (target, keymap) pair runs three ctest cases:

| ctest case suffix | runner `--mode` | what it asserts |
|---|---|---|
| `simavr_<tgt>_<km>` | `events` (default) | A small set of atomic keypresses with optional shift/ctrl modifier; one expected ASCII byte per press. |
| `simavr_<tgt>_<km>_identity` | `identity` | The exact byte sequence emitted during boot, before any keypress. |
| `simavr_<tgt>_<km>_string` | `string` | A typed sentence that exercises shift held, shift released mid-stream, a sticky caps-toggle, and ctrl held in one capture. |

The runner takes `--mode events|identity|string`; default is `events`.
```

- [ ] **Step 2: Extend the "Add a new keymap test" section**

In the same README, the "Add a new keymap test" recipe currently documents only the event-based test. After its closing step (item 9 in the current README), add:

```markdown
10. Author the **identity test** for the new keymap. Discover the boot
    identity bytes by temporarily setting a dummy `expected` and
    running `--mode identity --verbose` against the new keymap; copy
    the captured bytes back into `<new>_identity_test.expected`. Wire
    `<new>_identity_test` into `pick_identity` in
    `asdf_simavr_runner.c`.

11. Author the **string test** for the new keymap. Follow the per-
    keymap recipe in
    `docs/superpowers/plans/2026-05-28-simavr-string-and-identity-tests.md`
    Task 8: locate the caps-toggle coord, locate every key coord used
    in the typed sentence, compute the expected byte per step based on
    the keymap's plain/shift/caps matrix semantics, and wire
    `<new>_string_test` into `pick_string_test`. The shared sentence
    is `<shift>t</shift>his is a <caps>test<caps> of the <mapname>
    keymap.<ctrl>m</ctrl>`. The `<mapname>` expansion is
    per-keymap-author's choice (literal name, spaced, or any
    identifying string).
```

- [ ] **Step 3: Update the `--mode` flag entry in the runner flags list**

In the same README, the "Runner flags" section (around line 46) lists `--verbose`, `--vcd`, `--boot-only`, `--gdb`. Add `--mode` after `--gdb`:

```markdown
- `--mode events|identity|string` — pick which test mode the runner
  drives. Default `events` preserves backwards-compatible behavior.
  See Test modes above.
```

- [ ] **Step 4: Confirm rendered Markdown still scans cleanly**

A quick sanity check that the README still renders. The simplest is just to open it in a browser or scan it visually for broken table formatting.

- [ ] **Step 5: Commit**

```bash
git add firmware/asdf/test/simavr/README.md
git commit -m "document simavr identity and string test modes

- new 'Test modes' section explains the three modes and ctest suffix
  convention
- 'Add a new keymap test' recipe extended with identity (step 10) and
  string (step 11) authoring steps
- new --mode flag added to the runner-flags list"
```

---

## Post-completion checklist

After Task 10, verify the end state:

- [ ] `cd firmware/asdf && bash make-targets.sh -t simavr_test` reports 73 pass, 0 fail in ~60–90 s.
- [ ] `git log` shows 10 well-formed commits (one per task) on the branch.
- [ ] The CI workflow `integration_test` job, when this branch is pushed, runs the new matrix to green without any workflow file changes.
