cmake_minimum_required(VERSION 3.19)

set(KEYMAPFILE keymaps.txt)

# Set up the toolchain and other architecture specific details

if(ARCH MATCHES atmega328p)
  message(STATUS "setting up for atmega328p")
  set(AVF_H_FUSE 0xd9)
  set(AVR_L_FUSE 0xd2)
  set(AVR_MCU ${ARCH})

  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/generic-gcc-avr.cmake)
  set (ASDF_OUT_TARGET ${ASDF_TARGET}.elf)

elseif(ARCH MATCHES atmega2560)
  message(STATUS "setting up for atmega2560")
  set(AVF_H_FUSE 0x99)
  set(AVR_L_FUSE 0xe7)
  set(AVR_MCU ${ARCH})

  set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/generic-gcc-avr.cmake)
  set (ASDF_OUT_TARGET ${ASDF_TARGET}.elf)

endif()

project("asdf"
  VERSION 1.6.2
  DESCRIPTION "A customizable keyboard matrix controller for retrocomputers"
  LANGUAGES C)

set_property(GLOBAL PROPERTY C_STANDARD 99)

set(ASDF_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (ASDF_TARGET_NAME asdf-v${PROJECT_VERSION}-${ARCH})
set (ASDF_EXECUTABLE_TARGET_NAME ${ASDF_TARGET_NAME})

if(ARCH MATCHES test)
  add_subdirectory(test)
else()
  if((ARCH MATCHES atmega328p) OR (ARCH MATCHES atmega2560))
    set (ASDF_EXECUTABLE_TARGET_NAME ${ASDF_TARGET_NAME}.elf)

    function(custom_add_library EXECUTABLE_NAME)
      add_avr_library(${EXECUTABLE_NAME} ${ARGN})
    endfunction(custom_add_library)

    function(custom_add_executable EXECUTABLE_NAME)
      add_avr_executable(${EXECUTABLE_NAME} ${ARGN})
    endfunction(custom_add_executable)
  endif()

  add_subdirectory(src)
endif()
