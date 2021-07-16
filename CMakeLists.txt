cmake_minimum_required(VERSION 3.10)

project(Strukts VERSION 1.0.0 LANGUAGES C CXX)

# output dirs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

# test conditions -DWITH_TEST=ON to run
option(WITH_TEST "Builds and run the tests of the project." OFF)

add_subdirectory(src)

if(WITH_TEST)
    add_subdirectory(tests)    
endif()