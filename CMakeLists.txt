#
# cmake version
#
cmake_minimum_required(VERSION 3.7)


#
# common include
#
include(support/common.cmake)


#
# variables
#
set(PROJECT_BASENAME "two")
set(PROJECT_BASEDESCRIPTION "C++ Two library with common stuff")
set(PROJECT_BASEDIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PROJECT_SRC_DIR "${PROJECT_BASEDIR}")
set(PROJECT_BASEVERSION_MAJOR "0")
set(PROJECT_BASEVERSION_MINOR "0")
set(PROJECT_BASEVERSION_PATCH "1")
set(PROJECT_BASEVERSION "${PROJECT_BASEVERSION_MAJOR}.${PROJECT_BASEVERSION_MINOR}.${PROJECT_BASEVERSION_PATCH}")
set(PROJECT_BASESOVERSION "0")
set(PROJECT_INCLUDE_DIR "${PROJECT_BASEDIR}/include")
set(PROJECT_SRC_DIR "${PROJECT_BASEDIR}/src")
set(PROJECT_SUPPORT_DIR "${PROJECT_BASEDIR}/support")


#
# project
#
project(${PROJECT_BASENAME} LANGUAGES CXX)


#
# add GNU stuff
#
include(GNUInstallDirs)


#
# sources
#
set(PROJECT_SOURCES ${PROJECT_SRC_DIR}/colorizeString/colorizeString.cpp
                    ${PROJECT_SRC_DIR}/common/common.cpp
                    ${PROJECT_SRC_DIR}/c_logger/c_logger.cpp
                    ${PROJECT_SRC_DIR}/c_worker/c_worker.cpp)


#
# includes
#
set(PROJECT_INCLUDES ${PROJECT_INCLUDE_DIR}/two.h)
include_directories(/usr/include)
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME})


#
# library configuration
#
add_library(${PROJECT_BASENAME} SHARED ${PROJECT_SOURCES})

set_target_properties(${PROJECT_BASENAME} PROPERTIES
                      VERSION ${PROJECT_BASEVERSION}
                      SOVERSION ${PROJECT_BASESOVERSION}
                      PUBLIC_HEADER ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h
                      DESCRIPTION ${PROJECT_BASEDESCRIPTION})

#
# link libraries
#
target_link_libraries(${PROJECT_BASENAME} Threads::Threads)


#
# configure files
#
configure_file(${PROJECT_SUPPORT_DIR}/${PROJECT_BASENAME}.pc.in ${PROJECT_SUPPORT_DIR}/${PROJECT_BASENAME}.pc @ONLY)
configure_file(${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h.in ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME}.h @ONLY)


#
# include stuff
#
target_include_directories(${PROJECT_BASENAME} PRIVATE)


#
# install
#
install(TARGETS ${PROJECT_BASENAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY ${PROJECT_INCLUDE_DIR}/${PROJECT_BASENAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_BASENAME})

install(FILES ${PROJECT_SUPPORT_DIR}/${PROJECT_BASENAME}.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
