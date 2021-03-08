message("C compiler: ${CMAKE_C_COMPILER}")

function(create_keymap_setups keymaps keymap_table)
  list(TRANSFORM keymaps REPLACE "<\(.+\):\(.+\)>"  "\n  [\\2] = setup_\\1_keymap" OUTPUT_VARIABLE temp_list)
  string(REPLACE ";" "," temp_list2 "${temp_list}")
  set(${keymap_table} "${temp_list2}" PARENT_SCOPE)
endfunction(create_keymap_setups)

function(create_keymap_report keymaps keymap_report)
  list(TRANSFORM keymaps REPLACE "<\(.+\):\(.+\)>"  "\nkeymap [\\2]: \\1" OUTPUT_VARIABLE temp_list)
  string(REPLACE ";" "" temp_list2 "${temp_list}")
  set(${keymap_report} "${temp_list2}" PARENT_SCOPE)
endfunction(create_keymap_report)

include(../keymap_list.cmake)

create_keymap_setups("${keymap_list}" keymap_table)
create_keymap_report("${keymap_list}" keymap_report)

# get list length and decrement by one to account for trailing semicolon
list (LENGTH keymap_list num_keymaps)

message("**********************")
message("Keymap table: ${keymap_report}")
message("**********************\n\n")


configure_file(${ASDF_SRC_DIR}/Arch/asdf_arch_${ARCH}.h ${CMAKE_CURRENT_BINARY_DIR}/asdf_arch.h COPYONLY)
configure_file(${ASDF_SRC_DIR}/Arch/asdf_arch_${ARCH}.c ${CMAKE_CURRENT_BINARY_DIR}/asdf_arch.c COPYONLY)
configure_file(${ASDF_SRC_DIR}/asdf_keymap_table.c.in  ${CMAKE_CURRENT_BINARY_DIR}/asdf_keymap_table.c)
configure_file(${ASDF_SRC_DIR}/asdf_keymap_table.h.in  ${CMAKE_CURRENT_BINARY_DIR}/asdf_keymap_table.h)



list(APPEND C_FLAGS
  -std=c99
  -Wall
  -funsigned-char
  -funsigned-bitfields
  -ffunction-sections
  -fdata-sections
  -fpack-struct
  -fshort-enums
  -O2
  -Wall
  -Wextra
  -Wpointer-arith
  -Wcast-align
  -Wwrite-strings
  -Wswitch-default
  -Wunreachable-code
  -Winit-self
  -Wmissing-field-initializers
  -Wno-unknown-pragmas
  -Wstrict-prototypes
  -Wundef
  -Wold-style-definition
)

list (APPEND SOURCES
  asdf.c
  ${CMAKE_CURRENT_BINARY_DIR}/asdf_arch.c
  asdf_buffer.c
  asdf_hook.c
  asdf_keymap_table.c
  asdf_keymaps.c
  asdf_modifiers.c
  asdf_physical.c
  asdf_repeat.c
  asdf_virtual.c
  main.c
  )

# create a library for the keymap modules
add_subdirectory(Keymaps)

# add the executable
if (COMMAND custom_add_executable)
  custom_add_executable(${ASDF_TARGET_NAME}
  ${SOURCES}
  )
else()
  add_executable(${ASDF_TARGET_NAME})
endif()

target_include_directories(${ASDF_EXECUTABLE_TARGET_NAME}
  PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

target_compile_options(${ASDF_EXECUTABLE_TARGET_NAME}
  PRIVATE
  ${CFLAGS}
  )

target_link_libraries(${ASDF_EXECUTABLE_TARGET_NAME}
  keymaps
  )

