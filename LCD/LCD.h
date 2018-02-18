#include <iostream>
#include "lcdi2c.h"

using namespace std;

#ifndef LCD_LCD_H
#define LCD_LCD_H


class LCD {
public:
    LCD(string addr) {
        command[0] = "-a";
        command[1] = addr;
        command[2] = "-i";
		argc = 3;
        sendCmd();
        command[2] = "-b";
        command[3] = "0";
        command[4] = "-s";
        command[5] = "0";
        command[6] = "-x";
        command[7] = "0";
        command[8] = "-y";
        command[9] = "0";
		argc =10;
		sendCmd();
    }

    void print(string s) {
        command[10] = s;
		argc ++;
        sendCmd();
		argc --;
    }

    void setRow(int row) {
        command[9] = "" + row;
    }

    void setCol(int col) {
        command[7] = "" + col;
    }

    void reset() {
        command[10] = "-l";
        command[7] = "0";
        command[9] = "0";
		argc++;
        sendCmd();
		argc--;
    }

    void setBackLight(bool on) {
        command[3] = on? "1" : "0";
        sendCmd();
    }

private:
    void sendCmd() {
        lcd2c(argc, command);
    }
	int argc = 0;
    string command[12];
};


#endif //LCD_LCD_H
