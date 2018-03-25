#include <string>
#include <fstream>

#ifndef LOG_H
#define LOG_H

#define WARNING 0
#define INFORMATION 1
#define DEBUG 2

class Log {
public:
    Log(std::string file);

    void writeLog(std::string &text, uint8_t mode);

    void close();

private:
    std::ofstream logFile;
};


#endif LOG_H
