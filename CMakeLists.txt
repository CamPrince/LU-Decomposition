cmake_minimum_required(VERSION 3.10)
project(LU_Decomposition LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Specify the C compiler path
set(CMAKE_C_COMPILER "/usr/bin/gcc")

add_executable(lu_decomposition LU_Decomp.c LU_Header.h main.c read_matrix.c)

# Link the math library
target_link_libraries(lu_decomposition m)

# Optionally, include directories
target_include_directories(lu_decomposition PRIVATE include)