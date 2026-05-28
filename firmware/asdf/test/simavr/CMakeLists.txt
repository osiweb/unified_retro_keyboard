# Host-built test runner; never compiled with avr-gcc.

# Locate simavr and libelf. Headers live under /usr/include (apt) or
# /usr/local, /opt/local, /opt/homebrew (manual / MacPorts / Homebrew).
# Override with -DSIMAVR_ROOT=<prefix> or -DCMAKE_PREFIX_PATH=<prefix>.
find_path(SIMAVR_INCLUDE_DIR simavr/sim_avr.h
  HINTS ${SIMAVR_ROOT}/include
        /usr/local/include /opt/local/include /opt/homebrew/include)
find_library(SIMAVR_LIBRARY NAMES simavr
  HINTS ${SIMAVR_ROOT}/lib
        /usr/local/lib /opt/local/lib /opt/homebrew/lib)
find_path(ELF_INCLUDE_DIR libelf.h
  PATH_SUFFIXES libelf
  HINTS /usr/local/include /opt/local/include /opt/homebrew/include)
find_library(ELF_LIBRARY NAMES elf
  HINTS /usr/local/lib /opt/local/lib /opt/homebrew/lib)
if(NOT SIMAVR_INCLUDE_DIR OR NOT SIMAVR_LIBRARY)
  message(FATAL_ERROR
    "simavr not found. Install libsimavr-dev (apt) or build from source and "
    "pass -DSIMAVR_ROOT=<prefix>.")
endif()
if(NOT ELF_LIBRARY)
  message(FATAL_ERROR
    "libelf not found. Install libelf-dev (apt) or libelf (MacPorts/Homebrew).")
endif()

add_executable(asdf_simavr_runner
  asdf_simavr_runner.c
  arch_io/asdf_simavr_io.c
  harness/capture.c
  harness/sim.c
  harness/io.c
  harness/run.c
  harness/sim_assert.c
  harness/vcd.c
)
target_include_directories(asdf_simavr_runner PRIVATE
  ${SIMAVR_INCLUDE_DIR}
  ${ELF_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/arch_io
  ${CMAKE_CURRENT_SOURCE_DIR}/harness
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_options(asdf_simavr_runner PRIVATE -Wall -Wextra -Wno-unused-parameter -std=c99)
target_link_libraries(asdf_simavr_runner PRIVATE ${SIMAVR_LIBRARY} ${ELF_LIBRARY})

enable_testing()

add_executable(asdf_sim_test_capture
  harness/capture.c
  harness/test_capture.c
)
target_include_directories(asdf_sim_test_capture PRIVATE harness)
# -UNDEBUG so assert() is live even under the default RELEASE build,
# otherwise this test would silently always pass.
target_compile_options(asdf_sim_test_capture PRIVATE -Wall -Wextra -std=c99 -UNDEBUG)
add_test(NAME unit_capture COMMAND asdf_sim_test_capture)

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
      set_tests_properties(simavr_${tgt}_${km}${suffix} PROPERTIES TIMEOUT 30)
    endforeach()
  endforeach()
endforeach()
