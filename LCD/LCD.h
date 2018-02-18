//
// Created by pi on 14/02/18.
//
/* http://wiringpi.com/download-and-install/ */

#include <wiringPiI2C.h>
#include <iostream>

using namespace std;

#ifndef LCD_LCD_H
#define LCD_LCD_H


class LCD {
public:
    LCD(int addr) {
        if ((fd = wiringPiI2CSetup(addr)) < 0) {
            cout << "I2CSetup Failed " << fd << endl;
        } else {
            wiringPiI2CWrite(fd, 12);
        }
    }

private:
    int fd;
};


#endif //LCD_LCD_H
