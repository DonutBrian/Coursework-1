cmake_minimum_required(VERSION 4.3)
project(Coursework_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Coursework_1 list.c)

target_compile_definitions(Coursework_1 PRIVATE test_list)