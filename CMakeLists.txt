cmake_minimum_required(VERSION 2.4)
# Define our project, could be anything
project(TrabalhoMATA54)

# Flags for our entire system
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm")
set(CMAKE_C_FLAGS "${CMAKE_DEBUG_C_FLAGS} -lm -g -D DEBUG")
set(CMAKE_VERBOSE_MAKEFILE on)

# We will tell the system that our source will be
set(SOURCE_FILES main.c)

# And this will be our executable
# Debug Executable
add_executable(main_dbg ${SOURCE_FILES})
target_compile_options(main_dbg {CMAKE_DEBUG_C_FLAGS})

# Release Executable
add_executable(main ${SOURCE_FILES})
target_compile_options(main {CMAKE_C_FLAGS})

