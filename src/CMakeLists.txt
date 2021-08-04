file(GLOB strukts_src_files *.c)

# shared libaries -> dynamic linked: .so/.dll/.dylib
# static library (.a/.lib) -> libstrukts.a (this case)
add_library(strukts STATIC ${strukts_src_files})