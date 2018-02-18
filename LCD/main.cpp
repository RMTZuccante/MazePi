#include <iostream>
#include <sstream>
#include "LCD.h"
#include "lcdi2c.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    // LCD(0x27);
    //string cmd = "schifo -a 0x27 -l -b 1 'Ciao'";
    string comnds[7] = {"schifo", "-a", "0x27", "-l", "-b", "1", "Ciao! Come stai?"};
    char *cd[7];
    for (int i = 0; i < 7; ++i) {
        cd[i] = const_cast<char *>(comnds[i].c_str());
    }

    lcd2c(7, cd);
    return 0;
}
