#!/bin/bash

CMAKE_BUILD_TYPE="${1:-Debug}"

echo ""
echo " Build type is ${CMAKE_BUILD_TYPE} ..."
echo ""

INSTALL_DIR=../install

CMAKE_OPT="-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}"

cmake .. ${CMAKE_OPT}  && (echo ""; echo " Done!") || (echo ""; echo " Failed!")

echo ""
