cmake_minimum_required(VERSION 3.10)

project(test)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/output)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})
