#include "Log.h"
#include "STMConnect.h"

std::ofstream Log::logFile;

void Log::setLogFile(std::string file) {
    logFile.open("/home/nico/MazeLogs/llist", std::fstream::app);
    logFile << file << ' ';
    logFile.close();

    logFile.open("/home/nico/MazeLogs/" + file + ".html");
    logFile << "<link rel='stylesheet' type='text/css' href='log.css'>" << std::endl;
    logFile << "<body>";
    logFile << "Start of log file <br><br>" << std::endl;
}

void Log::writeLog(std::string text, uint8_t mode) {
    switch (mode) {
        case WARNING:
            std::cout << "\033[31m" << getTime() << ' ' << text << "\033[0m" << std::endl;
            if (logFile.is_open())logFile << "<t class='warning'>" << getTime() << ' ' << text << "</t>" << std::endl;
            toHTML(text);
            break;
        case INFORMATION:
            std::cout << "\033[34m" << getTime() << ' ' << text << "\033[0m" << std::endl;
            if (logFile.is_open())
                logFile << "<t class='information'>" << getTime() << ' ' << text << "</t>" << std::endl;
            toHTML(text);
            break;
        case DEBUG:
            std::cout << "\033[1m" << getTime() << ' ' << text << "\033[0m" << std::endl;
            if (logFile.is_open())logFile << "<t class='debug'>" << getTime() << ' ' << text << "</t>" << std::endl;
            toHTML(text);
            break;
        case UNIMPORTANT:
            std::cout << getTime() << ' ' << text << std::endl;
            if (logFile.is_open())
                logFile << "<t class='unimportant'>" << getTime() << ' ' << text << "</t>" << std::endl;
            toHTML(text);
            break;
    }
}

void Log::close() {
    logFile.close();
}

std::string Log::getTime() {
    return "[mins:secs:mils]";
}
