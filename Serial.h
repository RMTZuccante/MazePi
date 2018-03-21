#ifndef SERIAL_H
#define SERIAL_H

#include <cstring>
#include <string>
#include <fstream>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class Serial {
public:
    bool errs = false;

    Serial(int baudrate, std::string port);

    std::string read();

    void write(std::string &data);

private:
    std::fstream serial;

    speed_t getBaud(int baudrate);

    bool setPort(const std::string &port, const int baudrate);

};


#endif