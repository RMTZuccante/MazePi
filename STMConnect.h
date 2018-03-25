#include <array>
#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include "Serial.h"

#ifndef STMCONNETCT_H
#define STMCONNETCT_H

class STMConnect {
public:
    static std::string exec(const char *cmd);

    STMConnect();

    int init(int baudrate);

    std::string _read();

    void _write(std::string cmd);

    std::string getPort();

private:

    Serial *stm;
    std::string port;

    std::string findPort();

    void replace(std::string *str, char a, char b);
};

#endif