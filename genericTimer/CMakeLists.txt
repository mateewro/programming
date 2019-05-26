cmake_minimum_required (VERSION 3.0)
PROJECT(genericTimer)

set(GTEST_PATH "${PROJECT_SOURCE_DIR}/externals/googletest")
set(GTEST_INCLUDE_DIR ${GTEST_PATH} ${GTEST_PATH}/googlemock/include)
#set(GMOCK_PATH "${PROJECT_SOURCE_DIR}/externals/googletest/googlemock")
add_compile_options("--std=c++17")
add_subdirectory(${GTEST_PATH})
add_subdirectory(code)
add_subdirectory(test)

