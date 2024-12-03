cmake_minimum_required(VERSION 3.31)
project(advent_of_code)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(day1)
add_subdirectory(day2)
add_subdirectory(day3)
