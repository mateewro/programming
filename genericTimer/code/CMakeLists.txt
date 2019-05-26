file(GLOB SOURCES src/*.cpp)
cmake_minimum_required(VERSION 2.8)

include_directories("include/")
add_library(genericTimerLib ${SOURCES})
add_executable(timer main.cpp)
target_link_libraries(timer genericTimerLib pthread)
set_target_properties(timer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
