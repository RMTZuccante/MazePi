#include <iostream>
#include "STMConnect.h"
#include "Matrix.h"

#define LCD true

int main() {
    //std::string file =
    std::ofstream fout("/home/nico/MazeLogs/log.txt");
    fout << "Start of log file" << std::endl;
    STMConnect stm;

    switch (stm.init(115200)) {
        case 1:
            fout << "No serial port available" << std::endl;
            fout.close();
            exit(1);
        case 2:
            int i = 0;
            for (i; i < 5; ++i) {
                usleep(1000000);
                if (stm.init(115200) == 0) break;
            }
            if (i == 5) {
                fout << "Error during handshaking at port " << stm.getPort() << std::endl;
                fout.close();
                exit(2);
            }
        case 0:
            fout << "Connection established with device at port " << stm.getPort() << std::endl;
            break;
    }

#if LCD
    //stm.lcd("Connesso!");
#endif
    Matrix mat;

    std::string inmsg;
    do {
        std::string re = stm._read();
        std::cerr << re << std::endl;
        std::stringstream str(re);
        str >> inmsg;

        if (inmsg == "check") {
            mat.setLcdstr("null");
            uint16_t dists[3];
            float templ = -1, tempr = -1, inc = -1;
            uint8_t c = -1;
            str >> dists[0] >> dists[1] >> dists[2] >> templ >> tempr >> c >> inc;
            mat.check(dists, templ, tempr, c, inc);
            if (mat.getLcdstr() != "null") {
                //stm.lcd(mat.getLcdstr());
            }
        } else if (inmsg == "getinfo") {
            stm._write(std::to_string(mat.isBlack()) + " " + std::to_string(mat.isVictim()));

        } else if (inmsg == "move") {
            std::string dir;
            str >> dir;
            if (dir == "forth") mat._forward();
            else mat._back();

        } else if (inmsg == "checkpoint") {
            mat.backToCheck();
            uint16_t dists[3];
            while (true) {
                std::stringstream dt(stm._read());
                dt >> dists[0] >> dists[1] >> dists[2];
                bool equal = mat.compareCP(dists);
                if (equal) {
                    stm._write("1");
                    break;
                } else stm._write("0");
            }

        } else if (inmsg == "end") {
            std::cout << "Fine? " << mat.allVisited() << std::endl;
            stm._write(std::to_string(mat.allVisited()));

        } else if (inmsg == "getdir") stm._write(std::to_string(mat.getDir()));
        else if (inmsg == "debug") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            std::cout << "\033[1m" << msg << "\033[0m" << std::endl;

        } else if (inmsg == "warning") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            std::cout << "\033[31m" << msg << "\033[0m" << std::endl;

        } else if (inmsg == "information") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            std::cout << "\033[34m" << msg << "\033[0m" << std::endl;
        }

    } while (inmsg != "stop");
    fout.close();
    return 0;
}
