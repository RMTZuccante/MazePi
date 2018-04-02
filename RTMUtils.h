#ifndef RTMUTILS_H
#define RTMUTILS_H


#include <string>
#include <array>
#include <map>
#include <sstream>
#include <memory>

class RTMUtils {
public:
    static std::map<std::string, std::string> ports;

    static std::string exec(const char *command);

    static void loadPorts();

    static std::string getPort(std::string id);
};


#endif
