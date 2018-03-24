#!/usr/bin/env bash
cd /home/nico/Desktop/MazePi/
g++ -std=c++14 -v -o PiMaze main.cpp Matrix.cpp Matrix.h STMConnect.h Vector.h Serial.h Serial.cpp
cp /home/nico/Desktop/MazePi/PiMaze ~
#cp /home/nico/Desktop/MazePi/Serial.py ~