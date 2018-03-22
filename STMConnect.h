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
    static std::string exec(const char *cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                result += buffer.data();
        }
        return result;
    }

    STMConnect() {};

    int init(int baudrate) {
        port = findPort();
        if (port == "") return 1;
        stm = new Serial(baudrate, "/dev/" + port);
        if (stm->errs) return 1;
        int c = 0;
        srand(time(NULL));
        for (c; c < 10; c++) {
            std::string hs = "Start";
            hs += rand() % 125 + 65;
            _write(hs);
            if (_read() == hs) {
                _write("ok");
                break;
            } else _write("no");
        }

        if (c == 10) return 2;
        return 0;
    }

    std::string _read() {
        std::string s;
        while ((s = stm->read()) == "");
        s.erase(s.length() - 1, 1);
        replace(&s, '_', ' ');
        return s;
    }

    void _write(std::string cmd) {
        stm->write(cmd);
    }

    std::string getPort() {
        return port;
    }

private:

    Serial *stm;
    std::string port;

    std::string findPort() {
        std::string list = STMConnect::exec("ls /dev/ | grep ACM");
        if (list == "") return list;
        std::stringstream ports(list);
        std::string port;
        std::string stm32;
        while (ports >> port) stm32 = port;
        return stm32;
    }

    void replace(std::string *str, char a, char b) {
        for (int i = 0; i < str->size(); ++i) {
            if ((*str)[i] == a) (*str)[i] = b;
        }
    }
};

#endif
