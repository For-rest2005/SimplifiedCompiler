cmake_minimum_required(VERSION 3.10)

project(test)

add_compile_options(-g)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/compsrc/*.cpp )
set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
add_executable("virtual" "../virsrc/Virtual.cpp")
