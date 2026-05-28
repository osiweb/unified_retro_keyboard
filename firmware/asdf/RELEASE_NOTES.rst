ASDF Firmware Release Notes
===========================

Entries are listed most recent first. Highlights summarize the impact. Details give the implementation notes and other supporting changes.

Version 1.7.0 (Release)
-----------------------

This release includes fixes for bugs that could cause incorrect key
behaviors and could crash Sol-20 and Franklin keymaps. If you have 1.6.5, you
should upgrade the firmware.

Highlights
~~~~~~~~~~

- *Bug Fix*: On keymap switching, ensure virtual outputs start in the correct state
- *Feature*: Added integration testing based on simavr.

Details
~~~~~~~

- *Bug Fix*: ``asdf_keymaps_switch()`` now reapplies virtual outputs for the new map; added tests for the keymap switching path.
- *Bug Fix*: Fixed a ``printf`` format issue in the keymap code.
- *Feature*: Added matrix and DIP-switch injection, output capture, VCD trace capture, and per-keymap simavr tests.
- *Build*: Split CI into firmware build, host unit test, integration test, documentation, and release jobs.
- *Build*: Added portable simavr/libelf detection and CI install steps for ``libelf-dev``.
- *Build*: Added ``version.sh`` so scripts and CI read the project version from ``CMakeLists.txt``.
- *Build*: Tag builds verify that ``vX.Y.Z`` matches the CMake project version before publishing release assets.

Version 1.6.6 (Interim)
-----------------------

Highlights
~~~~~~~~~~

- *Bug Fix*: Fixed a serious keymap lookup bug that could cause Sol-20 and Franklin keymaps to fail
- *Feature*: Added firmware support for Franklin ACE 1000 replacement keyboards.
- *Feature*: Added a configurable row-scanner hook for new keyboard hardware.

Details
~~~~~~~

- *Bug Fix*: Fixed keymap lookup against the wrong modifier index in
  ``keymaps.c:get_codes()`` that could cause incorrect keymappings, and could cause
  keymaps with more rows or higher keymap numbers (Sol-20 or Franklin Ace) to
  crash.
- *Feature*: Added the Franklin ACE 1000 keymap and updated the README feature list.
- *Feature*: Added ``asdf_arch_set_row_scanner()`` and default row scanner declarations in the architecture headers.
- *Build*: Removed unused row/column list plumbing and an unused keymap helper.

Version 1.6.5 (2023-01-02)
--------------------------

Highlights
~~~~~~~~~~

- *Feature*: Added firmware builds for additional AVR targets.
- *Feature*: Added Videx-style Apple key bindings and self-test strings.
- *Build*: Streamlined multi-target firmware builds.

Details
~~~~~~~

- *Feature*: Added support for ATmega88P, ATmega168P, ATmega640, and ATmega1280 targets.
- *Feature*: Added a user-bindable function for printing ASCII strings from keymaps.
- *Feature*: Added Videx-style Apple bindings, Apple keymap character tests, and an Applesoft keyword test sequence.
- *Bug Fix*: Corrected Videx key mappings and Apple test program bindings.
- *Build*: Reworked CMake target factor out processor family from the MCU.
- *Build*: Fixed install directory handling and ``make-targets.sh`` issues.

Version 1.6.4 (2022-12-27)
--------------------------

Highlights
~~~~~~~~~~

- *Build*: Added automated firmware builds and documentation publishing.
- *Build*: Added Sphinx documentation with firmware download links.
- *Bug Fix*: Fixed build issues with newer GCC versions.

Details
~~~~~~~

- *Build*: Added the firmware GitHub Actions workflow and GitHub Pages deployment support.
- *Build*: Improved ``make-targets.sh`` and the firmware README build instructions.
- *Build*: Added generated documentation index files for versioned firmware downloads.
- *Bug Fix*: Fixed a GCC 11.3 compiler warning path.
- *Bug Fix*: Added missing keymap setup files and missing keymap headers needed by tests and builds.

Version 1.6.3 (2021-12-05)
--------------------------

Highlights
~~~~~~~~~~

- *Bug Fix*: Fixed slow repeat behavior on some keys.
- *Feature*: Added keyboard identification and self-test messages.
- *Feature*: The Sol-20 layout can send its ID message with Control-0.

Details
~~~~~~~

- *Feature*: Added configurable output rate for generated messages.
- *Feature*: Added ``asdf_arch_delay_ms()`` for millisecond delays.
- *Feature*: Added Apple II keyboard ID and test message bindings.
- *Feature*: Bound the Sol-20 ID message to Control-0.
- *Bug Fix*: A bit test optimization was causing slow key repeat on some matrix
  columns. Removed.
- *Bug Fix*: Fixed the ATmega2560 millisecond delay routine.
- *Bug Fix*: ``asdf_buffer_get()`` fixed to validate the buffer handle before use.

Version 1.6.2 (2021-11-29)
--------------------------

Highlights
~~~~~~~~~~

- *Bug Fix*: Fixed Apple II CAPS power LED behavior.
- *Feature*: Added Apple II CAPS and printing behavior.
- *Bug Fix*: Fixed startup problems from the keymap rewrite.

Details
~~~~~~~

- *Feature*: Added Apple II CAPS map behavior and related printing support.
- *Bug Fix*: Fixed the Apple CAPS power LED so it stays on.
- *Bug Fix*: Initialized buffers before other firmware subsystems.
- *Bug Fix*: Fixed extra indirection and library-related indirection errors.
- *Build*: Added CMake templates for generated keymap setup files.

Version 1.6.1 (2021-11-28)
--------------------------

Highlights
~~~~~~~~~~

- *Feature*: Restored the Apple II upper/lowercase layout.
- *Bug Fix*: Cleaned up initialization after the keymap rewrite.

Details
~~~~~~~

- *Feature*: Added back the Apple II upper/lowercase map after the keymap scheme change.
- *Bug Fix*: Removed redundant reset code and unused declarations.
- *Bug Fix*: Removed ``arch_init`` from ``main()``.
- *Build*: Updated generated keymap setup handling for the new layout.

Version 1.6.0 (2021-11-28)
--------------------------

Highlights
~~~~~~~~~~

- *Feature*: Reworked keymap definitions for easier layout maintenance.
- *Build*: Added generated setup files for keyboard layouts.
- *Build*: Updated the tests for the new layout system.

Details
~~~~~~~

- *Feature*: Replaced the old keymap table setup with per-keymap registration files.
- *Feature*: Added generated ``NUM_KEYMAPS`` and keymap table setup.
- *Build*: Fixed test CMake files and compile flags for the new scheme.
- *Bug Fix*: Fixed Sol map comments and keymap initialization cleanup items found during the conversion.

Version 1.5.1 (2021-11-08)
--------------------------

Highlights
~~~~~~~~~~

- *Bug Fix*: Fixed an ATmega328P output bug where OUT2 changed OUT1.
- *Build*: Cleaned up firmware file names and test build settings.

Details
~~~~~~~

- *Bug Fix*: Corrected the ATmega328P OUT2 output path, which was changing OUT1.
- *Build*: Changed build artifact names to place the version before the architecture.
- *Build*: Fixed CMake test files and C compile flags.

Version 1.5 (2021-03-04)
------------------------

Highlights
~~~~~~~~~~

- *Feature*: First tagged ASDF firmware release, with selectable layouts for ADM-style ASCII, Apple II, and Sol-20 keyboards.
- *Feature*: Added the virtual output layer for LEDs and TTL output signals.
- *Build*: Replaced the Makefile build flow with CMake.
- *Feature*: Added firmware support for ATmega2560 controllers and early OSI 542 scanning.

Details
~~~~~~~

- *Feature*: Added runtime keymap switching through DIP-switch selection.
- *Feature*: Added per-key debounce counters, repeat, autorepeat, and modifier handling.
- *Feature*: Added Apple II and Sol-20 keymaps, ASCII NULL, Shift-RESET clear screen, and Caps Lock naming cleanup.
- *Feature*: Added virtual LEDs, virtual outputs, hi-z-when-low outputs, and long/short pulse outputs.
- *Feature*: Split physical resources into ``asdf_physical.[ch]`` and added hooks for scanner, output, and initialization behavior.
- *Feature*: Added ATmega2560 architecture files and initial OSI 542 keyboard scan support.
- *Bug Fix*: Reinitialized repeat state and reset modifiers on keymap switch.
- *Bug Fix*: Fixed ATmega2560 row settling time and corrected several Sol-20 signal assignments.
- *Bug Fix*: Fixed long-delay handling so millisecond delays use ``_delay_ms()``.
- *Build*: Replaced the Makefile-only build with CMake.
- *Build*: Added unit tests for multiple keymaps and virtual outputs.
