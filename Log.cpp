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

void Log::writeLog(std::string mex, uint8_t mode) {
    std::string t = getTime();
    std::string text;
    unsigned int pos = mex.find('\n');
    if (pos <= mex.length()) {
        std::string al = " ";
        for (int j = 0; j < t.length(); ++j) {
            al += ' ';
        }
        text = mex.substr(0, pos + 1) + al + mex.substr(pos + 1);
    } else text = mex;

    switch (mode) {
        case WARNING:
            std::cout << "\033[31m" << t << ' ' << text << "\033[0m" << std::endl;
            toHTML(text);
            if (logFile.is_open())logFile << "<t class='warning'>" << t << ' ' << text << "</t>" << std::endl;
            break;
        case INFORMATION:
            std::cout << "\033[34m" << t << ' ' << text << "\033[0m" << std::endl;
            toHTML(text);
            if (logFile.is_open())
                logFile << "<t class='information'>" << t << ' ' << text << "</t>" << std::endl;
            break;
        case DEBUG:
            std::cout << "\033[1m" << t << ' ' << text << "\033[0m" << std::endl;
            toHTML(text);
            if (logFile.is_open())logFile << "<t class='debug'>" << t << ' ' << text << "</t>" << std::endl;
            break;
        case UNIMPORTANT:
            std::cout << t << ' ' << text << std::endl;
            toHTML(text);
            if (logFile.is_open())
                logFile << "<t class='unimportant'>" << t << ' ' << text << "</t>" << std::endl;
            break;
    }
}

void Log::close() {
    logFile.close();
}

std::string Log::getTime() {
    return ""; // "[mins:secs:mils]";
}
