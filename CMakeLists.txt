cmake_minimum_required(VERSION 3.18.0)
project(ooaip)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
