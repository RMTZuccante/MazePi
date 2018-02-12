#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string>

#include <iostream>

using namespace std;

#ifndef UNTITLED_STMCONNETCT_H
#define UNTITLED_STMCONNETCT_H

class STMConnect {
public:
    STMConnect(string port) {
        struct termios toptions;

        fd = open(port.c_str(), O_RDWR | O_NOCTTY);
        tcgetattr(fd, &toptions);
        cfsetispeed(&toptions, B115200);
        cfsetospeed(&toptions, B115200);
        toptions.c_cflag &= ~PARENB;
        toptions.c_cflag &= ~CSTOPB;
        toptions.c_cflag &= ~CSIZE;
        toptions.c_cflag |= CS8;
        toptions.c_lflag = 0;
        tcsetattr(fd, TCSANOW, &toptions);
    }

    string _read() {
        do {
            length = read(fd, buf, 64);
        } while (length < 1);
        buf[length - 2] = 0;
        return buf;
    }

    void _write(string cmd) {
        //cout << "Scrivo " << cmd;
        cmd += '\n';
        write(fd, cmd.c_str(), cmd.length());
    }

private:
    int fd;
    int length;
    char buf[64] = "null";

};

#endif //UNTITLED_STMCONNETCT_H
