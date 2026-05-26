# Host-built test runner; never compiled with avr-gcc.

add_executable(asdf_simavr_runner asdf_simavr_runner.c)
target_compile_options(asdf_simavr_runner PRIVATE -Wall -Wextra -Wno-unused-parameter -std=c99)
target_link_libraries(asdf_simavr_runner PRIVATE simavr)
