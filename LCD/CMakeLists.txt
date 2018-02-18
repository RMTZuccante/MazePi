cmake_minimum_required(VERSION 3.9)
project(LCD)

set(CMAKE_CXX_STANDARD 11)

add_executable(LCD main.cpp LCD.h lcd_i2c.c lcd_i2c.h lcdi2c.h)