#
# FindSqlite3.cmake
#
# Author: Stefano Takekawa s.takekawa_at_gmail.com
#
# Date: 2017
#
# Copyright: Apache Licence 2.0
#

#
# Variables that will be defined
#
# SQLITE3_FOUND       = system has SQLITE3 lib
# SQLITE3_LIBRARY     = full path to the SQLITE3 library
# SQLITE3_INCLUDE_DIR = where to find headers
#


#
# small log
#
message(" Find Sqlite3...")
message("")


#
# Sqlite Library Names
#
set(SQLITE_LIBRARY_NAMES sqlite3)


#
# Look for the header file
#
find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h)


#
# Look for the library
#
find_library(SQLITE3_LIBRARY NAMES sqlite3)


#
# check if both includes and library were found
#
string(COMPARE EQUAL "${SQLITE3_INCLUDE_DIR}" "SQLITE3_INCLUDE_DIR-NOTFOUND" SQLITE3_NOTFOUND_INCLUDE)
string(COMPARE EQUAL "${SQLITE3_LIBRARY}" "SQLITE3_LIBRARY-NOTFOUND" SQLITE3_NOTFOUND_LIBRARY)

if(NOT SQLITE3_NOTFOUND_INCLUDE AND NOT SQLITE3_NOTFOUND_LIBRARY)
   set(SQLITE3_FOUND TRUE)
else(NOT SQLITE3_NOTFOUND_INCLUDE AND NOT SQLITE3_NOTFOUND_LIBRARY)
   set(SQLITE3_FOUND FALSE)
endif(NOT SQLITE3_NOTFOUND_INCLUDE AND NOT SQLITE3_NOTFOUND_LIBRARY)


#
# check whether found or not w.r.t. to REQUIRED
#
if(SQLITE3_FOUND)
    message(STATUS "Found Sqlite3: ${SQLITE3_LIBRARY}")
else(SQLITE3_FOUND)
    if(Sqlite3_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find Sqlite3")
    else(Sqlite3_FIND_REQUIRED)
        message(SEND_ERROR "Could not find Sqlite3")
    endif(Sqlite3_FIND_REQUIRED)
    message("")
endif(SQLITE3_FOUND)
