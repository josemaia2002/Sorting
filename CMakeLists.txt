cmake_minimum_required(VERSION 3.22.1)
project(teste VERSION 2.1 LANGUAGES CXX )

set(CMAKE_CXX_FLAGS "-g")

include_directories( include )

add_executable( program
                src/main.cpp)
