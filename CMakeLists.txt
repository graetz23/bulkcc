cmake_minimum_required(VERSION 3.14)
project(BULKCC VERSION 0.16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

add_library(bulkcc_lib
    source/bulkcc/bulkccException.cpp
    source/bulkcc/bulkccObj.cpp
    source/bulkcc/bulkccController.cpp
    source/bulkcc/bulkcc.cpp
)

target_include_directories(bulkcc_lib PUBLIC
    ${CMAKE_SOURCE_DIR}/source
)

add_executable(bulkcc
    source/main.cpp
)

target_link_libraries(bulkcc PRIVATE bulkcc_lib)

target_include_directories(bulkcc PRIVATE
    ${CMAKE_SOURCE_DIR}/source
)

enable_testing()

add_executable(bulkcc_tests
    tests/test_bulkcc.cpp
    ${CMAKE_SOURCE_DIR}/build/_deps/catch2-src/extras/catch_amalgamated.cpp
)

target_include_directories(bulkcc_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/source
    ${CMAKE_SOURCE_DIR}/tests
    ${CMAKE_SOURCE_DIR}/build/_deps/catch2-src/extras
)

target_link_libraries(bulkcc_tests PRIVATE bulkcc_lib)

target_compile_features(bulkcc_tests PRIVATE cxx_std_14)

add_test(NAME bulkcc_tests COMMAND bulkcc_tests)
