#ifndef LOG_H
#define LOG_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

class Log {
public:
    static const uint8_t WARNING = 0;
    static const uint8_t INFORMATION = 1;
    static const uint8_t DEBUG = 2;
    static const uint8_t UNIMPORTANT = 3;

    static void setLogFile(std::string file);

    static void writeLog(std::string text, uint8_t mode);

    static void close();

private:
    static std::ofstream logFile;
    static clock_t start;

    static void toHTML(std::string &s) {
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '\n') s = s.substr(0, i - 1) + "<br>" + s.substr(i + 1);
        }
    }

    static std::string getTime();
};


#endif
