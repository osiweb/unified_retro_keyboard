# ASDF2: Next-Generation Keyboard Firmware Architecture

## Executive Summary

ASDF2 is a complete redesign of the ASDF keyboard firmware, replacing the current flat keymap/modifier system with a **Hierarchical State Machine (HSM)** model. The goal is to create a model embedded keyboard platform that:

- Demonstrates excellent software architecture patterns
- Provides an accessible YAML-based configuration system
- Supports exotic retrocomputing keyboards through hierarchical state machines
- Rivals QMK in flexibility while maintaining simplicity and embedded efficiency

**Key Design Decisions:**
- **HSM Runtime**: Events bubble up, keycodes inherit down through state hierarchy
- **YAML Configuration**: External config files replace C keymaps entirely
- **Compile-Time Generation**: Python generates optimized C from YAML at build time
- **Sparse Storage**: Efficient representation for large/sparse key matrices
- **Protocol Abstraction**: Clean separation enables parallel ASCII, serial, USB HID outputs

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
2. **Dense matrices**: Waste space when matrices are sparse
3. **C-only keymaps**: Require programming knowledge to modify
4. **No event inheritance**: Each layer must define all keys
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
│  • Event dispatch with bubbling                                  │
│  • State transitions with entry/exit actions                     │
│  • Hierarchical keycode lookup                                   │
│  • Timer pool for repeat/tap-hold                               │
└─────────────────────────────────────────────────────────────────┘
                            │
┌───────────────────────────▼─────────────────────────────────────┐
│                    Output Protocol Layer                         │
│  • Parallel ASCII (current)                                      │
│  • Serial/VT-100 (future)                                       │
│  • USB HID (future)                                             │
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
- **Events bubble up**: Unhandled events propagate from leaf to root
- **Keycodes inherit down**: Child states only define differences from parent
- **Entry/exit actions**: Fire on state transitions
- **Timers**: Generic infrastructure for repeat, tap-hold, etc.

### 1.2 Core Data Structures

```c
// === asdf_hsm.h ===

typedef uint8_t hsm_state_id_t;

#define HSM_STATE_NONE    0x00
#define HSM_STATE_ROOT    0x01
#define HSM_STATE_HANDLED 0xFE  // Event was consumed
#define HSM_STATE_SUPER   0xFF  // Delegate to parent

// Event types
typedef enum {
    HSM_EVT_NONE = 0,
    HSM_EVT_KEY_PRESS,
    HSM_EVT_KEY_RELEASE,
    HSM_EVT_TIMER,
    HSM_EVT_ENTRY,
    HSM_EVT_EXIT,
    HSM_EVT_INIT,
} hsm_event_type_t;

// Event structure (8 bytes, fits in registers)
typedef struct {
    hsm_event_type_t type;   // 1 byte
    uint8_t row;             // 1 byte
    uint8_t col;             // 1 byte
    uint8_t param;           // 1 byte (timer ID, etc.)
    uint16_t timestamp;      // 2 bytes (for tap detection)
    uint16_t reserved;       // 2 bytes (alignment)
} hsm_event_t;

// Sparse key binding (4 bytes each, stored in PROGMEM)
typedef struct {
    uint8_t row;
    uint8_t col;
    uint8_t keycode;
    uint8_t flags;
} hsm_binding_t;

#define HSM_BIND_ON_PRESS    0x01
#define HSM_BIND_ON_RELEASE  0x02
#define HSM_BIND_REPEATABLE  0x04

// State definition (stored in PROGMEM)
typedef struct {
    hsm_state_id_t id;
    hsm_state_id_t parent;
    hsm_state_id_t initial_child;   // For composite states
    uint8_t flags;
    uint8_t handler_index;          // Index into handler function table
    const hsm_binding_t *bindings;  // Sparse key bindings (PROGMEM)
    uint8_t binding_count;
} hsm_state_def_t;

#define HSM_FLAG_COMPOSITE    0x01  // Has child states
#define HSM_FLAG_ENTRY_ACTION 0x02  // Has entry action
#define HSM_FLAG_EXIT_ACTION  0x04  // Has exit action
```

### 1.3 Event Dispatch (Bubbling)

```c
// === asdf_hsm.c ===

static hsm_state_id_t current_state;
static hsm_state_id_t current_leaf;  // Deepest active state

hsm_state_id_t hsm_dispatch(const hsm_event_t *event) {
    hsm_state_id_t state = current_leaf;

    // Bubble up until handled or root reached
    while (state != HSM_STATE_NONE) {
        const hsm_state_def_t *def = hsm_get_state_def(state);
        hsm_state_id_t result = hsm_call_handler(def, event);

        if (result == HSM_STATE_HANDLED) {
            return result;  // Event consumed
        }
        if (result != HSM_STATE_SUPER) {
            // Transition requested
            hsm_transition_to(result);
            return result;
        }
        // Bubble up to parent
        state = def->parent;
    }
    return HSM_STATE_NONE;  // Unhandled
}
```

### 1.4 Hierarchical Keycode Lookup

```c
// Lookup with inheritance: child → parent → grandparent → ...
asdf_keycode_t hsm_lookup_keycode(uint8_t row, uint8_t col) {
    hsm_state_id_t state = current_leaf;

    while (state != HSM_STATE_NONE) {
        const hsm_state_def_t *def = hsm_get_state_def(state);

        // Binary search in sorted sparse bindings
        const hsm_binding_t *binding = hsm_find_binding(
            def->bindings, def->binding_count, row, col
        );

        if (binding != NULL) {
            return pgm_read_byte(&binding->keycode);
        }

        // Not found in this state, try parent
        state = def->parent;
    }
    return ACTION_NOTHING;
}

// Binary search (bindings sorted by row<<4|col)
static const hsm_binding_t *hsm_find_binding(
    const hsm_binding_t *bindings,
    uint8_t count,
    uint8_t row,
    uint8_t col
) {
    if (!bindings || count == 0) return NULL;

    uint8_t key = (row << 4) | col;
    uint8_t lo = 0, hi = count;

    while (lo < hi) {
        uint8_t mid = lo + ((hi - lo) >> 1);
        uint8_t mid_key = (pgm_read_byte(&bindings[mid].row) << 4)
                        | pgm_read_byte(&bindings[mid].col);
        if (mid_key < key) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    if (lo < count) {
        uint8_t found_key = (pgm_read_byte(&bindings[lo].row) << 4)
                          | pgm_read_byte(&bindings[lo].col);
        if (found_key == key) {
            return &bindings[lo];
        }
    }
    return NULL;
}
```

### 1.5 State Transitions

```c
void hsm_transition_to(hsm_state_id_t target) {
    hsm_state_id_t source = current_leaf;

    // Find Lowest Common Ancestor (LCA)
    hsm_state_id_t lca = hsm_find_lca(source, target);

    // Exit from source up to LCA
    hsm_state_id_t s = source;
    while (s != lca && s != HSM_STATE_NONE) {
        hsm_call_exit_action(s);
        s = hsm_get_parent(s);
    }

    // Build entry path from LCA to target
    hsm_state_id_t entry_path[HSM_MAX_DEPTH];
    uint8_t depth = 0;
    s = target;
    while (s != lca && s != HSM_STATE_NONE) {
        entry_path[depth++] = s;
        s = hsm_get_parent(s);
    }

    // Enter from LCA down to target (reverse order)
    while (depth > 0) {
        hsm_call_entry_action(entry_path[--depth]);
    }

    current_leaf = target;

    // Handle initial transition for composite states
    const hsm_state_def_t *def = hsm_get_state_def(target);
    if ((def->flags & HSM_FLAG_COMPOSITE) && def->initial_child != HSM_STATE_NONE) {
        hsm_transition_to(def->initial_child);
    }
}
```

### 1.6 Timer Pool

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

## Part 2: YAML Configuration System

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
│   └── keymapgen/               # Python code generator
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
  base:
    parent: apple2_root
    type: leaf

    keymap:
      - row: 0
        keys: [NONE, SHIFT, SHIFT, NONE, ESC, TAB, CTRL, '\\']
      - row: 1
        keys: [DEL, 'p', ';', '/', SPACE, 'z', 'a', 'q']
      - row: 2
        keys: [NONE, ',', 'm', 'n', 'b', 'v', 'c', 'x']
      - row: 3
        keys: ["'", 'k', 'j', 'h', 'g', 'f', 'd', 's']
      - row: 4
        keys: [NONE, 'i', 'u', 'y', 't', 'r', 'e', 'w']
      - row: 5
        keys: [NONE, RESET, CLEAR, REPEAT, CAPS, '-', ':', '0']
      - row: 6
        keys: [CR, 'o', 'l', '.', HERE_IS, REPT, '=', '9']
      - row: 7
        keys: [LEFT, RIGHT, BREAK, '`', POWER, ']', '[', 'P']
      # Row 8 is DIP switches (defined separately)

    # Event handlers for this state
    on:
      key_press:
        - match: { action: SHIFT }
          transition: shift
        - match: { action: CTRL }
          transition: ctrl
        - match: { action: CAPS }
          action: toggle_caps_state

  # Shift layer - only differences from base
  shift:
    parent: base
    type: leaf

    # Sparse overrides (inherits rest from parent)
    keymap_overrides:
      - { row: 0, col: 7, key: '|' }
      - { row: 1, col: 1, key: 'P' }
      - { row: 1, col: 2, key: '+' }
      - { row: 1, col: 3, key: '?' }
      - { row: 2, col: 1, key: '<' }
      - { row: 2, col: 2, key: 'M' }
      - { row: 2, col: 3, key: 'N' }
      # ... remaining shift overrides

    on:
      key_release:
        - match: { action: SHIFT }
          transition: base

  # Caps layer - auto-uppercase transformation
  caps:
    parent: base
    type: leaf

    transform:
      uppercase_alpha: true  # 'a'-'z' → 'A'-'Z'

  # Ctrl layer - control code transformation
  ctrl:
    parent: base
    type: leaf

    transform:
      control_codes: true  # 'a'-'z' → 0x01-0x1A

    on:
      key_release:
        - match: { action: CTRL }
          transition: base

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

## Part 3: Python Code Generator

### 3.1 Generator Pipeline

```
YAML Files
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
│ Transformer │  ← Build internal model, resolve transforms
└──────┬──────┘
       │
       ▼
┌─────────────┐
│  Optimizer  │  ← Sort bindings for binary search
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
python -m keymapgen keyboards/apple2.yaml -o src/generated/

# Generate all keyboards
python -m keymapgen keyboards/*.yaml -o src/generated/

# Validate only (no output)
python -m keymapgen --validate keyboards/apple2.yaml

# Verbose mode with diagnostics
python -m keymapgen -v keyboards/apple2.yaml -o src/generated/
```

### 3.3 Generated C Output

```c
// === Generated: asdf_keymap_apple2.c ===

#include "asdf_hsm.h"
#include "asdf_keymap_apple2.h"

// Sparse bindings for base layer (sorted by row<<4|col)
static const PROGMEM hsm_binding_t apple2_base_bindings[] = {
    { .row = 0, .col = 1, .keycode = ACTION_SHIFT, .flags = HSM_BIND_ON_PRESS },
    { .row = 0, .col = 2, .keycode = ACTION_SHIFT, .flags = HSM_BIND_ON_PRESS },
    { .row = 0, .col = 4, .keycode = 0x1B,         .flags = HSM_BIND_ON_PRESS }, // ESC
    { .row = 0, .col = 5, .keycode = 0x09,         .flags = HSM_BIND_ON_PRESS }, // TAB
    { .row = 0, .col = 6, .keycode = ACTION_CTRL,  .flags = HSM_BIND_ON_PRESS },
    { .row = 0, .col = 7, .keycode = '\\',         .flags = HSM_BIND_ON_PRESS },
    // ... remaining bindings, sorted
};

// Sparse bindings for shift layer (only overrides)
static const PROGMEM hsm_binding_t apple2_shift_bindings[] = {
    { .row = 0, .col = 7, .keycode = '|',  .flags = HSM_BIND_ON_PRESS },
    { .row = 1, .col = 1, .keycode = 'P',  .flags = HSM_BIND_ON_PRESS },
    { .row = 1, .col = 2, .keycode = '+',  .flags = HSM_BIND_ON_PRESS },
    // ... only shifted keys
};

// State definitions
static const PROGMEM hsm_state_def_t apple2_states[] = {
    [APPLE2_STATE_ROOT] = {
        .id = APPLE2_STATE_ROOT,
        .parent = HSM_STATE_ROOT,
        .initial_child = APPLE2_STATE_BASE,
        .flags = HSM_FLAG_COMPOSITE | HSM_FLAG_ENTRY_ACTION,
        .handler_index = HANDLER_APPLE2_ROOT,
        .bindings = NULL,
        .binding_count = 0,
    },
    [APPLE2_STATE_BASE] = {
        .id = APPLE2_STATE_BASE,
        .parent = APPLE2_STATE_ROOT,
        .initial_child = HSM_STATE_NONE,
        .flags = 0,
        .handler_index = HANDLER_APPLE2_BASE,
        .bindings = apple2_base_bindings,
        .binding_count = sizeof(apple2_base_bindings) / sizeof(hsm_binding_t),
    },
    [APPLE2_STATE_SHIFT] = {
        .id = APPLE2_STATE_SHIFT,
        .parent = APPLE2_STATE_BASE,  // Inherits from base
        .initial_child = HSM_STATE_NONE,
        .flags = 0,
        .handler_index = HANDLER_APPLE2_SHIFT,
        .bindings = apple2_shift_bindings,
        .binding_count = sizeof(apple2_shift_bindings) / sizeof(hsm_binding_t),
    },
    // ... remaining states
};

// Keyboard registration
void setup_apple2_keymap(void) {
    hsm_register_keyboard(apple2_states, APPLE2_STATE_COUNT);
    asdf_set_print_delay(40);

    // Virtual device assignments
    asdf_virtual_assign(VCAPS_LED, PHYSICAL_LED1, V_NOFUNC, 1);
    asdf_virtual_assign(VOUT1, PHYSICAL_OUT3_OPEN_HI, V_PULSE_SHORT, 1);
    asdf_virtual_assign(VOUT2, PHYSICAL_OUT1_OPEN_LO, V_PULSE_LONG, 0);

    // Initial state
    asdf_modifier_capslock_activate(0);
}
```

---

## Part 4: Output Protocol Layer

### 4.1 Protocol Interface

```c
// === asdf_output.h ===

typedef struct {
    void (*init)(void);
    void (*send_code)(uint16_t code);
    void (*send_event)(uint16_t code, uint8_t pressed);  // For HID
    void (*send_sequence)(const uint8_t *data, uint8_t len);
    void (*flush)(void);
} asdf_output_protocol_t;

// Active protocol
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
- `src/asdf_hsm.c` - Event dispatch, transitions, timers

**Tasks:**
1. Define all HSM data structures
2. Implement event dispatch with bubbling
3. Implement state transitions with entry/exit
4. Implement timer pool
5. Write unit tests using test harness

### Phase 2: Sparse Keycode Lookup
**Deliverables:**
- Binary search lookup function
- Hierarchical fallthrough

**Tasks:**
1. Implement `hsm_find_binding()` with binary search
2. Implement `hsm_lookup_keycode()` with inheritance
3. Verify O(log n) lookup performance

### Phase 3: Integration with Key Scanner
**Deliverables:**
- Modified `asdf.c` generating HSM events

**Tasks:**
1. Refactor `asdf_keyscan()` to emit HSM events
2. Connect HSM output to existing buffer system
3. Maintain backward compatibility during transition

### Phase 4: Python Code Generator
**Deliverables:**
- Complete `scripts/keymapgen/` package

**Tasks:**
1. Implement YAML parser with include resolution
2. Implement schema validator
3. Implement Jinja2 code emitter
4. Write generator tests

### Phase 5: YAML Schema and Common Files
**Deliverables:**
- `keymaps/schema.yaml`
- `keymaps/common/*.yaml`

**Tasks:**
1. Define complete JSON Schema
2. Create common ASCII codes file
3. Create common actions file
4. Create base keyboard template

### Phase 6: Migrate Existing Keymaps
**Deliverables:**
- `keymaps/keyboards/classic.yaml`
- `keymaps/keyboards/apple2.yaml`
- `keymaps/keyboards/sol20.yaml`
- `keymaps/keyboards/ace1000.yaml`

**Tasks:**
1. Convert each C keymap to YAML
2. Validate generated C matches original behavior
3. Run full test suite

### Phase 7: Output Protocol Layer
**Deliverables:**
- `src/asdf_output.h`
- `src/asdf_output.c`
- `src/Protocols/asdf_proto_parallel.c`

**Tasks:**
1. Define protocol interface
2. Implement protocol dispatch
3. Wrap existing parallel ASCII output

### Phase 8: Documentation
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
| HSM current state | - | 4 B |
| Timer pool (4 timers) | - | 16 B |
| **Total** | ~150 B | ~170 B |

### Flash Usage (per keyboard)

| Component | ASDF1 | ASDF2 |
|-----------|-------|-------|
| Dense matrices (4 layers) | ~400 B | - |
| Sparse bindings | - | ~300 B |
| State definitions | - | ~80 B |
| Handler dispatch | 256 B | ~64 B |
| **Total** | ~650 B | ~450 B |

**Result:** ASDF2 uses ~30% less flash per keyboard due to sparse representation.

---

## Part 7: Testing Strategy

### Unit Tests
- HSM event dispatch
- State transitions
- Timer operations
- Sparse binding lookup
- Keycode inheritance

### Integration Tests
- Full keyboard scan cycle
- Modifier state changes
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
6. **Memory efficient** - Less flash usage than ASDF1

---

## Quick Start for Implementation

1. **Read these files first:**
   - `src/asdf.c` (especially lines 188-850, dispatch table)
   - `src/asdf_keymaps.c` (keymap registration)
   - `src/Keymaps/asdf_keymap_classic_add_map.c` (matrix format)

2. **Start with Phase 1:**
   - Create `src/asdf_hsm.h` with data structures
   - Implement basic event dispatch in `src/asdf_hsm.c`
   - Test using existing test harness

3. **Build incrementally:**
   - Each phase should be testable independently
   - Maintain backward compatibility until final migration
