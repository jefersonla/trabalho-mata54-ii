# CMake generated Testfile for 
# Source directory: /home/jeferson/ClionProjects/TrabalhoMATA54
# Build directory: /home/jeferson/ClionProjects/TrabalhoMATA54
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test1 "/usr/bin/cmake" "-E" "compare_files" "saida01" "saida01.cmp")
set_tests_properties(test1 PROPERTIES  WORKING_DIRECTORY "/home/jeferson/ClionProjects/TrabalhoMATA54/tests")
add_test(test2 "/usr/bin/cmake" "-E" "compare_files" "saida02" "saida02.cmp")
set_tests_properties(test2 PROPERTIES  WORKING_DIRECTORY "/home/jeferson/ClionProjects/TrabalhoMATA54/tests")
add_test(test3 "/usr/bin/cmake" "-E" "compare_files" "saida03" "saida03.cmp")
set_tests_properties(test3 PROPERTIES  WORKING_DIRECTORY "/home/jeferson/ClionProjects/TrabalhoMATA54/tests")
