cmake_minimum_required(VERSION 3.31.3)
project(advent_of_code)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SUBDIRS "${CMAKE_SOURCE_DIR}/day*")
foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()

add_compile_options(-Wall -Wextra -Wpedantic -std=c++20)