# Include CMake's external modules
include(GoogleTest)
include(ExternalProject)

enable_testing()

# source file globs
file(GLOB strukts_test_files *.cpp)
file(GLOB strukts_src_files ${Strukts_SOURCE_DIR}/src/*.c)

# CXX compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

# download external dependencies
ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

# directory for looking for header files ~ g++ -I
include_directories(
    ${EXTERNAL_INSTALL_LOCATION}/include # external dependencies headers
    ${Strukts_SOURCE_DIR}/include/strukts  # lib own headers
)

# directory for looking for vendored libs such as gtest ~ g++ -L
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

# build final binary
add_executable(test ${strukts_src_files} ${strukts_test_files})

# dependencies: targets that should run before others
add_dependencies(test googletest)

# links specific libraries to the final binary
target_link_libraries(test gtest gtest_main)  # -lgtest -lgtest_main

# adds gtests
gtest_add_tests(TARGET test)

# runs tests
add_custom_command(TARGET test
                   POST_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/bin/test)