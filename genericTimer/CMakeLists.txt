cmake_minimum_required (VERSION 2.8)
PROJECT(genericTimer)

set(GTEST_PATH "${PROJECT_SOURCE_DIR}/../externals/googletest/googletest")
set(GTEST_INCLUDE_DIR ${GTEST_PATH} ${GTEST_PATH}/../googlemock/include)
add_compile_options("--std=c++17")
add_subdirectory(${GTEST_PATH} ./gtest)
add_subdirectory(code)
add_subdirectory(test)

