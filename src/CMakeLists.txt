include(FetchContent)

file(GLOB strukts_src_files *.c)

set(CMAKE_C_FLAGS "-g -Wall -Wextra")

# shared libaries -> dynamic linked: .so/.dll/.dylib
# static library (.a/.lib) -> libstrukts.a (this case)
add_library(strukts STATIC ${strukts_src_files} ${safemalloc_SOURCE_DIR})  # strukts + dependencies