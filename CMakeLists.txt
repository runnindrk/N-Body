cmake_minimum_required(VERSION 3.0)
project(N-Body)

# Add libraries
include_directories(/lib/eigen)

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Specify the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Recursively find all source files in the src directory
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Add executable target
add_executable(N-Body ${SOURCES})