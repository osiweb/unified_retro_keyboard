# simavr typed-string and identity tests for ASDF firmware

## Background and motivation

The simavr integration suite ([`2026-05-25-simavr-integration-tests-design.md`](2026-05-25-simavr-integration-tests-design.md))
asserts 3–6 representative key presses per (target, keymap) pair. That
catches keymap-wide regressions but leaves a few classes of bugs
uncovered:

- **Modifier transitions inside a single key sequence** — the existing
  cases press one main key with at most one modifier held, then drop
  everything before moving to the next event. They do not exercise
  patterns like "press shift, type one letter, release shift, then keep
  typing without shift" — a basic typing sequence that touches the
  modifier deactivation paths.
- **Sticky toggle behavior** — shiftlock/capslock presses are not
  exercised. The existing event model has no way to express a sticky
  state change without consuming an output byte per modifier.
- **The boot identity message** — each keymap prints an identity string
  during boot (`"[Keymap: classic]\n"` etc). The current cases drain
  these bytes without asserting them, so a corrupted or wrong identity
  message would pass.

This spec adds two new test modes to the existing simavr runner, both
re-using its harness and capture machinery. The new modes coexist with
the current event-based cases — they do not replace them.

## Goals

- Catch regressions in the modifier-deactivation path by typing a
  short sentence that uses shift held, shift released mid-stream, a
  sticky caps toggle, and ctrl held — all in one continuous capture.
- Catch regressions in the boot identity output by asserting the exact
  bytes each keymap emits before user input begins.
- Extend the matrix to (target × keymap × test-mode), with the existing
  event-based cases preserved unchanged.
- Keep the authoring story for new keymaps consistent: per-keymap test
  data lives in `keymap_data/asdf_simavr_test_<name>.h`, hand-written,
  no firmware-header coupling.

## Non-goals

- No firmware changes. The tests observe behavior only.
- No automatic derivation of expected output from keymap matrices. Each
  keymap's expected output strings are hand-authored, same as the
  existing per-event expected bytes.
- No new VCD or capture machinery. Both new modes use the existing
  `cap_*` and `sim_expect_byte_within` helpers.
- No coverage of additional modifier types (alt, meta, etc.) beyond
  shift, caps-toggle, and ctrl.

## Test types

Three ctest cases per (target, keymap), all driven by the same runner
binary via a `--mode` flag:

| ctest case suffix | runner mode | what it asserts |
|---|---|---|
| (unchanged) `simavr_<target>_<keymap>` | `events` (default) | Existing per-event press/expect cases — preserved exactly as today. |
| `simavr_<target>_<keymap>_identity` | `identity` | Boot the firmware; capture every byte emitted during boot; compare against the keymap's expected identity string. |
| `simavr_<target>_<keymap>_string` | `string` | Drive a typed-sentence script with explicit modifier transitions; assert byte-by-byte output. |

Matrix size grows from 24 cases (4 targets × 6 keymaps) to 72. The
runtime cost is roughly linear in step count; expect total integration
runtime to roughly triple, from ~30 s to ~90 s.

## The typed-string script

The script is a per-keymap data structure (no `{mapname}` substitution
in code — the expansion is baked into each keymap's step array). The
canonical typed sentence is:

```
<shift press>t<shift release>his is a <caps tap>test<caps tap> of the <mapname> keymap.<ctrl press>m<ctrl release>
```

For each keymap, the test author encodes the literal sequence of script
steps, computing the expected output byte for each `KEY` step based on
the keymap's matrices and the current modifier state.

Example expected outputs (the test author computes these by hand):

- `classic`: `This is a TEST of the classic keymap.\r`
- `classic_caps`: `THIS IS A TEST OF THE CLASSIC_CAPS KEYMAP.\r` (caps-locked; shift and caps-toggle have no effect on letter case)
- `apple2`: depends on apple2's shift and caps semantics — encoded per the matrix definitions in `src/Keymaps/asdf_keymap_apple2.c`.

The `<mapname>` token expands to whatever the test author wrote in that
keymap's data file. It can be the literal keymap name (`classic`),
spaced out (`classic caps`), or any other identifying string the author
chooses — there is no requirement that it match the cmake keymap
identifier. This avoids forcing the script to type an underscore on
keymaps where underscore is a shifted character.

## The identity test

Each keymap prints a fixed identity string during boot. The identity
test boots the firmware, captures every byte emitted in a configurable
window (default 1.2 s, longer than the longest known print train), and
compares the captured byte sequence to the keymap's hand-authored
`expected` string.

Failure prints the captured bytes alongside the expected bytes with a
byte-offset diff.

## Data model

Additions to `test/simavr/harness/test_types.h`:

```c
#define SIM_MOD_CAPS  3   /* joins SIM_MOD_NONE / SHIFT / CTRL */

typedef enum {
    SIM_STEP_KEY,          /* press+release a key, expect one byte */
    SIM_STEP_MOD_DOWN,     /* press a modifier and hold */
    SIM_STEP_MOD_UP,       /* release the held modifier */
    SIM_STEP_MOD_TAP       /* press+release (used for the sticky caps toggle) */
} sim_step_type_t;

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
    sim_coord_t              modifier_caps_toggle;  /* shiftlock or capslock — keymap-specific */
    sim_coord_t              modifier_ctrl;
    const sim_string_step_t *steps;
    int                      num_steps;
} sim_string_test_t;

typedef struct {
    uint32_t            boot_scan_ticks;   /* capture window */
    const char         *expected;          /* exact bytes the firmware should print */
    int                 expected_len;
} sim_identity_test_t;
```

The existing `sim_keymap_test_t` is unchanged. The two new structs are
independent — they share no fields with each other or with the event
struct beyond `sim_coord_t`.

### Per-keymap data file

Each `keymap_data/asdf_simavr_test_<name>.h` gains two new exported
objects alongside `<name>_test`:

```c
static const sim_string_step_t classic_string_steps[] = {
    /* "<shift>t</shift>his is a " */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY, .row = 1, .col = 6, .expected = 'T' },   /* t */
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_SHIFT },
    { .type = SIM_STEP_KEY, .row = R, .col = C, .expected = 'h' },
    /* ... letters ... */

    /* "TEST" via sticky caps */
    { .type = SIM_STEP_MOD_TAP, .modifier = SIM_MOD_CAPS },
    { .type = SIM_STEP_KEY, .row = 1, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_KEY, .row = R, .col = C, .expected = 'E' },
    { .type = SIM_STEP_KEY, .row = R, .col = C, .expected = 'S' },
    { .type = SIM_STEP_KEY, .row = 1, .col = 6, .expected = 'T' },
    { .type = SIM_STEP_MOD_TAP, .modifier = SIM_MOD_CAPS },

    /* " of the classic keymap." */
    /* ... letters ... */

    /* Ctrl-M */
    { .type = SIM_STEP_MOD_DOWN, .modifier = SIM_MOD_CTRL },
    { .type = SIM_STEP_KEY, .row = R, .col = C, .expected = '\r' },
    { .type = SIM_STEP_MOD_UP,   .modifier = SIM_MOD_CTRL },
};

static const sim_string_test_t classic_string_test = {
    .dip_value = 0,
    .boot_scan_ticks = 1000,
    .modifier_shift        = { .row = 0, .col = 2 },
    .modifier_caps_toggle  = { .row = R, .col = C },   /* author fills in */
    .modifier_ctrl         = { .row = 0, .col = 6 },
    .steps     = classic_string_steps,
    .num_steps = sizeof(classic_string_steps) / sizeof(classic_string_steps[0]),
};

static const sim_identity_test_t classic_identity_test = {
    .boot_scan_ticks = 1200,
    .expected        = "[Keymap: classic]\n",
    .expected_len    = 18,
};
```

The per-step expected byte (rather than a top-level expected string) is
deliberate: when a wrong modifier transition garbles the sentence,
ctest output names the exact step that diverged, which is far faster to
diagnose than a whole-string diff.

## Runner changes

`asdf_simavr_runner` gains a `--mode events|identity|string` flag,
default `events`. The runner picks one of three new dispatch paths
based on the mode:

- **`events` mode** — unchanged from today. Looks up `<name>_test`.
- **`identity` mode** — looks up `<name>_identity_test`. Boots the
  firmware and runs `sim_wait_ms` for `boot_scan_ticks`. The existing
  `cap_*` ring buffer captures every byte emitted on the data port
  during that window. After the wait, compares the captured byte
  buffer length and contents to `expected`. On match, exits 0. On
  mismatch, prints a side-by-side diff with byte offsets.
- **`string` mode** — looks up `<name>_string_test`. "Drain capture"
  below means `cap_clear()` — resets the capture ring buffer so the
  next `KEY` step starts with no residual bytes. Walks the steps:
  - `KEY`: `matrix_press(row, col)`, `sim_expect_byte_within` for the
    expected byte, `matrix_release(row, col)`, 50 ms guard wait.
  - `MOD_DOWN`: press the appropriate modifier coord (shift, caps, or
    ctrl), 15 ms settle, drain capture.
  - `MOD_UP`: release the held modifier, 15 ms settle, drain capture.
  - `MOD_TAP`: press, 15 ms settle, release, 15 ms settle, drain
    capture. The firmware's debouncer must see both edges to register
    the toggle.
  - After all steps, exits 0.

The three `pick_*` functions follow the existing `pick_keymap`
pattern: explicit `if`-ladders, one entry per keymap, no auto-dispatch.

## CMake plumbing

`test/simavr/CMakeLists.txt` triple-loops over `(target, keymap, mode)`:

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
      set_tests_properties(simavr_${tgt}_${km}${suffix}
                           PROPERTIES TIMEOUT 30)
    endforeach()
  endforeach()
endforeach()
```

Existing case names are preserved (the `events` mode produces no
suffix). The timeout is bumped from 15 s to 30 s to give the
~50-step `string` cases comfortable headroom under slow simavr targets.

## CI

The `integration_test` job in `.github/workflows/asdf-firmware.yml` is
unchanged — it runs `bash make-targets.sh -t simavr_test`, which picks
up the larger matrix automatically through cmake.

Expected job runtime grows from ~30 s to ~90 s. Still well under the
job timeout.

## Authoring effort per keymap

For each of the six keymaps:

1. **Locate the caps-toggle coord** — read
   `src/Keymaps/asdf_keymap_<name>.c`, find which `(row, col)` in the
   plain matrix carries the shiftlock or capslock action. Add it to the
   keymap's data file as `modifier_caps_toggle`.

2. **Locate each key coord used in the script** — the canonical sentence
   needs: `t h i s a e o f k y m p`, space, period, and the Ctrl-M
   target. Plus whatever extra letters and characters the keymap's
   chosen `<mapname>` expansion uses.

3. **Author the `<name>_string_steps` array** — manually compute the
   expected byte for each `KEY` step based on the current modifier
   state and the keymap's matrices. For boot-CAPS keymaps the early
   letters are uppercase by default; the caps-toggle taps disable caps
   midway, so the `test` segment may produce lowercase.

4. **Author the `<name>_identity_test` literal** — copy the exact bytes
   the firmware emits during boot. Easiest path: run the runner once
   with `--mode identity --verbose` against a placeholder expected
   string, copy the captured bytes into the data file, re-run to
   confirm.

5. **Wire the new test data into the runner** — add three lookup
   entries to `pick_*` functions in `asdf_simavr_runner.c`.

Estimated effort: 30–60 min per keymap, dominated by matrix reading
and per-step expected-byte computation. The `_caps` variants inherit
most coords from their non-caps parents and copy heavily.

## Risks and open questions

- **Boot-CAPS keymap shift semantics.** For `apple2`, `sol`, and
  `ace1000`, the meaning of "shift held + letter" with caps already
  locked depends on the keymap's shift matrix. The test author must
  read each keymap's source to compute the expected `T`/`t`/`'` etc
  for the opening `<shift>t</shift>` step.

- **Underscore on the plain matrix.** Some keymaps put underscore on a
  shifted position. If the test author wants `_` in their `<mapname>`
  expansion, they must either insert explicit shift transitions or
  pick a different `<mapname>` spelling. The per-keymap `<mapname>`
  flexibility deliberately avoids forcing this.

- **`SIM_STEP_MOD_TAP` debounce timing.** The firmware needs to see
  both edges of the caps-toggle press to register the toggle. 15 ms
  settle before and after release matches the existing modifier
  pre-settle for SHIFT/CTRL events; it has already been validated for
  the modifier-bearing event tests. If shiftlock registration turns
  out to need longer than 15 ms in any keymap, the tap settle is
  trivial to extend in the runner.

- **Identity-string capture races.** If a keymap's print train is
  faster than the 1.2 s default capture window, the test passes
  early. If slower, it fails by length mismatch. Each keymap's
  `boot_scan_ticks` should be sized to outlast the longest print
  train it could ever emit.

## Out of scope

- Firmware changes of any kind.
- Auto-derivation of expected output from keymap matrices.
- New VCD or capture machinery beyond what `events` mode uses.
- Support for additional modifiers beyond shift, caps-toggle, ctrl.
- Restructuring of the per-keymap data file layout (one file per
  keymap, hand-authored — same as today).
