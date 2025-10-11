cmake_minimum_required(VERSION 3.16)

project(stm32f407_bootloader C ASM)

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please provide -DCMAKE_TOOLCHAIN_FILE=<path-to-arm-none-eabi-toolchain>")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(bootloader
    ${SRC_DIR}/main.c
    ${SRC_DIR}/bootloader.c
    ${SRC_DIR}/flash_driver.c
    ${SRC_DIR}/protocol.c
    ${SRC_DIR}/transport.c
    ${SRC_DIR}/transport_uart.c
    ${SRC_DIR}/transport_can.c
    ${SRC_DIR}/peripherals.c
    ${SRC_DIR}/crc32.c
    ${SRC_DIR}/system_stm32f4xx.c
    ${SRC_DIR}/startup_stm32f407xx.s
)

if(NOT CMAKE_OBJCOPY)
    find_program(CMAKE_OBJCOPY arm-none-eabi-objcopy)
endif()

if(NOT CMAKE_OBJCOPY)
    message(FATAL_ERROR "Unable to locate objcopy. Set CMAKE_OBJCOPY or ensure arm-none-eabi-objcopy is in PATH.")
endif()

target_include_directories(bootloader PRIVATE
    ${INC_DIR}
)

target_compile_definitions(bootloader PRIVATE
    STM32F407xx
)

target_compile_options(bootloader PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -ffunction-sections
    -fdata-sections
    -fno-common
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
)

target_link_options(bootloader PRIVATE
    -T${CMAKE_CURRENT_SOURCE_DIR}/linker/bootloader.ld
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/bootloader.map
    -nostartfiles
)

add_custom_command(TARGET bootloader POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:bootloader> ${CMAKE_CURRENT_BINARY_DIR}/bootloader.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:bootloader> ${CMAKE_CURRENT_BINARY_DIR}/bootloader.hex
    COMMENT "Generating bootloader.bin and bootloader.hex"
)
