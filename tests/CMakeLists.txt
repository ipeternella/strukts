# Include CMake's external modules
include(GoogleTest)
include(FetchContent)

enable_testing()

# source file globs
file(GLOB strukts_test_files *.cpp)

# CXX compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra --coverage")

# dependency: googletest
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG         origin/master
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
endif ()

# build dependency: googletest supports CMake -> compiles to ${googletest_BINARY_DIR} dir
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# build final binary
add_executable(test ${strukts_test_files})

# links specific libraries to the final binary
target_link_libraries(test gtest gtest_main strukts safemalloc)  # g++ -lgtest -lgtest_main -lsafemalloc -lstrukts

# adds gtests
gtest_add_tests(TARGET test)

# runs tests
# add_custom_command(TARGET test
#                    POST_BUILD
#                    COMMAND ${CMAKE_BINARY_DIR}/bin/test)