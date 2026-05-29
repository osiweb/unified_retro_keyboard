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

## Downloads

The latest downloads are available at:

- **Download page**: <https://osiweb.github.io/unified_retro_keyboard/> — per-target `.hex` files and the release notes for every version.

<!-- **GitHub Releases**: <https://github.com/osiweb/unified_retro_keyboard/releases/latest> — the same `.hex` files plus `.elf` builds and a zipped copy of the docs site, attached as release assets. -->

## Supported keymaps:

The following keymaps may be selected via the DIP switches:

  * (0): ADM-style ASCII keyboard
  * (1): ADM-style ASCII keyboard (all caps)
  * (2): Apple 2 ASCII keyboard (upper/lower)
  * (3): Apple 2 ASCII keyboard (standard all caps)
  * (4): Sol-20 ASCII keyboard
  * (5): Franklin ACE 1000 keyboard (Thanks to Chris Ryu)


## Keyboard features

  * N-key rollover
  * Debouncing
  * Auto repeat and manual repeat.  Autorepeat may be enabled or diabled via DIP switch.
  * Positive or negative strobe polarity selection via DIP switch.

## Compiling and configuration

### Changing project name and version number.

- Edit the file "CMakeLists.txt"
- You will see a "project" section near the beginning of the file.

        project("asdf"
            VERSION 1.7.0
            DESCRIPTION "A customizable keyboard matrix controller for retrocomputers"
            LANGUAGES C)

- You can change the project name from "asdf" to whatever you like, and change the version number as you see fit.  These values will be used to name the resulting hex files, and also to name the download links in the GitHub page, if you choose to create one.

        project("my-keyboard"
            VERSION 1.0
            DESCRIPTION "My customized keyboard firmware"
            LANGUAGES C)

### building using github actions:

If you have commit privileges to the repository, or if you have your own fork,
then push a commit to one of the following branches to trigger an automatic build:

- main
- asdf-build-test

Pushing a `vX.Y.Z` tag also triggers the release pipeline (documentation deploy and GitHub Release with built `.hex` / `.elf` assets).

This will generate a github page with downloadable hex files. You will find the
link to the github page in the "Actions" tab of the repository.

You will also need to activate GitHub pages.  To do this:

- Click "Settings" at the top of this GitHub page, then along the menu bar on the left, select "Pages" in the "Code and Actions Section."
- In the "Build and deployment" section, select "Deploy from Branch"
- The "Branch" section will display a message that github pages is disabled.  Select the branch "gh-pages" from the dropdown, and the "disabled" message will be replaced with a message that the site is being built from "gh-pages".  Once you have triggered a build, you will see a message at the top of this page with a link to the live page.
-

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

    Valid targets: atmega88p, atmega168p, atmega328p, atmega640, atmega1280, atmega2560, test, simavr_test

    (`test` runs the host-side Unity unit tests; `simavr_test` runs
    simavr-driven integration tests against the built AVR ELFs.)

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

            bash make-targets.sh -pais

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

1) make build directories for the desired architectures:

        mkdir build-atmega328p build-atmega2560

2) enter each build directory and run cmake for the desired architecture.

        cd build-atmega2560
        cmake .. -DARCH=atmega2560 -DCMAKE_BUILD_TYPE=RELEASE
        make

3) to run unit tests, the process is the same as above, with "test" as the
   target:

        mkdir build-test
        cd build-test
        cmake .. -DARCH=test
        make && ctest

## Porting

This firmware was written in modular, portable C99, to be compiled with GCC
(avr-gcc for the Atmega). The hardware-specific files are in Arch/*.[ch]. To
adapt the Atmega port for additional hardware, enter the ./src/Arch directory,
and copy the files asdf_arch_atmega2560.c and asdf_arch_atmega2560.h to new
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
