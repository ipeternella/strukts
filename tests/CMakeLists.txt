enable_testing()
include(GoogleTest)

# source file globs
file(GLOB strukts_test_files *.cpp)
file(GLOB strukts_src_files ${Strukts_SOURCE_DIR}/src/*.c)

# CXX compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

# directory for looking for header files ~ g++ -I
include_directories(
    ${Strukts_SOURCE_DIR}/include/internal/vendor  # vendor headers (ex: gtest)
    ${Strukts_SOURCE_DIR}/include  # lib own headers
)

# directory for looking for vendored libs such as gtest ~ g++ -L
link_directories(${Strukts_SOURCE_DIR}/lib)

add_executable(test ${strukts_src_files} ${strukts_test_files})

target_link_libraries(test gtest gtest_main)  # -lgtest -lgtest_main

# adds gtests
gtest_add_tests(TARGET test)

# runs tests
add_custom_command(TARGET test
                   POST_BUILD
                   COMMAND ${CMAKE_BINARY_DIR}/bin/test)