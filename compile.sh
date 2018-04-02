#!/usr/bin/env bash
cd /home/nico/Desktop/MazePi/
g++ -std=c++14 -v -o PiMaze main.cpp Matrix.cpp Matrix.h STMConnect.h STMConnect.cpp Log.h Log.cpp Vector.h Serial.h RTMUtils.cpp RTMUtils.h Serial.cpp -lpython2.7
cp /home/nico/Desktop/MazePi/PiMaze ~
cp /home/nico/Desktop/MazePi/Serial.py ~