ASDF Keyboard scanning firmware
-
The ASDF (Auto Scan by DF) firmware is a key matrix scanner that can detect and
debounce keypress and release events on a key matrix and either send codes or
perform actions on keypress or release. Keymaps are defined per application and
may, for example, generate ASCII codes, special keyscan codes, etc. The code is
modular and may be integrated into a larger system easily.

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
  keyboard states that only change the key value, such as SHIFT, CAPS LOCK, CONTROL,
  etc. The state of each modifier key is kept in a state variable. In most
  cases, pressing the key will set the value to a "pressed" state, and releasing
  will reset the value to an "unpressed" state. However some functions interact.
  For example, Shift Lock is sticky, so pressing Shift Lock toggles the Shift
  Lock state, and Releasing Shift Lock does nothing; but pressing "Shift" will
  reset the "Shift Lock" state.

  All modifier state variables are kept in a modifier state variable array. On a
  regular keypress, all of the modifier state variables are OR'ed together to
  produce an index into a value array for the standard key, to determine the
  value sent by the standard keypress.

* DIP switches: DIP switches are implemented by adding them into the key
  matrix, and providing activate() and deactivate() functions for the on and off
  positions.

* Multiple keymaps. DIP switches 0-4 select the map. The current version
  includes: 
  (0): ADM-style ASCII keyboard 
  (1): ADM-style ASCII keyboard (all caps)
  
* Indicators: Controlled via activate() and deactivate() functions for the various keys.

* Debounce and Repeat functions: The main keyscan logic implements key
  debouncing. Multiple keys may be debounced simultaneously using a separate
  debounce counter for each key in the matrix.

* Repeat key and Autorepeat: This is provided by the repeat module. Autorepeat
  may be disabled or enabled either by configuration, by activate()/deactivate()
  functions, or other keyboard logic. Repeat and autorepeat only apply to the
  most recently pressed key.

* (Future feature) NVRAM: For architectures that support EEPROM or other non-volatile storage,
  configuration parameters are stored in non-volatile storage to survive a power
  cycle.

* ASCII output - supported via output_value function.

* (Future feature) Serial, USB CDC, USB HID interfaces - supportable via output_value function.

* Indicator LEDs and other direct logic-level hardware controls: supported via
  per-key activate/deactivate functions, and also via hooks to standard key
  functions.

Compiling and configuration
--
The source files are in the ./src directory.  The final build files go in the ./build directory.

To build, enter the ./src directory. You should be able to build a binary and
hex file suitable for programming a microcontroller by typing "Make". You may
edit the Makefile to specify your target platform (default is Atmega328P ASCII
controller). You may also wish to edit your preferences in "asdf_config.h" to
specify repeat timings, optimize the debounce setting (if you have very bounce
keys), and specify the character output buffer size (if you are implementing
macros, etc.)

Porting
--
This firmware was written in modular, portable C99, to be compiled with GCC
(avr-gcc for the Atmega). The hardware-sepecific files are in Arch/*.[ch]. To
adapt the Atmega port for additional hardware, enter the ./src/Arch directory,
and copy the files asdf_arch_atmega328p.c and asdf_arch_astmega328p.h to new
filenames, and edit them to suit the hardware changes.

The firmware is designed to run from ROM on a slow vintage processor, with a
small RAM footprint, and is not re-entrant. It is designed to compile on small
architectures, or to be hand-translated to assembly on small processors, or to
an HDL for a CPLD or FPGA.

The code was written to favor readability over cleverness. While tempted to
optimize bit testing via bithacks, I opted for code simplicity since the
performance benefit was not there for 8-bit values.

To port to a new processor architecture, you may use the atmega328p files as an
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

