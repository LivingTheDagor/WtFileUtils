cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
project(WtFileUtils LANGUAGES C CXX)

include(cmake/functions.cmake)
set(BASE_DIR ${CMAKE_CURRENT_LIST_DIR})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(Windows)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(Linux)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_compile_definitions(Mac)
endif ()

add_subdirectory(3rdParty)
add_subdirectory(src)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR) # not a subproject, include tests
    message(STATUS "WtFileUtils ran as base project")
    print_stats() # print CMAKE stats about compiler and such
    set_compiler_flags() # sets the flags I want
    add_subdirectory(debugging)
    add_subdirectory(replay)
else()
    message(STATUS "WtFileUtils ran as subproject")
endif()
