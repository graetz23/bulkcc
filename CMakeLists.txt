# @file CMakeLists.txt
# @author Christian
#
# BULKCC is distributed under the MIT License (MIT); this file is part of.
#
# Copyright (c) 2016-2026 Christian (graetz23@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required(VERSION 3.14)
project(BULKCC)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(${CMAKE_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
    acutest
    GIT_REPOSITORY https://github.com/mity/acutest.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(acutest)

set(BULKCC_SOURCES
    source/bulkcc/bulkccException.cpp
    source/bulkcc/bulkccObj.cpp
    source/bulkcc/bulkccController.cpp
    source/bulkcc/bulkcc.cpp
    source/main.cpp
)

set(BULKCC_LIB_SOURCES
    source/bulkcc/bulkccException.cpp
    source/bulkcc/bulkccObj.cpp
    source/bulkcc/bulkccController.cpp
    source/bulkcc/bulkcc.cpp
)

add_executable(bulkcc ${BULKCC_SOURCES})

set(TEST_SOURCES
    tests/test_bulkcc.cpp
    tests/src/test_types.cpp
    ${BULKCC_LIB_SOURCES}
)
add_executable(bulkcc_test EXCLUDE_FROM_ALL ${TEST_SOURCES})
target_include_directories(bulkcc_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/build/_deps/acutest-src/include
)
add_test(NAME bulkcc_test COMMAND bulkcc_test)
