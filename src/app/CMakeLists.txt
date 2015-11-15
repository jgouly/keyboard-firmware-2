add_executable(firmware.elf main.cpp)
if(${TARGET} STREQUAL "host")
  set(TARGET_LIB target)
else()
  set(TARGET_LIB -Wl,-whole-archive target -Wl,-no-whole-archive)
endif()
target_link_libraries(firmware.elf ${TARGET_LIB})
if (NOT "${CMAKE_OBJCOPY}" STREQUAL "CMAKE_OBJCOPY-NOTFOUND")
  add_custom_command(TARGET "firmware.elf" POST_BUILD
    COMMAND
      ${CMAKE_OBJCOPY} -O binary -R .eeprom
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/firmware.elf
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/firmware.bin
    COMMENT "Creating firmware.bin file")
endif()
