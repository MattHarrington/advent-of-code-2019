cmake_minimum_required(VERSION 3.10)

configure_file(day01_input.txt day01_input.txt COPYONLY)

add_executable(day01 day01.cpp)
