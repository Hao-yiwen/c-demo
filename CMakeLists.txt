cmake_minimum_required(VERSION 3.27)
project(c_demo C)

set(CMAKE_C_STANDARD 11)

add_library(c_demo STATIC library.c
        test.c
        file1.c
)

# 添加可执行文件
add_executable(c_demo_exec file2.c)

# 将静态库链接到可执行文件
target_link_libraries(c_demo_exec c_demo)