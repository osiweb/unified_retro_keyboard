ASDF Keyboard scanning firmware
-
This is a key matrix scanner that can detect and debounce keypress and release
events on a key matrix and either send codes or perform actions on keypress or
release. Keymaps are defined per application and may, for example, generate
ASCII codes, special keyscan codes, etc. The code is modular and may be
integrated into a larger system easily.

By default, the code supports any number of rows by 8 columns, which will give
the bestperformance on an 8-bit microcontroller. For more than 8 columns per
row, the row datatype would need to be changed to uint16_t to support 16
columns, etc.

The first supported application is a parallel ASCII output keyboard. If you want
serial or USB output, you can supply your own routines.

ASDF supports basic keyboard functionality and is configurable via a few
boolean variables, and via the key maps. The key maps are organized in
row,column format, with separate keymaps shift, capslock, and control-key modes.

Features:
--
* modifiers: A set of modifier keys may be specified. When only a few modifiers
  are used, this mechanism is a low-overhead alternative to a keymap overlay for
  keyboard states that only change the key codes produced by a keypress, such as
  SHIFT, CAPS LOCK, CONTROL, etc. The state of each modifier key is kept in a
  state variable. In most cases, pressing the key will set the value to a
  "pressed" state, and releasing will reset the value to an "unpressed" state.
  However some functions interact. For example, Shift Lock is sticky, so
  pressing Shift Lock toggles the Shift Lock state, and Releasing Shift Lock
  does nothing; but pressing "Shift" will reset the "Shift Lock" state.

  All modifier state variables are kept in a modifier state variable array. On a
  regular keypress, all of the modifier state variables are OR'ed together to
  produce an index into a value array for the standard key, to determine the
  value sent by the standard keypress.

* DIP switches: DIP switches are implemented by adding them into the key
  matrix, and providing activate() and deactivate() functions for the on and off
  positions.

* Multiple keymaps. DIP switches 0-4 select the map. The current version
  includes: 
  
  * (0): ADM-style ASCII keyboard 
  * (1): ADM-style ASCII keyboard (all caps)
  * (2): Apple 2 ASCII keyboard (upper/lower)
  * (3): Apple 2 ASCII keyboard (standard all caps)
  * (4): Sol-20 ASCII keyboard

* Debounce and Repeat functions: The main keyscan logic implements key
  debouncing. Multiple keys may be debounced simultaneously using a separate
  debounce counter for each key in the matrix.

* Repeat key and Autorepeat: This is provided by the repeat module. Autorepeat
  may be disabled or enabled either by configuration, by activate()/deactivate()
  functions, or other keyboard logic. Repeat and autorepeat only apply to the
  most recently pressed key.

* ASCII output - supported via output_value function.

* Virtual Output layer: Indicator LEDs and other direct logic-level hardware controls: supported via
 a virtual output layer.  The keymaps (and certain functions such as shiftlock and capslock) may bind virtual outputs.  The keymaps may then specify how the virtual outputs map to the available physical resources.  This allows one keymap to place the capslock LED in one position, and another keymap may place the capslock LED elswhere.  This simplifies support of multiple keyboards and keymaps.

Compiling and configuration
--
The source files are in the ./src directory. All build products — object files,
ELF binaries, hex files, map files, and the test executables — are written to the
./build directory. That directory must already exist; the makefiles will not
create it, so if your checkout does not have one, "mkdir build" first.

You will need GNU make, avr-gcc and avr-binutils to build the firmware, and the
host gcc to build the tests. All make commands are run from the ./src directory.

To build a firmware image for each supported target:

    cd src
    make cleanall ARCH=atmega2560 && make app ARCH=atmega2560
    make cleanall ARCH=atmega328p && make app ARCH=atmega328p

Each build produces ../build/asdf-\<arch\>-v\<version\>.elf, .hex and .map, and
prints a size report — for example, asdf-atmega2560-v0.9.hex. There is no upload
target in the makefiles; program the .hex file onto the microcontroller with
avrdude or the programmer of your choice.

The supported values of ARCH are the names of the architecture files in
./src/Arch, currently atmega2560 (the default) and atmega328p. A KEYMAP variable
selects which set of keymaps is compiled in; it defaults to "production" and
there is no reason to change it for a firmware build. VERSION supplies the
version stamped into the output filenames, and is set in Makefile.app; it does
not affect the compiled code, only what the artifacts are called. The
corresponding source revisions are tagged in git as asdf-v-\<version\>.

**Always run "make cleanall" when you change ARCH or KEYMAP.** The build selects
the target hardware and keymap set by copying files into place, rather than by
include paths or preprocessor flags:

    Arch/asdf_arch_$(ARCH).c                  ->  asdf_arch.c
    Arch/asdf_arch_$(ARCH).h                  ->  asdf_arch.h
    Keymaps/asdf_all_keymap_defs_$(KEYMAP).h  ->  asdf_keymap_defs.h

The rest of the sources include the generic names. The rules that make these
copies do not reliably notice that ARCH has changed, and only "cleanall" removes
the copies and forces them to be regenerated. Plain "make clean" is not enough:
it clears the object files but leaves the stale copies behind. The object files
are not qualified by architecture either, so they have to be cleared between
targets in any case.

Passing ARCH to cleanall, as shown above, scopes the deletion to that target's
own build products and leaves an image already built for another architecture
in place. A bare "make cleanall" would delete the default target's hex file.

Building with a stale copy in place fails loudly rather than producing a bad
image: either the compiler rejects register names that do not exist on the
selected part, or the linker rejects objects built for a different AVR
architecture.

You may also wish to edit your preferences in "asdf_config.h" to specify repeat
timings, optimize the debounce setting (if you have very bouncy keys), and
specify the character output buffer size (if you are implementing macros, etc.)

Testing
--
The unit tests use the Unity framework, vendored in ./test/unity. They build
against a host architecture stub, so they compile with the native gcc rather
than avr-gcc.

    cd src
    make cleanall && make test

Each suite is built as a standalone executable in ./build and run immediately as
part of the build, so make stops at the first suite that fails.

The tests build with ARCH=test and KEYMAP=test, and so overwrite the same
generated copies that a firmware build uses. Run "make cleanall" when switching
between "make test" and "make app" in either direction.

Known issue: the asdf\_keymaps and asdf\_virtual suites currently fail to link,
with an undefined reference to asdf\_repeat\_init, because asdf\_repeat.c is
missing from their dependency lists in Makefile.test. The asdf\_repeat,
asdf\_modifiers, asdf\_buffer and asdf\_hook suites pass.

Porting
--
This firmware was written in modular, portable C99, to be compiled with GCC
(avr-gcc for the Atmega). The hardware-sepecific files are in Arch/*.[ch]. To
adapt the Atmega port for additional hardware, enter the ./src/Arch directory,
and copy the files asdf_arch_atmega2560.c and asdf_arch_astmeg2560.h to new
filenames, and edit them to suit the hardware changes.

The firmware is designed to run from ROM on a slow vintage processor, with a
small RAM footprint, and is not re-entrant. It is designed to compile on small
architectures, or to be hand-translated to assembly on small processors, or to
an HDL for a CPLD or FPGA.

The code was written to favor readability over cleverness. While tempted to
optimize bit testing via bithacks, I opted for code simplicity since the
performance benefit was not there for 8-bit values.

To port to a new processor architecture, you may use the atmega2560 files as an
example, and create a pair of architecture-specific .c and .h files for the new
hardware, exporting the following functions:

- asdf_arch_init: initializes the CPU and hardware

- asdf_arch_read_row: given a row number, output the row to the matrix, and read
  all the columns on that row asdf_arch_send_code

- asdf_arch_send_code: given a key code, output the code to the computer, via
  serial, parallel, I2C, whatever is appropriate.

- asdf_arch_tick: true once every 1ms. This tests a flag set in an interrupt
  routine that is triggered every 1ms. The function return value is polled and a
  keyscan initiated when true. An alternative, if you have an RTOS, or even just
  a scheduler, would be to schedule the keyscan every 1 ms, rather than poll. In
  that case, this function is not needed, and the "superloop" in main.c would
  contain a call to the scheduler.
  
- asdf_arch_XXXX_set: The hardware provides a number of physical resources, such
  as TTL or tri-state outputs, which can be used to drive LEDs, TTL logic output
  lines, etc. These are driven by a virtual output layer. The virtual layer
  requires a function to set the state of the physical resources. One function
  is provided for each such resource. For example, if a TTL output is called
  OUT1, then the function asdf_arch_out1_set() must be defined. For now, the
  required devices are: 
- LED1, LED2, LED3 (LED outputs)
- OUT1, OUT2, OUT3 (TTL outputs)
- OUT1\_OPEN\_HI, OUT2\_OPEN\_HI, OUT3\_OPEN\_HI (Open collector outputs)
- OUT1\_OPEN\_LO, OUT2\_OPEN\_LO, OUT3\_OPEN\_LO (Open emitter outputs)

