#!/usr/bin/env bash
g++ -std=c++14 -v -o MazePi.out main.cpp Matrix.cpp Matrix.h STMConnect.h Vector.h -lpython2.7
cp /home/nico/Desktop/MazePi/MazePi.out ~
cp /home/nico/Desktop/MazePi/Serial.py ~