file(GLOB SOURCES *.cpp)

include_directories("${GTEST_INCLUDE_DIR}" "${PROJECT_SOURCE_DIR}/code/include")

add_executable(genericTimer ${SOURCES})
target_link_libraries(genericTimer genericTimerLib gtest_main pthread)

add_custom_command(TARGET genericTimerTest DEPENDS genericTimerTest genericTimerLib
    COMMAND ${PROJECT_SOURCE_DIR}/build/test/genericTimerTest)
