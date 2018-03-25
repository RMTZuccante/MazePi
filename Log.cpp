//
// Created by nico on 25/03/18.
//

#include <iostream>
#include "Log.h"

Log::Log(std::string file) {
    logFile.open("/home/nico/MazeLogs/llist", std::fstream::app);
    logFile << file << ' ';
    logFile.close();

    logFile.open("/home/nico/MazeLogs/" + file + ".html");
    logFile << "<link rel='stylesheet' type='text/css' href='log.css'>" << std::endl;
    logFile << "<body>";
    logFile << "Start of log file, date: " << file << "<br><br>" << std::endl;
}

void Log::writeLog(std::basic_string<char> text, uint8_t mode) {
    switch (mode) {
        case WARNING:
            std::cout << "\033[31m" << text << "\033[0m" << std::endl;
            logFile << "<t class='warning'>" << text << "</t>" << std::endl;
            break;
        case INFORMATION:
            std::cout << "\033[34m" << text << "\033[0m" << std::endl;
            logFile << "<t class='information'>" << text << "</t>" << std::endl;
            break;
        case DEBUG:
            std::cout << "\033[1m" << text << "\033[0m" << std::endl;
            logFile << "<t class='debug'>" << text << "</t>" << std::endl;
            break;
    }
}

void Log::close() {
    logFile.close();
}
