#include <iostream>
#include "Serial.h"

Serial::Serial(int baudrate, std::string port) {
    errs = setPort(port, baudrate);
    if (!errs) serial.open(port);
}

std::string Serial::read() {
    std::string out;
    getline(serial, out);
    serial.ignore();
    return out;
}

void Serial::write(std::string &data) {
    serial.clear();
    serial << data << std::endl;
    serial.flush();
}

bool Serial::setPort(const std::string &port, const int baudrate) {
    int fd = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (fd == -1) return 1;
    struct termios settings;
    memset(&settings, 0, sizeof settings);
    settings.c_cflag = getBaud(baudrate) | CRTSCTS | CS8 | CLOCAL | CREAD & ~PARENB & ~CSTOPB & ~CSIZE | CS8;
    settings.c_iflag = IGNPAR;
    settings.c_oflag |= OPOST;
    settings.c_lflag = 0;
    settings.c_cc[VTIME] = 10;
    settings.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &settings);
    close(fd);
    return 0;
}

speed_t Serial::getBaud(int baudrate) {
    switch (baudrate) {
        case 4800:
            return B4800;
        case 9600:
            return B9600;
        case 19200:
            return B19200;
        case 38400:
            return B38400;
        case 57600:
            return B57600;
        case 115200:
            return B115200;
    }
}