cmake_minimum_required(VERSION 3.25)
project(ex01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex01
        main.cpp RPN.h RPN.cpp)
