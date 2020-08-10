cmake_minimum_required(VERSION 3.16)
project(Math)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Math test/test.cpp)
