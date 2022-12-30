cmake_minimum_required(VERSION 3.19)

set(KEYMAPFILE keymaps.txt)

# Set up the toolchain and other architecture specific details

set(ARCH_FAMILY_ATMEGA328P atmega328p)
set(ARCH_FAMILY_ATMEGA2560 atmega2560)

if(ARCH MATCHES atmega328p OR ARCH MATCHES atmega168p OR ARCH MATCHES atmega88p)
  set(FUSE_NOTES "Setting up for ${ARCH}: \n\n\
       Fuses: EXTENDED = 0xFF, HIGH = 0xdf, LOW = 0xd2\n\n\
       Brownout detect level:          111   (disabled) \n\
       Debug Wire (DWEN):              0     (disabled) \n\
       SPIEN:                          1     (enabled) \n\
       Watchdog (WDTON):               0     (disabled) \n\
       Save EEPROM (EESAVE):           0     (disabled) \n\
       Boot section / size (BOOTZ):    11    (size=128[88p,168p]/256[328p])) \n\
       Boot Reset Vector (BOOTRST):    0     (disabled) \n\
       Divide Clock by 8 (CKDIV8):     0     (disabled) \n\
       Clock out B0 (CKOUT)            0     (disabled) \n\
       Clock select (CKSEL3:0):       0010   (Ext Crystal 8.0 MHz) \n\
       Startup time (SUT):             01    (4.1 ms)\n\n")

  set(AVR_X_FUSE 0xff)
  set(AVR_H_FUSE 0xdf)
  set(AVR_L_FUSE 0xd2)

  set(AVR_MCU ${ARCH})
  set(ARCH_FAMILY ${ARCH_FAMILY_ATMEGA328P})
  set(ARCH_TYPE AVR)
  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/generic-gcc-avr.cmake)
  set (FINAL_TARGET ${TARGET}.elf)

elseif(ARCH MATCHES atmega640 OR ARCH MATCHES atmega1280 OR ARCH MATCHES atmega2560)
  set(FUSE_NOTES "Setting up for ${ARCH}: \n\n\
       Fuses: EXTENDED = 0xFD, HIGH = 0x98, LOW = 0xFD\n\n\
       Brownout detect level:          111   (disabled) \n\
       On-chip Debug (OCD):            0     (disabled) \n\
       JTAGEN:                         1     (enabled) \n\
       SPIEN:                          1     (enabled) \n\
       Watchdog (WDTON):               0     (disabled) \n\
       Save EEPROM (EESAVE):           0     (disabled) \n\
       Boot section / size (BOOTZ):    00    (size=4096/start=$1F000) \n\
       Boot Reset Vector (BOOTRST):    0     (enabled) \n\
       Divide Clock by 8 (CKDIV8):     0     (disabled) \n\
       Clock out E7 (CKOUT)            0     (disabled) \n\
       Clock select (CKSEL0:3):       0111   (Full Swing Osc.) \n\
       Startup time (SUT):             10    (4.1 ms)\n\n")

  set(AVR_X_FUSE 0xff)
  set(AVR_H_FUSE 0x99)
  set(AVR_L_FUSE 0xe7)

  set(AVR_MCU ${ARCH})
  set(ARCH_FAMILY ${ARCH_FAMILY_ATMEGA2560})
  set(ARCH_TYPE AVR)

  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/generic-gcc-avr.cmake)
  set (FINAL_TARGET ${TARGET}.elf)

endif()

project("asdf"
  VERSION 1.6.4
  DESCRIPTION "A customizable keyboard matrix controller for retrocomputers"
  LANGUAGES C)

set_property(GLOBAL PROPERTY C_STANDARD 99)

set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
message("SRC Dir is ${PROJECT_SRC_DIR}")

#set(PYTHON_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts)
#message("Python scripts Dir is ${PYTHON_SCRIPTS_DIR}")

set(DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs)
message("Documentation and web page directory is ${DOC_DIR}")

set (PROJECT_TARGET_NAME ${PROJECT_NAME}-v${PROJECT_VERSION}-${ARCH})
set (PROJECT_EXECUTABLE_TARGET_NAME ${PROJECT_TARGET_NAME})

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

# generate reStructuredText index file for project version: Note: this may be
# rebuilt for each target, but as long as all have the same project version, the
# build is idempotent, so no issues.
configure_file(${DOC_DIR}/source/_templates/index.rst.in ${DOC_DIR}/source/index.rst)
