cmake_minimum_required(VERSION 3.10)

project(mini_stl)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    vector_example
    examples/vector_example.cpp
)

target_include_directories(
    vector_example
    PRIVATE include
)
