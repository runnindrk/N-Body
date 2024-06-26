cmake_minimum_required(VERSION 3.0)
project(N-Body)

# Add libraries
include_directories(/usr/lib/eigen)

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}-O3)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS}-O3)

# Required
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(OpenMP REQUIRED)
# find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Specify the source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Recursively find all source files in the src directory
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

# Add executable target
add_executable(N-Body ${SOURCES})
target_link_libraries(N-Body PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(N-Body PRIVATE OpenMP::OpenMP_CXX)
