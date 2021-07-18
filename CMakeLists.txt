cmake_minimum_required(VERSION 3.10)
project(Strukts VERSION 1.0.0 LANGUAGES C CXX)

# cmake modules
include(FetchContent)

# output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# test conditions -DWITH_TEST=ON to run
option(WITH_TEST "Builds and run the tests of the project." OFF)

# directory for looking for header files
include_directories(${Strukts_SOURCE_DIR}/include/strukts)  # strukts own headers ~ gcc -I

# third-party dependency: safemalloc
FetchContent_Declare(safemalloc
    GIT_REPOSITORY https://github.com/Theldus/safemalloc
    GIT_TAG         origin/master
)

FetchContent_GetProperties(safemalloc)
if (NOT safemalloc_POPULATED)
    FetchContent_Populate(safemalloc)  # fetches safemalloc git repo on "_deps" folder
endif ()

# compile safemalloc as it has no CMake support
file(GLOB safemalloc_src ${safemalloc_SOURCE_DIR}/*.c)
include_directories(${safemalloc_SOURCE_DIR})  # includes safemalloc headers ~ gcc -I

# build other CMakefiles
add_subdirectory(src)

if(WITH_TEST)
    add_subdirectory(tests)    
endif()