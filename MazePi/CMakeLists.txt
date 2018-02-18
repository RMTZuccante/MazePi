cmake_minimum_required(VERSION 3.9)
project(MazePi)

set(CMAKE_CXX_STANDARD 11)

add_executable(MazePi main.cpp Matrix.cpp Matrix.h STMConnect.h Vector.h)