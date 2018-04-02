#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>

#include "ImageProcessor.h"
#include "KNearestOcr.h"

class Camera {
public:
    Camera(std::string &device, int delay);

    explicit Camera(std::string &device) : Camera(device, 1000) {};

    void test();

    void learn();

    void adjust();

    std::string read();

private:
    cv::VideoCapture input;
    ImageProcessor proc;
    KNearestOcr ocr;
    int delay;
    bool loaded;
};

#endif
