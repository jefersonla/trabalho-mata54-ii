cmake_minimum_required(VERSION 2.4)
# Define our project, could be anything
project(TrabalhoMATA54)

# Flags for our entire system
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -lm)
set(CMAKE_DEBUG_C_FLAGS ${CMAKE_DEBUG_C_FLAGS} -lm -g -D DEBUG)
#set(CMAKE_VERBOSE_MAKEFILE on)

# We will tell the system that our source will be
set(SOURCE_FILES main.c)

# And this will be our executable
# Debug Executable
add_executable(main_dbg ${SOURCE_FILES})
target_compile_options(main_dbg PUBLIC "${CMAKE_DEBUG_C_FLAGS}")

# Release Executable
add_executable(main ${SOURCE_FILES})

# Perform tests
# Test 1
#add_custom_command(
#        TARGET main
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E echo "Running First Test $<TARGET_FILE_NAME:main> ..."
#        COMMAND main < tests/teste01.a > tests/saida01.cmp
#        COMMAND main < tests/teste01.b >> tests/saida01.cmp
#        COMMAND rm trabalho.bin
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)

# Test 2
#add_custom_command(
#        TARGET main
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E echo "Running Second Test $<TARGET_FILE_NAME:main> ..."
#        COMMAND main < tests/teste02.a > tests/saida02.cmp
#        COMMAND main < tests/teste02.b >> tests/saida02.cmp
#        COMMAND rm trabalho.bin
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)

# Test 3
#add_custom_command(
#        TARGET main
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E echo "Running Third Test $<TARGET_FILE_NAME:main> ..."
#        COMMAND main < tests/teste03.a > tests/saida03.cmp
#        COMMAND main < tests/teste03.b >> tests/saida03.cmp
#        COMMAND rm trabalho.bin
#
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#)

# Compara Os testes
# Verificação test1
#add_test(
#        NAME test1
#        COMMAND ${CMAKE_COMMAND} -E compare_files saida01 saida01.cmp
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
#)

# Verificação test2
#add_test(
#        NAME test2
#        COMMAND ${CMAKE_COMMAND} -E compare_files saida02 saida02.cmp
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
#)

# Verificação test3
#add_test(
#        NAME test3
#        COMMAND ${CMAKE_COMMAND} -E compare_files saida03 saida03.cmp
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
#)

# Ativa os testes
#enable_testing()