#include <iostream>
#include "STMConnect.h"
#include "Matrix.h"

#define LCD true

void warining(std::string &msg, std::ofstream &fout) {
    std::cout << "\033[31m" << msg << "\033[0m" << std::endl;
    fout << "<t class='warning'>" << msg << "</t>" << std::endl;
}

void information(std::string &msg, std::ofstream &fout) {
    std::cout << "\033[34m" << msg << "\033[0m" << std::endl;
    fout << "<t class='information'>" << msg << "</t>" << std::endl;
}

void debug(std::string &msg, std::ofstream &fout) {
    std::cout << "\033[1m" << msg << "\033[0m" << std::endl;
    fout << "<t class='debug'>" << msg << "</t>" << std::endl;
}

int main() {
    //std::string file =
    std::ofstream fout("/home/nico/MazeLogs/log.html");
    fout << "<link rel='stylesheet' type='text/css' href='log.css'>" << std::endl;
    fout << "Start of log file<br>" << std::endl;
    STMConnect stm;

    bool keep = true;

    int nf = 0, ni = 0;

    while (keep)
        switch (stm.init(115200)) {
            case 1:
                if (nf > 15) {
                    warining(*(new std::string("No serial port available")), fout);
                    fout.close();
                    exit(1);
                } else {
                    nf++;
                    usleep(1000000);
                }
            case 2:
                if (ni > 5) {
                    warining(*(new std::string("Error during handshaking at port " + stm.getPort())), fout);
                    fout.close();
                    exit(2);
                } else {
                    ni++;
                    usleep(1000000);
                }
                break;
            case 0:
                information(*(new std::string("Connection established with device at port " + stm.getPort())), fout);
                keep = false;
                break;
        }

#if LCD
    //stm.lcd("Connesso!");
#endif
    Matrix mat;

    std::string inmsg;
    do {
        std::string re = stm._read();
        fout << re << std::endl;
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
            debug(msg, fout);

        } else if (inmsg == "warning") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            warining(msg, fout);

        } else if (inmsg == "information") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            information(msg, fout);
        }

    } while (inmsg != "stop");
    fout.close();
    return 0;
}
