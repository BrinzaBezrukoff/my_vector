cmake_minimum_required(VERSION 3.21)
project(vector)

set(CMAKE_CXX_STANDARD 11)

add_executable(vector main.cpp vector/Vector.cpp vector/Vector.h)
