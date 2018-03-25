#include "STMConnect.h"

STMConnect::STMConnect() {}

std::string STMConnect::exec(const char *cmd) {
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

int STMConnect::init(int baudrate) {
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

std::string STMConnect::findPort() {
    std::string list = STMConnect::exec("ls /dev/ | grep ACM");
    if (list == "") return list;
    std::stringstream ports(list);
    std::string port;
    std::string stm32;
    while (ports >> port) stm32 = port;
    return stm32;
}

void STMConnect::replace(std::string *str, char a, char b) {
    for (int i = 0; i < str->size(); ++i) {
        if ((*str)[i] == a) (*str)[i] = b;
    }
}
