cmake_minimum_required(VERSION 2.4)
# Define our project, could be anything
project(TrabalhoMATA54)

# Some flags for CMAKE, as we don't want the first he will remove this
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm")
set(CMAKE_VERBOSE_MAKEFILE on)

# We will tell the system that our source will be
set(SOURCE_FILES main.c)
#set(LIBRARY_SOURCES libs/arvore.c)

# Add libraries
#add_library(arvore ${LIBRARY_SOURCES})

# And this will be our executable
# Debug Executable
add_executable(dbsg ${SOURCE_FILES})
# Release Executable
add_executable(main ${SOURCE_FILES})

# Link libraries
#target_link_libraries(main arvore)