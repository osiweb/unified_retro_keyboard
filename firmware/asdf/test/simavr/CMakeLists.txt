# Host-built test runner; never compiled with avr-gcc.

add_executable(asdf_simavr_runner
  asdf_simavr_runner.c
  arch_io/asdf_simavr_io.c
)
target_include_directories(asdf_simavr_runner PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/arch_io
)
target_compile_options(asdf_simavr_runner PRIVATE -Wall -Wextra -Wno-unused-parameter -std=c99)
target_link_libraries(asdf_simavr_runner PRIVATE simavr)
