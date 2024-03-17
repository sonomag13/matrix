cmake_minimum_required(VERSION 3.20)

project(matrix)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(
        matrix
        main.cpp
)

enable_testing()
add_subdirectory(UnitTests)