# Minimum version of CMake required
cmake_minimum_required(VERSION 3.20)

# CMake config for location
include(pico_sdk_import.cmake)

# Project
project(pico_multicore_temp)

# Initialize pico-sdk
pico_sdk_init()

# Add executable file
add_executable(pico_multicore_temp multicore_temp.c)

# Link libraries to be used
target_link_libraries(pico_multicore_temp pico_stdlib pico_multicore hardware_adc)

# Enable serial output
pico_enable_stdio_usb(pico_multicore_temp 1)
pico_enable_stdio_uart(pico_multicore_temp 0)

# Build files to program the pico
pico_add_extra_outputs(pico_multicore_temp)