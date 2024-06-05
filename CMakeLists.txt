cmake_minimum_required(VERSION 3.27)
project(c_demo C)

set(CMAKE_C_STANDARD 11)

add_library(c_demo STATIC library.c
        test.c)
