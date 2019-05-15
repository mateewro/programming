file(GLOB SOURCES src/*.cpp)
cmake_minimum_required(VERSION 2.8)

include_directories("include/")
add_library(genericTimerLib ${SOURCES})
add_executable(GenericTimer main.cpp)
target_link_libraries(GenericTimer genericTimerLib)
set_target_properties(GenericTimer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
