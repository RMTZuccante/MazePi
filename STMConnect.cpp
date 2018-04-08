#include "STMConnect.h"

int STMConnect::init(int baudrate) {
    port = RTMUtils::getPort("Arduino");

    if (port.empty()) return 1;
    stm = new Serial(baudrate, port);
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

std::string STMConnect::_read() {
    std::string s = stm->read();
    replace(&s, '_', ' ');
    return s;
}

void STMConnect::_write(std::string cmd) {
    stm->write(cmd);
}

std::string STMConnect::getPort() {
    return port;
}

void STMConnect::replace(std::string *str, char a, char b) {
    for (int i = 0; i < str->size(); ++i) {
        if ((*str)[i] == a) (*str)[i] = b;
    }
}

void STMConnect::close() {
    stm->close();
}
