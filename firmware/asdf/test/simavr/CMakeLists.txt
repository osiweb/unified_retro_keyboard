# Host-built test runner; never compiled with avr-gcc.

add_executable(asdf_simavr_runner
  asdf_simavr_runner.c
  arch_io/asdf_simavr_io.c
  harness/capture.c
)
target_include_directories(asdf_simavr_runner PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/arch_io
  ${CMAKE_CURRENT_SOURCE_DIR}/harness
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
