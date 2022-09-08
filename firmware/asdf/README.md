# ASDF Keyboard scanning firmware

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

## Downloads:

Download the latest release of the firmware [here](https://osiweb.github.io/unified_retro_keyboard)

## Features:

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

* Virtual Output layer: Indicator LEDs and other direct logic-level hardware
 controls: supported via a virtual output layer. The keymaps (and certain
 functions such as shiftlock and capslock) may bind virtual outputs. The keymaps
 may then specify how the virtual outputs map to the available physical
 resources. This allows one keymap to place the capslock LED in one position,
 and another keymap may place the capslock LED elswhere. This simplifies support
 of multiple keyboards and keymaps.

## Compiling and configuration

### building using github actions:

If you have commit privileges to the repository, or if you have your own fork,
then push a commit to one of the following branches to trigger an automatic build:

- asdf-release
- asdf-build-test

This will generate a github page with downloadable hex files. You will find the
link to the github page in the "Actions" tab of the repository.  

### build using the make-build-dirs.sh script.


1) Run the make-targets.sh script

    Options:

            -x   Before creating a build directgory or virtual env, remove
                 any pre-existing version
            -t   add an architecture directory
            -a   Add all valid architecture directories
            -i   Build each specified target and install to dist directory
            -p   Install pipenv virtual environment for python scripts
            -c   Clean all artifacts
            -s   Copy dist files to sphinx directory

    Valid targets: atmega640, atmega1280, atmega2560

    - To create build directories for all targets and install the python virtual
      environment:

            bash make-targets.sh -ap

    - To create a a build directory for atmega1280, deleting any pre-existing directory:

            bash make-targets.sh -xt atmega2560

    - To remove and rebuild the python virtual environment:

            bash make-targets.sh -xp

    - To copy hex files to sphinx source tree (Requires the hex files
      to be installed in ./dist either from make install in each target
      directory, or 'bash make-targets.sh -ai')

            bash make-targets.sh -s


    - From a fresh checkout, build all targets and install hex files in
      sphinx tree for the download links:

            bash make-targets -pais

2) Enter the build directory for the desired architecture and build:
   Only needed if working on single target.  To make all targets at once,
   use the make-targest script described in step 1.

   Example: building the atmega2560 binary:

         cd build-atmega2560
         make

3) Build the sphinx documentation:

         cd docs
         pipenv run make html

### build manually (e.g., for development)

1) make and build directories for the desired architectures:

        mkdir build-atmega328p build-atmega2560

3) enter each build directory and run cmake for the desired architecture.

        cd build-atmega2560
        cmake .. -DARCH=atmega2560 -DCMAKE_BUILD_TYPE=RELEASE
   >    make

4) to run unit tests, the process is the same as above, with "test" as the
   target:

        mkdir build-test
        cd build-test
        cmake .. -DARCH=test
        cd src
        ctest

## Porting

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

