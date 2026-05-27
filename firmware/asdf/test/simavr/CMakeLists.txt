# Host-built test runner; never compiled with avr-gcc.

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
  ${CMAKE_CURRENT_SOURCE_DIR}/arch_io
  ${CMAKE_CURRENT_SOURCE_DIR}/harness
  ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_options(asdf_simavr_runner PRIVATE -Wall -Wextra -Wno-unused-parameter -std=c99)
target_link_libraries(asdf_simavr_runner PRIVATE simavr)

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

foreach(tgt ${SIMAVR_TARGETS})
  foreach(km ${SIMAVR_KEYMAPS})
    set(elf_path ${CMAKE_SOURCE_DIR}/build-${tgt}/src/asdf-v1.6.6-${tgt}.elf)
    add_test(
      NAME simavr_${tgt}_${km}
      COMMAND asdf_simavr_runner
              --target ${tgt} --keymap ${km}
              --elf ${elf_path}
              --vcd ${CMAKE_CURRENT_BINARY_DIR}/simavr_${tgt}_${km}.vcd
    )
    set_tests_properties(simavr_${tgt}_${km} PROPERTIES TIMEOUT 15)
  endforeach()
endforeach()
