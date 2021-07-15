file(GLOB strukts_src_files *.c)

set(CMAKE_C_FLAGS "-g -Wall -Wextra")

# directory for looking for header files (gcc -I)
include_directories(${Strukts_SOURCE_DIR}/include)

# shared libaries -> dynamic linked: .so/.dll/.dylib
# static library (.a/.lib) -> libstrukts.a (this case)
add_library(strukts STATIC ${strukts_src_files})  # strukts -> target of Makefile