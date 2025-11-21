configure_file(${PROJECT_SRC_DIR}/Arch/asdf_arch_test.h ${CMAKE_CURRENT_BINARY_DIR}/asdf_arch.h COPYONLY)

list(APPEND C_FLAGS
  "-std=c99"
  "-Wall"
  "-Wextra"
  "-Wpointer-arith"
  "-Wcast-align"
  "-Wwrite-strings"
  "-Wswitch-default"
  "-Wunreachable-code"
  "-Winit-self"
  "-Wmissing-field-initializers"
  "-Wno-unknown-pragmas"
  "-Wstrict-prototypes"
  "-Wundef"
  "-Wold-style-definition"
  "-g"
  )

list(APPEND TEST_INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PROJECT_SRC_DIR}
  ${PROJECT_SRC_DIR}/Arch
  )

add_library(unity
  STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/unity/unity.c
  )

target_include_directories(unity
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/unity
  )


add_library(asdf_core
  STATIC
  asdf_keymap_table.c
  ${PROJECT_SRC_DIR}/asdf.c
  ${PROJECT_SRC_DIR}/asdf_buffer.c
  ${PROJECT_SRC_DIR}/asdf_hook.c
  ${PROJECT_SRC_DIR}/asdf_keymaps.c
  ${PROJECT_SRC_DIR}/asdf_modifiers.c
  ${PROJECT_SRC_DIR}/asdf_physical.c
  ${PROJECT_SRC_DIR}/asdf_repeat.c
  ${PROJECT_SRC_DIR}/asdf_virtual.c
  ${PROJECT_SRC_DIR}/asdf_print.c
  ${PROJECT_SRC_DIR}/Arch/asdf_arch_test.c
  )

target_include_directories(asdf_core
  PRIVATE
  ${PROJECT_SRC_DIR}
  ${PROJECT_SRC_DIR}/Arch
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )

add_library(test_helpers
  STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/test_asdf_lib.c
  ${CMAKE_CURRENT_SOURCE_DIR}/test_asdf_keymap_defs.c
  ${CMAKE_CURRENT_SOURCE_DIR}/asdf_keymap_table.c
  )

target_include_directories(test_helpers
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${PROJECT_SRC_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )


target_compile_options(test_helpers
  PRIVATE
  ${CFLAGS}
  )

function(setup_test testname)

  add_executable(${testname}
    ${testname}.c
    )

  target_compile_options(${testname}
    PRIVATE
    ${CFLAGS}
    )

  target_include_directories(${testname}
    PRIVATE
    ${TEST_INCLUDES}
    )

  target_link_libraries(${testname} unity asdf_core test_helpers)

  add_test(
    NAME ${testname}
    COMMAND ${CMAKE_BINARY_DIR}/test/${testname}
    )
endfunction()

enable_testing()

setup_test(test_asdf_repeat)
setup_test(test_asdf_modifiers)
setup_test(test_asdf_keymaps)
setup_test(test_asdf_buffer)
setup_test(test_asdf_output)
setup_test(test_asdf_actions)
setup_test(test_asdf_print)
setup_test(test_asdf_virtual)
setup_test(test_asdf_hook)
setup_test(test_keymap_lookup)
