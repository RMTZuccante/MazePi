#include "RTMUtils.h"

std::map<std::string, std::string> RTMUtils::ports;

std::string RTMUtils::exec(const char *command) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(command, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

void RTMUtils::loadPorts() {
    std::stringstream getPorts(exec("tree /dev | grep -e 'video' -e 'ACM' | grep 'usb' | grep -v 'pci'"));

    for (std::string line; getline(getPorts, line);) {
        if (line.find("video", 20) != std::string::npos) {
            int i0 = line.find("usb-") + 4, i1 = line.find("-video") - i0;
            ports.insert(make_pair(line.substr(i0, i1), "/dev" + line.substr(line.find("/video"))));
        } else if (line.find("ACM", 20) != std::string::npos) {
            int i0 = line.find("usb-") + 4, i1 = line.find("-if") - i0;
            ports.insert(make_pair(line.substr(i0, i1), "/dev" + line.substr(line.find("/tty"))));
        }
    }
}

std::string RTMUtils::getPort(std::string id) {
    for (auto const &port : ports) {
        if (port.first.find(id) != std::string::npos) return port.second;
    }

    return "";
}


