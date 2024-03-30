cmake_minimum_required(VERSION 3.10)

project(solo)

#include directory
include_directories(include)

# Add executable target
add_executable(solo src/main.c)


# Set output directory for binaries
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
