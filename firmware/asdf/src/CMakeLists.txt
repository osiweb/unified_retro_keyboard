
set (KEYMAP "production")

message("C compiler: ${CMAKE_C_COMPILER}")

temporary_config_file(${ASDF_SRC_DIR}/Arch/asdf_arch_${ARCH}.h ${CMAKE_CURRENT_BINARY_DIR}/asdf_arch.h)
temporary_config_file(${ASDF_SRC_DIR}/Arch/asdf_arch_${ARCH}.c ${CMAKE_CURRENT_BINARY_DIR}/asdf_arch.c)
temporary_config_file(${ASDF_SRC_DIR}/Keymaps/asdf_all_keymap_defs_${KEYMAP}.h ${CMAKE_CURRENT_BINARY_DIR}/asdf_keymap_defs.h)


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
  asdf_keymaps.c
  asdf_modifiers.c
  asdf_physical.c
  asdf_repeat.c
  asdf_virtual.c
  main.c
  )

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




