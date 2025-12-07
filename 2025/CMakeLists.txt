cmake_minimum_required(VERSION 3.30)
project(advent_of_code)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

file(GLOB DAY_DIRS "${CMAKE_SOURCE_DIR}/day*")

foreach(day ${DAY_DIRS})
    if(IS_DIRECTORY ${day})

        get_filename_component(day_name ${day} NAME)

        file(GLOB day_sources "${day}/*.cpp")

        if(day_sources)
            add_executable(${day_name} ${day_sources})

            set_target_properties(${day_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
            )
        endif()

    endif()
endforeach()

