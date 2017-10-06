#
# cmake version
#
cmake_minimum_required(VERSION 3.7)


#
# variables
#
set(PROJECT_BASENAME "tests")
set(PROJECT_BASEDESCRIPTION "C++ Two library test programs")


#
# project
#
project(${PROJECT_BASENAME} LANGUAGES CXX)


#
# add tests
#
add_subdirectory(c_logger)
add_subdirectory(c_textfilereader)
add_subdirectory(colorizeString)
add_subdirectory(common)
