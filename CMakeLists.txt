cmake_minimum_required(VERSION 3.8)
project(MazePi)

find_package(OpenCV REQUIRED)
find_package(PythonLibs REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp Matrix.cpp Matrix.h RTMUtils.cpp Log.cpp Log.h RTMUtils.h Vector.h STMConnect.cpp STMConnect.h Serial.cpp Serial.h Config.h Camera.cpp Camera.h KNearestOcr.cpp KNearestOcr.h ImageProcessor.cpp ImageProcessor.h)
add_executable(MazePi ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
target_link_libraries(MazePi ${OpenCV_LIBS} ${PYTHON_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "PiMaze")
