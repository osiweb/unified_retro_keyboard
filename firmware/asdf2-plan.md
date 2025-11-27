# TURK: The Unified Reconfigurable Keyboard Project

## Executive Summary

TURK is the next generation of the Unified Retro Keyboard project, comprising:

- **ASDF** (Abstract Scanner Definition Framework) - The HSM-based firmware runtime
- **JKL;** (Jazzy Keyboard Language) - YAML-based keyboard configuration language

ASDF2 is a complete redesign of the ASDF keyboard firmware, replacing the current flat keymap/modifier system with a **Hierarchical State Machine (HSM)** model. The goal is to create a model embedded keyboard platform that:

- Demonstrates excellent software architecture patterns
- Provides an accessible configuration system via JKL;
- Supports exotic retrocomputing keyboards through hierarchical state machines
- Supports modern keyboard features (tap-dance, leader keys, mod-tap, layers)
- Maintains simplicity and embedded efficiency with a lean runtime

```
┌─────────────────────────────┐
│  JKL; Configuration         │  ← User-facing YAML dialect
│  keyboards/*.jkl            │     (Jazzy Keyboard Language)
└─────────────────────────────┘
            │ (build time)
┌───────────▼─────────────────┐
│  ASDF Runtime               │  ← HSM, keymaps, output abstraction
│  (Abstract Scanner          │
│   Definition Framework)     │
└─────────────────────────────┘
            │
┌───────────▼─────────────────┐
│  HAL                        │  ← Architecture-specific I/O
└─────────────────────────────┘

            TURK
   (The Unified Reconfigurable
        Keyboard Project)
```

**Key Design Decisions:**
- **HSM Runtime**: Non-keypress events bubble up through state hierarchy; replaces `asdf_modifiers.c`
- **Polymorphic Keymaps**: Dense, sparse, or single-override - generator picks optimal representation
- **Uniform Key Entries**: Each key has action+param for both press and release events
- **Compile-Time Optimization**: Python generator resolves JKL; inheritance and chooses keymap types at build time
- **JKL; Configuration**: External `.jkl` files replace C keymaps entirely
- **Protocol Abstraction**: Clean separation enables parallel ASCII, serial, USB HID outputs
- **Extensible Events**: HSM handles timers, serial/wireless input for expandable keyboards

---

## Current Architecture (ASDF1)

Understanding the existing code is essential for the redesign.

### Key Files to Study

| File | Purpose |
|------|---------|
| `src/asdf.h` | Action codes enum (`action_t`), keycode type definitions |
| `src/asdf.c` | Key scanner, debouncer, dispatch table (lines 188-850) |
| `src/asdf_keymaps.c` | Keymap registration, `asdf_keymaps_get_code()` lookup |
| `src/asdf_modifiers.c` | Modifier state machine (shift/caps/ctrl) |
| `src/asdf_hook.c` | Function hook system for extensibility |
| `src/asdf_virtual.c` | Virtual-to-physical device mapping |
| `src/Keymaps/asdf_keymap_classic_add_map.c` | Example dense matrix definition |
| `src/Arch/asdf_arch_atmega2560.c` | HAL implementation |

### Current Data Flow

```
Physical Matrix
     │
     ▼
asdf_arch_read_row()     ← Architecture-specific
     │
     ▼
asdf_keyscan()           ← Debouncing, change detection
     │
     ├─► keycode (0x00-0x7F) → asdf_put_code() → buffer
     │
     └─► action (0xA0+) → dispatch_table[action] → handler
     │
     ▼
main loop: asdf_next_code() → output_hook() → asdf_arch_send_code()
```

### Current Limitations

1. **Flat modifier system**: Only 4 fixed states (plain/shift/caps/ctrl)
2. **Split dispatch logic**: Keycodes (0x00-0x7F) and actions (0xA0+) handled differently
3. **C-only keymaps**: Require programming knowledge to modify
4. **No extensibility**: Cannot handle external events (serial, wireless keyboards)
5. **Single output format**: Parallel ASCII hardcoded

---

## ASDF2 Architecture

### System Layers

```
┌─────────────────────────────────────────────────────────────────┐
│                    YAML Configuration Layer                      │
│  keyboards/*.yaml → Python Generator → Generated C               │
└─────────────────────────────────────────────────────────────────┘
                            │ (build time)
┌───────────────────────────▼─────────────────────────────────────┐
│                    HSM Runtime Engine                            │
│  • O(1) keymap lookup via flattened per-state arrays            │
│  • Event dispatch with bubbling (timers, serial, etc.)          │
│  • State transitions with entry/exit actions                     │
│  • Timer pool for repeat/tap-hold                               │
│  • Replaces asdf_modifiers.c                                    │
└─────────────────────────────────────────────────────────────────┘
                            │
┌───────────────────────────▼─────────────────────────────────────┐
│                    Output Protocol Layer                         │
│  Abstraction between HSM and HAL for output format:             │
│  • Parallel ASCII (current)                                      │
│  • Serial/VT-100 (future)                                       │
│  • USB HID (future)                                             │
│  • Switch matrix emulation (future)                             │
└─────────────────────────────────────────────────────────────────┘
                            │
┌───────────────────────────▼─────────────────────────────────────┐
│                    Hardware Abstraction Layer                    │
│  • ATmega2560, ATmega328P, test harness                         │
└─────────────────────────────────────────────────────────────────┘
```

---

## Part 1: Hierarchical State Machine (HSM)

### 1.1 State Hierarchy Concept

```
ROOT (global)
 └── keyboard_select (via DIP switches)
      ├── ADM3A
      │    ├── base      ← default layer, all keys defined
      │    ├── shift     ← sparse overrides only
      │    ├── caps      ← sparse overrides only
      │    └── ctrl      ← sparse overrides only
      ├── Apple2
      │    └── ...
      └── Sol20
           └── ...
```

**Key behaviors:**
- **O(1) keymap lookup**: Each state has a complete keymap array (no runtime inheritance)
- **Events bubble up**: Unhandled non-keypress events propagate from leaf to root
- **Entry/exit actions**: Fire on state transitions
- **Timers**: Generic infrastructure for repeat, tap-hold, etc.
- **External events**: Serial/wireless input for keyboard expansion (e.g., add numpad)

### 1.2 Core Data Structures

```c
// === asdf_hsm.h ===

typedef uint8_t hsm_state_id_t;

#define HSM_STATE_NONE    0x00
#define HSM_STATE_ROOT    0x01
#define HSM_STATE_HANDLED 0xFE  // Event was consumed
#define HSM_STATE_SUPER   0xFF  // Delegate to parent

// Event types (keypresses are events)
typedef enum {
    HSM_EVT_NONE = 0,
    HSM_EVT_KEY_PRESS,
    HSM_EVT_KEY_RELEASE,
    HSM_EVT_TIMER,
    HSM_EVT_SERIAL_RX,      // Byte received on serial (wireless/expansion)
    HSM_EVT_ENTRY,
    HSM_EVT_EXIT,
    HSM_EVT_INIT,
} hsm_event_type_t;

// Event structure (8 bytes, fits in registers)
typedef struct {
    hsm_event_type_t type;   // 1 byte
    uint8_t row;             // 1 byte (or serial byte for HSM_EVT_SERIAL_RX)
    uint8_t col;             // 1 byte
    uint8_t param;           // 1 byte (timer ID, etc.)
    uint16_t timestamp;      // 2 bytes (for tap detection)
    uint16_t reserved;       // 2 bytes (alignment)
} hsm_event_t;

// Keymap entry: uniform action+param for press and release
typedef struct {
    uint8_t press_action;    // Action code for key press
    uint8_t press_param;     // Parameter for press action
    uint8_t release_action;  // Action code for key release
    uint8_t release_param;   // Parameter for release action
} keymap_entry_t;  // 4 bytes for 8-bit params

typedef struct {
    uint8_t press_action;
    uint8_t release_action;
    uint16_t press_param;    // 16-bit for extended keycodes (USB HID, Unicode)
    uint16_t release_param;
} keymap_entry_16_t;  // 6 bytes for 16-bit params

// Action codes (examples)
#define ACT_NONE        0x00  // No action
#define ACT_EMIT        0x01  // Emit param as keycode
#define ACT_TRANSITION  0x02  // Transition to state in param
#define ACT_TOGGLE      0x03  // Toggle state (for caps lock)
#define ACT_PULSE       0x04  // Pulse virtual output in param
#define ACT_SET_OUTPUT  0x05  // Set virtual output in param
#define ACT_CLEAR_OUTPUT 0x06 // Clear virtual output in param

// === Polymorphic Keymap Interface ===
// Different implementations for different state characteristics

struct keymap_s;  // Forward declaration

typedef keymap_entry_t (*keymap_lookup_fn)(const struct keymap_s *km, uint8_t row, uint8_t col);

typedef struct keymap_s {
    keymap_lookup_fn lookup;
    const void *data;
} keymap_t;

// State definition (stored in PROGMEM)
typedef struct {
    hsm_state_id_t id;
    hsm_state_id_t parent;              // For event bubbling (non-keypress)
    hsm_state_id_t initial_child;       // For composite states
    uint8_t flags;
    const keymap_t *keymap;             // Polymorphic keymap (see section 1.3)
    hsm_handler_fn event_handler;       // Handler for non-keypress events
} hsm_state_def_t;

// Event handler function type
// Returns: HSM_STATE_HANDLED, HSM_STATE_SUPER, or target state ID for transition
typedef hsm_state_id_t (*hsm_handler_fn)(const hsm_event_t *event);

#define HSM_FLAG_COMPOSITE    0x01  // Has child states
#define HSM_FLAG_ENTRY_ACTION 0x02  // Has entry action
#define HSM_FLAG_EXIT_ACTION  0x04  // Has exit action
```

### 1.3 Polymorphic Keymap Types

The keymap is polymorphic - different implementations for different state characteristics.
The generator chooses the optimal representation, or the user can specify it in YAML.

```c
// === asdf_hsm.c ===

static const hsm_state_def_t *current_state;

// Unified keymap lookup - delegates to implementation
void hsm_handle_key_event(uint8_t row, uint8_t col, uint8_t pressed) {
    const keymap_t *km = current_state->keymap;
    keymap_entry_t entry = km->lookup(km, row, col);

    if (pressed) {
        dispatch_action(entry.press_action, entry.press_param);
    } else {
        dispatch_action(entry.release_action, entry.release_param);
    }
}
```

#### 1.3.1 Dense Keymap (O(1))

Full array for states with most keys defined (base, shift, ctrl):

```c
typedef struct {
    const keymap_entry_t *entries;  // [ROWS * COLS] array
} keymap_dense_t;

keymap_entry_t lookup_dense(const keymap_t *km, uint8_t row, uint8_t col) {
    const keymap_dense_t *dense = km->data;
    return dense->entries[row * MATRIX_COLS + col];
}
```

#### 1.3.2 Single-Override Keymap (O(1))

For tap-dance/leader states that override exactly one key, with instant fallback:

```c
typedef struct {
    uint8_t row;
    uint8_t col;
    keymap_entry_t entry;
    const keymap_t *fallback;
} keymap_single_t;

keymap_entry_t lookup_single(const keymap_t *km, uint8_t row, uint8_t col) {
    const keymap_single_t *single = km->data;
    if (row == single->row && col == single->col) {
        return single->entry;
    }
    return single->fallback->lookup(single->fallback, row, col);
}
```

Cost: ~8 bytes per state instead of ~288 bytes for dense. Fallback is type-agnostic.

#### 1.3.3 Sparse Keymap (O(log n))

For states with few overrides (10-20 keys). Sorted list with binary search + fallback:

```c
typedef struct {
    const keymap_entry_t *entries;  // Sparse entries, sorted by (row<<4)|col
    uint8_t count;
    const keymap_t *fallback;
} keymap_sparse_t;

keymap_entry_t lookup_sparse(const keymap_t *km, uint8_t row, uint8_t col) {
    const keymap_sparse_t *sparse = km->data;
    // Binary search in sorted entries
    const keymap_entry_t *found = binary_search(sparse->entries, sparse->count, row, col);
    if (found) {
        return *found;
    }
    return sparse->fallback->lookup(sparse->fallback, row, col);
}
```

#### 1.3.4 Generator Selection

The generator chooses implementation based on state characteristics:

| Condition | Implementation |
|-----------|----------------|
| >50% keys defined | Dense |
| 1 key override | Single-override |
| 2-30 key overrides | Sparse |

User can override in YAML:
```yaml
states:
  my_layer:
    keymap_type: sparse  # Force sparse even if dense would be chosen
```

#### 1.3.5 Action Dispatch

```c
static void dispatch_action(uint8_t action, uint8_t param) {
    switch (action) {
        case ACT_NONE:
            break;
        case ACT_EMIT:
            asdf_put_code(param);
            break;
        case ACT_TRANSITION:
            hsm_transition_to(param);
            break;
        case ACT_TOGGLE:
            hsm_toggle_state(param);
            break;
        case ACT_PULSE:
            asdf_virtual_activate(param);
            break;
        // ... etc
    }
}
```

### 1.4 Event Dispatch (Bubbling for Non-Keypress Events)

Non-keypress events (timers, serial input, etc.) bubble up the state hierarchy:

```c
hsm_state_id_t hsm_dispatch_event(const hsm_event_t *event) {
    const hsm_state_def_t *state = current_state;

    // Bubble up until handled or root reached
    while (state != NULL) {
        if (state->event_handler != NULL) {
            hsm_state_id_t result = state->event_handler(event);

            if (result == HSM_STATE_HANDLED) {
                return result;  // Event consumed
            }
            if (result != HSM_STATE_SUPER) {
                // Transition requested
                hsm_transition_to(result);
                return result;
            }
        }
        // Bubble up to parent
        state = hsm_get_state_def(state->parent);
    }
    return HSM_STATE_NONE;  // Unhandled
}
```

This allows parent states to provide default handling for events like:
- Timer expiry (autorepeat at root level)
- Serial byte received (expansion keyboard handling)
- Entry/exit actions

### 1.5 State Transitions

For typical keyboard state changes (base → shift → base), transitions are between
sibling states, so the LCA algorithm simplifies. Entry/exit actions fire as needed:

```c
void hsm_transition_to(hsm_state_id_t target) {
    const hsm_state_def_t *source = current_state;
    const hsm_state_def_t *target_def = hsm_get_state_def(target);

    // Find Lowest Common Ancestor (LCA)
    hsm_state_id_t lca = hsm_find_lca(source->id, target);

    // Exit from source up to LCA
    const hsm_state_def_t *s = source;
    while (s->id != lca && s->id != HSM_STATE_NONE) {
        hsm_call_exit_action(s);
        s = hsm_get_state_def(s->parent);
    }

    // Build entry path from LCA to target
    hsm_state_id_t entry_path[HSM_MAX_DEPTH];
    uint8_t depth = 0;
    hsm_state_id_t t = target;
    while (t != lca && t != HSM_STATE_NONE) {
        entry_path[depth++] = t;
        t = hsm_get_state_def(t)->parent;
    }

    // Enter from LCA down to target (reverse order)
    while (depth > 0) {
        hsm_call_entry_action(hsm_get_state_def(entry_path[--depth]));
    }

    current_state = target_def;

    // Handle initial transition for composite states
    if ((target_def->flags & HSM_FLAG_COMPOSITE) &&
        target_def->initial_child != HSM_STATE_NONE) {
        hsm_transition_to(target_def->initial_child);
    }
}
```

### 1.6 Advanced Key Behaviors

The HSM naturally supports modern keyboard features through state composition.

#### 1.6.1 Tap-Dance

A key that does different things based on tap count. Each tap count is a sibling
state under the same parent, using single-override keymaps:

```
base (dense)
 ├── td_semicolon_1 (single-override → base)  tap 1: ';'
 ├── td_semicolon_2 (single-override → base)  tap 2: ':'
 └── td_semicolon_3 (single-override → base)  tap 3: emit ";)" sequence
```

- First press → transition to td_semicolon_1, start timer
- Second press before timeout → transition to td_semicolon_2, restart timer
- Timer expires → execute action for current tap count, return to base

All tap states are siblings - no deep nesting. Each state costs ~8 bytes (single-override).

```yaml
# YAML configuration
tap_dance:
  semicolon:
    key: { row: 3, col: 5 }
    timeout_ms: 200
    taps:
      1: ';'
      2: ':'
      3: [';', ')']  # sequence
```

#### 1.6.2 Leader Key

A key that starts a sequence mode, like vim's leader. Forms a trie of states:

```
base (dense)
 └── leader_active (single-override: leader key captures)
      ├── leader_d (single-override: 'd' captures)
      │    └── leader_dd (action: Ctrl+Shift+K)
      ├── leader_g (single-override: 'g' captures)
      │    ├── leader_gg (action: Ctrl+Home)
      │    └── leader_gd (action: goto definition)
      └── leader_timeout (returns to base)
```

Each level is a child because we track position in the sequence. Nodes with multiple
branches use sparse keymaps; single-path nodes use single-override.

```yaml
# YAML configuration
leader:
  key: { row: 0, col: 0 }
  timeout_ms: 500
  sequences:
    - keys: [d, d]
      action: { emit: [CTRL+SHIFT+K] }
    - keys: [g, g]
      action: { emit: [CTRL+HOME] }
    - keys: [g, d]
      action: { emit: [F12] }  # goto definition
```

#### 1.6.3 Mod-Tap (Hold vs Tap)

A key that acts as modifier when held, regular key when tapped:

```
base (dense)
 └── mt_pending (single-override: the mod-tap key)
      ├── [timer expires] → activate modifier, transition to mt_held
      └── [key released before timer] → emit tap key, return to base
```

```yaml
mod_tap:
  - key: { row: 4, col: 0 }
    hold: SHIFT
    tap: 'a'
    hold_threshold_ms: 200
```

### 1.7 Timer Pool

```c
#define HSM_MAX_TIMERS 4

typedef struct {
    uint16_t remaining_ticks;  // 0 = inactive
    uint8_t param;             // Passed in timer event
    hsm_state_id_t target;     // State to receive event
} hsm_timer_t;

static hsm_timer_t timers[HSM_MAX_TIMERS];

uint8_t hsm_timer_start(uint16_t duration_ms, uint8_t param, hsm_state_id_t target) {
    for (uint8_t i = 0; i < HSM_MAX_TIMERS; i++) {
        if (timers[i].remaining_ticks == 0) {
            timers[i].remaining_ticks = duration_ms;  // Assuming 1ms tick
            timers[i].param = param;
            timers[i].target = target;
            return i;
        }
    }
    return 0xFF;  // No timer available
}

void hsm_timer_cancel(uint8_t timer_id) {
    if (timer_id < HSM_MAX_TIMERS) {
        timers[timer_id].remaining_ticks = 0;
    }
}

// Called from main loop every 1ms
void hsm_timer_tick(void) {
    for (uint8_t i = 0; i < HSM_MAX_TIMERS; i++) {
        if (timers[i].remaining_ticks > 0) {
            if (--timers[i].remaining_ticks == 0) {
                hsm_event_t evt = {
                    .type = HSM_EVT_TIMER,
                    .param = timers[i].param,
                };
                // Dispatch to specific state or current
                hsm_dispatch(&evt);
            }
        }
    }
}
```

---

## Part 2: JKL; Configuration Language

JKL; (Jazzy Keyboard Language) is a YAML-based configuration language for TURK keyboards.
The `jkl` tool processes JKL; files and generates C code for the ASDF runtime.

### 2.1 Directory Structure

```
firmware/asdf/
├── keymaps/
│   ├── common/
│   │   ├── ascii_codes.yaml     # ASCII code definitions
│   │   ├── actions.yaml         # Action code definitions
│   │   └── base_keyboard.yaml   # Shared base configuration
│   ├── keyboards/
│   │   ├── classic.yaml         # ADM-3A style
│   │   ├── apple2.yaml          # Apple II
│   │   ├── sol20.yaml           # Sol-20
│   │   └── vt100.yaml           # VT-100 terminal
│   └── schema.yaml              # JSON Schema for validation
├── scripts/
│   └── jkl/                     # JKL; code generator tool
│       ├── __init__.py
│       ├── cli.py               # Command-line interface
│       ├── parser.py            # YAML parsing, include resolution
│       ├── validator.py         # Schema validation
│       ├── models.py            # Internal data model
│       ├── codegen.py           # C code generation
│       └── templates/           # Jinja2 templates
│           ├── keymap.c.j2
│           └── keymap.h.j2
└── src/
    └── generated/               # Generated C files (gitignored)
```

### 2.2 YAML Schema

```yaml
# keyboards/apple2.yaml - Complete example

version: "1.0"

metadata:
  name: apple2
  description: "Apple II keyboard with upper/lowercase"
  id_message: "[Keymap: Apple 2 (u/l case)]"

# Inherit common configuration
extends: common/base_keyboard.yaml

# Physical matrix dimensions
matrix:
  rows: 9
  cols: 8

# Firmware settings
settings:
  print_delay_ms: 40
  autorepeat:
    initial_delay_ms: 500
    repeat_interval_ms: 50

# Virtual device mappings
hardware:
  virtual_devices:
    power_led:
      virtual: VCAPS_LED
      physical: LED1
      function: none
      initial: on

    reset:
      virtual: VOUT1
      physical: OUT3_OPEN_HI
      function: pulse_short
      active: low

    clear_screen:
      virtual: VOUT2
      physical: OUT1_OPEN_LO
      function: pulse_long
      active: high

# Hierarchical state machine
states:
  # Root state for this keyboard
  apple2_root:
    type: composite
    initial: base
    on_entry:
      - action: print_id_message

  # Base layer - full keymap defined here
  # Each key specifies action+param for press and release
  # Simple keys use shorthand: 'a' expands to { press: [EMIT, 'a'] }
  base:
    parent: apple2_root
    type: leaf

    keymap:
      - row: 0
        keys:
          - NONE
          - { press: [TRANSITION, shift] }  # SHIFT key
          - { press: [TRANSITION, shift] }  # SHIFT key
          - NONE
          - ESC                              # Shorthand for { press: [EMIT, 0x1B] }
          - TAB
          - { press: [TRANSITION, ctrl] }   # CTRL key
          - '\\'
      - row: 1
        keys: [DEL, 'p', ';', '/', SPACE, 'z', 'a', 'q']
      - row: 2
        keys: [NONE, ',', 'm', 'n', 'b', 'v', 'c', 'x']
      - row: 3
        keys: ["'", 'k', 'j', 'h', 'g', 'f', 'd', 's']
      - row: 4
        keys: [NONE, 'i', 'u', 'y', 't', 'r', 'e', 'w']
      - row: 5
        keys:
          - NONE
          - { press: [PULSE, VOUT_RESET] }  # RESET button
          - { press: [PULSE, VOUT_CLEAR] }  # CLEAR button
          - REPEAT
          - { press: [TOGGLE, caps] }       # CAPS LOCK
          - '-'
          - ':'
          - '0'
      - row: 6
        keys: [CR, 'o', 'l', '.', HERE_IS, REPT, '=', '9']
      - row: 7
        keys: [LEFT, RIGHT, BREAK, '`', POWER, ']', '[', 'P']
      # Row 8 is DIP switches (defined separately)

  # Shift layer - inherits from base, overrides specific keys
  # Generator flattens this to complete keymap at build time
  shift:
    parent: base
    type: leaf

    keymap_overrides:
      - { row: 0, col: 1, press: [TRANSITION, shift], release: [TRANSITION, base] }
      - { row: 0, col: 2, press: [TRANSITION, shift], release: [TRANSITION, base] }
      - { row: 0, col: 7, key: '|' }
      - { row: 1, col: 1, key: 'P' }
      - { row: 1, col: 2, key: '+' }
      - { row: 1, col: 3, key: '?' }
      - { row: 2, col: 1, key: '<' }
      - { row: 2, col: 2, key: 'M' }
      - { row: 2, col: 3, key: 'N' }
      # ... remaining shift overrides (generator applies to full keymap)

  # Caps layer - sparse overrides for uppercase alpha
  caps:
    parent: base
    type: leaf

    keymap_overrides:
      - { row: 0, col: 4, press: [TOGGLE, caps] }  # Caps key returns to base
      # 26 alpha overrides: 'a'->'A', 'b'->'B', etc.
      # (Generator can expand 'uppercase_alpha: true' shorthand if desired)
      - { row: 1, col: 1, key: 'P' }
      - { row: 1, col: 7, key: 'Q' }
      # ... remaining alpha keys

  # Ctrl layer - sparse overrides for control codes
  ctrl:
    parent: base
    type: leaf

    keymap_overrides:
      - { row: 0, col: 6, press: [TRANSITION, ctrl], release: [TRANSITION, base] }
      # Control codes: 'a'->0x01, 'b'->0x02, etc.
      - { row: 1, col: 6, key: 0x01 }  # Ctrl-A
      - { row: 1, col: 7, key: 0x11 }  # Ctrl-Q
      # ... remaining ctrl overrides

# DIP switch configuration
dip_switches:
  row: 8
  switches:
    - { col: 0, action: MAPSEL_0 }
    - { col: 1, action: MAPSEL_1 }
    - { col: 2, action: MAPSEL_2 }
    - { col: 3, action: MAPSEL_3 }
    - { col: 6, action: STROBE_POLARITY }
    - { col: 7, action: AUTOREPEAT }

# Macro sequences
sequences:
  here_is:
    trigger: ACTION_HERE_IS
    on_hold: play_once
    steps:
      - { char: 'D', delay_ms: 20 }
      - { char: 'A', delay_ms: 20 }
      - { char: 'V', delay_ms: 20 }
      - { char: 'E' }
```

### 2.3 Inheritance Example

```yaml
# common/base_keyboard.yaml - Shared base configuration

version: "1.0"

metadata:
  name: base
  description: "Base keyboard configuration"

settings:
  print_delay_ms: 40
  autorepeat:
    initial_delay_ms: 500
    repeat_interval_ms: 50

# Common DIP switch layout
dip_switches:
  row: 8
  switches:
    - { col: 0, action: MAPSEL_0 }
    - { col: 1, action: MAPSEL_1 }
    - { col: 2, action: MAPSEL_2 }
    - { col: 3, action: MAPSEL_3 }

# Base state with common behaviors
states:
  root:
    type: composite
    on:
      key_press:
        - match: { flag: repeatable }
          action: start_repeat_timer
      key_release:
        - action: cancel_repeat_timer
      timer:
        - match: { timer: repeat }
          action: emit_repeat_key
```

Child keyboards use `extends:` to inherit and override:

```yaml
# keyboards/apple2.yaml
extends: common/base_keyboard.yaml

metadata:
  name: apple2  # Overrides base name

settings:
  print_delay_ms: 40  # Can override

states:
  apple2_root:
    parent: root  # Extends base root state
    # Apple II specific states...
```

---

## Part 3: jkl Code Generator Tool

### 3.1 Generator Pipeline

```
JKL; YAML Files
    │
    ▼
┌─────────────┐
│   Parser    │  ← Resolve includes, merge inheritance
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Validator  │  ← Check schema, validate references
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Flattener  │  ← Resolve inheritance, flatten keymaps per state
└──────┬──────┘
       │
       ▼
┌─────────────┐
│   Emitter   │  ← Generate C via Jinja2 templates
└──────┬──────┘
       │
       ▼
Generated C Files
```

### 3.2 CLI Interface

```bash
# Generate single keyboard
python -m jkl keyboards/apple2.yaml -o src/generated/

# Generate all keyboards
python -m jkl keyboards/*.yaml -o src/generated/

# Validate only (no output)
python -m jkl --validate keyboards/apple2.yaml

# Verbose mode with diagnostics
python -m jkl -v keyboards/apple2.yaml -o src/generated/
```

### 3.3 Generated C Output

```c
// === Generated: asdf_keymap_apple2.c ===

#include "asdf_hsm.h"
#include "asdf_keymap_apple2.h"

// Complete flattened keymap for base state (72 entries for 9x8 matrix)
// Each entry: { press_action, press_param, release_action, release_param }
static const PROGMEM keymap_entry_t apple2_base_keymap[] = {
    // Row 0
    { ACT_NONE, 0, ACT_NONE, 0 },                              // [0,0] unused
    { ACT_TRANSITION, APPLE2_STATE_SHIFT, ACT_NONE, 0 },       // [0,1] SHIFT
    { ACT_TRANSITION, APPLE2_STATE_SHIFT, ACT_NONE, 0 },       // [0,2] SHIFT
    { ACT_NONE, 0, ACT_NONE, 0 },                              // [0,3] unused
    { ACT_EMIT, 0x1B, ACT_NONE, 0 },                           // [0,4] ESC
    { ACT_EMIT, 0x09, ACT_NONE, 0 },                           // [0,5] TAB
    { ACT_TRANSITION, APPLE2_STATE_CTRL, ACT_NONE, 0 },        // [0,6] CTRL
    { ACT_EMIT, '\\', ACT_NONE, 0 },                           // [0,7] backslash
    // Row 1
    { ACT_EMIT, 0x7F, ACT_NONE, 0 },                           // [1,0] DEL
    { ACT_EMIT, 'p', ACT_NONE, 0 },                            // [1,1] p
    // ... remaining 64 entries
};

// Complete flattened keymap for shift state (inherits from base with overrides)
static const PROGMEM keymap_entry_t apple2_shift_keymap[] = {
    // Row 0 - note SHIFT keys now have release action
    { ACT_NONE, 0, ACT_NONE, 0 },                              // [0,0] unused
    { ACT_TRANSITION, APPLE2_STATE_SHIFT, ACT_TRANSITION, APPLE2_STATE_BASE }, // [0,1] SHIFT
    { ACT_TRANSITION, APPLE2_STATE_SHIFT, ACT_TRANSITION, APPLE2_STATE_BASE }, // [0,2] SHIFT
    { ACT_NONE, 0, ACT_NONE, 0 },                              // [0,3] unused
    { ACT_EMIT, 0x1B, ACT_NONE, 0 },                           // [0,4] ESC (inherited)
    { ACT_EMIT, 0x09, ACT_NONE, 0 },                           // [0,5] TAB (inherited)
    { ACT_TRANSITION, APPLE2_STATE_CTRL, ACT_NONE, 0 },        // [0,6] CTRL (inherited)
    { ACT_EMIT, '|', ACT_NONE, 0 },                            // [0,7] pipe (overridden)
    // Row 1
    { ACT_EMIT, 0x7F, ACT_NONE, 0 },                           // [1,0] DEL (inherited)
    { ACT_EMIT, 'P', ACT_NONE, 0 },                            // [1,1] P (overridden)
    // ... remaining entries (each state has complete 72-entry keymap)
};

// State definitions
static const PROGMEM hsm_state_def_t apple2_states[] = {
    [APPLE2_STATE_ROOT] = {
        .id = APPLE2_STATE_ROOT,
        .parent = HSM_STATE_ROOT,
        .initial_child = APPLE2_STATE_BASE,
        .flags = HSM_FLAG_COMPOSITE | HSM_FLAG_ENTRY_ACTION,
        .keymap = NULL,  // Composite states have no keymap
        .event_handler = apple2_root_handler,
    },
    [APPLE2_STATE_BASE] = {
        .id = APPLE2_STATE_BASE,
        .parent = APPLE2_STATE_ROOT,
        .initial_child = HSM_STATE_NONE,
        .flags = 0,
        .keymap = apple2_base_keymap,  // Complete flattened keymap
        .event_handler = NULL,         // No special event handling
    },
    [APPLE2_STATE_SHIFT] = {
        .id = APPLE2_STATE_SHIFT,
        .parent = APPLE2_STATE_ROOT,   // Parent for event bubbling only
        .initial_child = HSM_STATE_NONE,
        .flags = 0,
        .keymap = apple2_shift_keymap, // Complete flattened keymap
        .event_handler = NULL,
    },
    // ... remaining states (caps, ctrl)
};

// Keyboard registration
void setup_apple2_keymap(void) {
    hsm_register_keyboard(apple2_states, APPLE2_STATE_COUNT);
    asdf_set_print_delay(40);

    // Virtual device assignments
    asdf_virtual_assign(VCAPS_LED, PHYSICAL_LED1, V_NOFUNC, 1);
    asdf_virtual_assign(VOUT1, PHYSICAL_OUT3_OPEN_HI, V_PULSE_SHORT, 1);
    asdf_virtual_assign(VOUT2, PHYSICAL_OUT1_OPEN_LO, V_PULSE_LONG, 0);
}
```

---

## Part 4: Output Protocol Layer

The Output Protocol Layer sits between the HSM and the HAL, abstracting how
keycodes are transmitted to the host system. This allows the same HSM/keymap
logic to drive different output types without modification.

```
HSM (state machine, keymaps)
         │
         ▼
┌─────────────────────────┐
│  Output Protocol Layer  │  ← Abstraction for output format
│  • Parallel ASCII       │
│  • Serial/VT-100        │
│  • USB HID              │
│  • Switch Matrix Emu    │
└─────────────────────────┘
         │
         ▼
HAL (architecture-specific I/O)
```

**Future use cases (design later, abstraction now):**
- **VT-100**: Emit escape sequences for cursor keys, function keys
- **USB HID**: Track pressed keys, send HID reports on change
- **Switch Matrix Emulation**: Drive row/column outputs to emulate a different
  keyboard's switch matrix - allows one PCB to connect to multiple vintage computers

### 4.1 Protocol Interface

```c
// === asdf_output.h ===

typedef struct {
    void (*init)(void);
    void (*send_code)(uint16_t code);
    void (*send_event)(uint16_t code, uint8_t pressed);  // For HID-style protocols
    void (*send_sequence)(const uint8_t *data, uint8_t len);
    void (*flush)(void);
} asdf_output_protocol_t;

// Active protocol (set at init, could be DIP-switch selectable)
void asdf_output_set_protocol(const asdf_output_protocol_t *protocol);

// Send functions (delegate to active protocol)
void asdf_output_send(uint16_t code);
void asdf_output_send_pressed(uint16_t code, uint8_t pressed);
```

### 4.2 Parallel ASCII Protocol (Current)

```c
// === asdf_proto_parallel.c ===

static void parallel_send_code(uint16_t code) {
    if (code < 0x100) {
        asdf_arch_send_code((uint8_t)code);
    }
}

const asdf_output_protocol_t asdf_protocol_parallel = {
    .init = NULL,
    .send_code = parallel_send_code,
    .send_event = NULL,
    .send_sequence = NULL,
    .flush = NULL,
};
```

### 4.3 Future Protocols (Scaffolds)

```c
// === asdf_proto_vt100.c (future) ===

static void vt100_send_code(uint16_t code) {
    // Handle special keys with escape sequences
    switch (code) {
        case VT100_UP:    uart_send_string("\x1B[A"); break;
        case VT100_DOWN:  uart_send_string("\x1B[B"); break;
        case VT100_RIGHT: uart_send_string("\x1B[C"); break;
        case VT100_LEFT:  uart_send_string("\x1B[D"); break;
        default:
            if (code < 0x80) uart_send_byte((uint8_t)code);
    }
}

// === asdf_proto_hid.c (future) ===

static hid_report_t current_report;

static void hid_send_event(uint16_t code, uint8_t pressed) {
    if (pressed) {
        hid_add_key(&current_report, code);
    } else {
        hid_remove_key(&current_report, code);
    }
}

static void hid_flush(void) {
    usb_send_report(&current_report);
}
```

---

## Part 5: Implementation Phases

### Phase 1: HSM Core Engine
**Deliverables:**
- `src/asdf_hsm.h` - Data structures and interface
- `src/asdf_hsm.c` - O(1) keymap lookup, event dispatch, transitions, timers

**Tasks:**
1. Define HSM data structures (keymap_entry_t, hsm_state_def_t, hsm_event_t)
2. Implement O(1) keymap lookup: `hsm_handle_key_event(row, col, pressed)`
3. Implement action dispatch switch/table
4. Implement state transitions with entry/exit actions
5. Implement event bubbling for non-keypress events
6. Implement timer pool
7. Write unit tests using test harness

### Phase 2: Integration with Key Scanner
**Deliverables:**
- Modified `asdf.c` calling HSM for key events
- Remove `asdf_modifiers.c` (replaced by HSM)

**Tasks:**
1. Refactor `asdf_keyscan()` to call `hsm_handle_key_event()`
2. Connect HSM output to existing buffer system
3. Maintain backward compatibility during transition

### Phase 3: jkl Code Generator Tool
**Deliverables:**
- Complete `scripts/jkl/` package

**Tasks:**
1. Implement YAML parser with include resolution
2. Implement keymap flattener (resolve inheritance at build time)
3. Implement schema validator
4. Implement Jinja2 code emitter (generates complete keymaps per state)
5. Write generator tests

### Phase 4: YAML Schema and Common Files
**Deliverables:**
- `keymaps/schema.yaml`
- `keymaps/common/*.yaml`

**Tasks:**
1. Define complete JSON Schema
2. Create common ASCII codes file
3. Create common actions file
4. Create base keyboard template

### Phase 5: Migrate Existing Keymaps
**Deliverables:**
- `keymaps/keyboards/classic.yaml`
- `keymaps/keyboards/apple2.yaml`
- `keymaps/keyboards/sol20.yaml`
- `keymaps/keyboards/ace1000.yaml`

**Tasks:**
1. Convert each C keymap to YAML
2. Validate generated C matches original behavior
3. Run full test suite

### Phase 6: Output Protocol Layer
**Deliverables:**
- `src/asdf_output.h`
- `src/asdf_output.c`
- `src/Protocols/asdf_proto_parallel.c`

**Tasks:**
1. Define protocol interface
2. Implement protocol dispatch
3. Wrap existing parallel ASCII output

### Phase 7: Documentation
**Deliverables:**
- `docs/user-guide.md`
- `docs/yaml-reference.md`
- `docs/architecture.md`
- `docs/tutorials/`

**Tasks:**
1. Write user guide for creating keyboards
2. Document complete YAML schema
3. Document architecture for contributors
4. Create step-by-step tutorials

---

## Part 6: Memory Budget

### RAM Usage (ATmega2560, 8KB available)

| Component | ASDF1 | ASDF2 |
|-----------|-------|-------|
| Debounce counters | 128 B | 128 B |
| Key state bitmap | 16 B | 16 B |
| Modifier state | 4 B | - |
| HSM current state pointer | - | 2 B |
| Timer pool (4 timers) | - | 16 B |
| **Total** | ~150 B | ~162 B |

### Flash Usage (per keyboard, 9x8 matrix = 72 keys)

**Basic keyboard (4 states: base, shift, ctrl, caps):**

| Component | ASDF1 | ASDF2 (dense) |
|-----------|-------|---------------|
| Keymap per layer | 72 B (1 byte/key) | 288 B (4 bytes/key) |
| 4 layers total | ~288 B | ~1152 B |
| State definitions | - | ~48 B |
| Keymap interface overhead | - | ~32 B |
| Handler dispatch | ~256 B | ~64 B |
| **Total per keyboard** | ~550 B | ~1296 B |

**With polymorphic keymaps (example: 10 tap-dance keys):**

| Keymap Type | Size per state |
|-------------|----------------|
| Dense (base, shift, ctrl, caps) | 288 B (full array) |
| Single-override (tap-dance states) | ~8 B (row, col, entry, fallback ptr) |
| Sparse (26 overrides for caps) | ~108 B (entries + metadata) |

10 tap-dance keys × 3 taps each = 30 single-override states = ~240 B
vs 30 dense states = ~8640 B

**Summary:** Polymorphic keymaps keep advanced features memory-efficient:
- Dense for primary layers (base, shift, ctrl)
- Sparse for caps lock (26 alpha overrides) and similar
- Single-override for tap-dance/leader states (~8 B each)

---

## Part 7: Testing Strategy

### Unit Tests
- Keymap lookup for all types (dense, sparse, single-override)
- Fallback chain resolution across keymap types
- Action dispatch for all action types
- State transitions with entry/exit actions
- Timer operations
- Event bubbling for non-keypress events
- Tap-dance state transitions and timing
- Leader key trie traversal

### Integration Tests
- Full keyboard scan cycle
- Modifier state changes (base → shift → base)
- Output generation

### Regression Tests
- Compare generated output with ASDF1 for each keyboard
- Verify timing characteristics

### Hardware Tests
- Test on ATmega2560 target
- Verify electrical characteristics unchanged

---

## Success Criteria

1. **All existing keyboards work identically** - Bit-for-bit output compatibility
2. **YAML-only configuration** - No C code required to create keyboards
3. **New keyboard in < 1 hour** - Measured time to create VT-100 keyboard
4. **Clear documentation** - New contributor can understand architecture
5. **Extensible protocols** - Adding USB HID requires only new protocol file
6. **O(1) key event handling** - Single array lookup, no runtime inheritance

---

## Quick Start for Implementation

1. **Read these files first:**
   - `src/asdf.c` (especially dispatch table)
   - `src/asdf_keymaps.c` (keymap registration)
   - `src/asdf_modifiers.c` (to be replaced by HSM)
   - `src/Keymaps/asdf_keymap_classic_add_map.c` (matrix format)

2. **Start with Phase 1:**
   - Create `src/asdf_hsm.h` with data structures
   - Implement `hsm_handle_key_event()` with O(1) lookup
   - Implement `dispatch_action()` switch
   - Hand-code one test keyboard's keymap arrays
   - Test using existing test harness

3. **Build incrementally:**
   - Each phase should be testable independently
   - Maintain backward compatibility until final migration
   - Build generator after HSM runtime is proven
