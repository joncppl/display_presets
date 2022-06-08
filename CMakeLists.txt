cmake_minimum_required(VERSION 3.21)
project(display_presets)

set(CMAKE_CXX_STANDARD 17)

add_executable(store store.cpp)
add_executable(load load.cpp)