#
# CMakeLists.txt for the colorizeString test application
#
# Author: Stefano Takekawa s.takekawa_at_gmail.com
#
# Date: 2017
#
# Copyright: Apache Licence 2.0
#


#
# cmake version
#
cmake_minimum_required(VERSION 3.7)


#
# common include
#
include(../../support/common.cmake)


#
# variables
#
set(PROJECT_BASENAME "colorizeString")
set(PROJECT_BASEDESCRIPTION "colorizeString test")
set(PROJECT_BASEDIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_SRC_DIR "${PROJECT_BASEDIR}")
set(PROJECT_TWOLIB_DIR "${PROJECT_BASEDIR}/../..")
set(PROJECT_TWOLIB_LIB_DIR "${PROJECT_TWOLIB_DIR}/build")


#
# project
#
project(${PROJECT_BASENAME} LANGUAGES CXX)


#
# sources
#
set(PROJECT_SOURCES ${PROJECT_SRC_DIR}/${PROJECT_BASENAME}.cpp)


#
# includes
#
include_directories(${PROJECT_TWOLIB_DIR}/include)


#
# library configuration
#
find_library(PROJECT_TWOLIB NAMES two HINTS "${PROJECT_TWOLIB_LIB_DIR}")
set(PROJECT_LIBRARIES ${PROJECT_TWOLIB})


#
# executable configuration
#
add_executable(${PROJECT_BASENAME} ${PROJECT_SOURCES})


#
# link libraries
#
target_link_libraries(${PROJECT_BASENAME} ${PROJECT_LIBRARIES} Threads::Threads)


#
# install
#
install(TARGETS ${PROJECT_BASENAME} DESTINATION ${PROJECT_BASEDIR}/../bin)
