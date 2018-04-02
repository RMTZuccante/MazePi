#include <array>
#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include "Serial.h"
#include "RTMUtils.h"

#ifndef STMCONNETCT_H
#define STMCONNETCT_H

class STMConnect {
public:

    int init(int baudrate);

    std::string _read();

    void _write(std::string cmd);

    std::string getPort();

    void close();

private:

    Serial *stm;
    std::string port;

    void replace(std::string *str, char a, char b);
};

#endif