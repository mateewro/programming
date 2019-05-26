cmake_minimum_required(VERSION 2.8)
file(GLOB SOURCES *.cpp)

include_directories("${GTEST_INCLUDE_DIR}" "${PROJECT_SOURCE_DIR}/code/include" "${PROJECT_SOURCE_DIR}/externals/googletest/googlemock/include" "${PROJECT_SOURCE_DIR}/externals/googletest/googletest/include")


add_executable(genericTimer ${SOURCES})
target_link_libraries(genericTimer genericTimerLib gmock_main pthread)

add_custom_command(TARGET gtest gmock genericTimerTest DEPENDS genericTimerTest genericTimerLib
    COMMAND ${PROJECT_SOURCE_DIR}/build/test/genericTimerTest)
