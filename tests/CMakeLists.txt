enable_testing()

file(GLOB strukts_test_files *.cpp)
file(GLOB strukts_src_files ${Strukts_SOURCE_DIR}/src/*.c)

# CXX compiler flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

# directory for looking for header files ~ g++ -I
include_directories(
    ${Strukts_SOURCE_DIR}/include/internal/vendor 
    ${Strukts_SOURCE_DIR}/include
)

# directory for looking for vendored libs such as gtest ~ g++ -L
link_directories(${Strukts_SOURCE_DIR}/lib)

add_executable(testing ${strukts_src_files} ${strukts_test_files})

target_link_libraries(testing gtest gtest_main)  # -lgtest -lgtest_main
# target_link_options(testing PUBLIC "-Wl,-t,-v")
add_test(NAME linked_list_tests COMMAND testing)