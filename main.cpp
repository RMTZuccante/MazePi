#include <iostream>
#include "STMConnect.h"
#include "Matrix.h"

#define LCD true

int main() {
    STMConnect stm(115200);
#if LCD
    stm.lcd("Connesso!");
#endif
    Matrix mat;


    std::string inmsg;
    do {

        std::stringstream str(stm._read());
        str >> inmsg;

        if (inmsg == "check") {
            mat.setLcdstr("null");
            uint16_t dists[3];
            float templ = -1, tempr = -1, c = -1, inc = -1;
            str >> dists[0] >> dists[1] >> dists[2] >> templ >> tempr >> c >> inc;
            mat.check(dists, templ, tempr, c, inc);
            if (mat.getLcdstr() != "null") {
                stm.lcd(mat.getLcdstr());
            }
        } else if (inmsg == "getinfo") {
            stm._write(std::to_string(mat.isBlack()) + " " + std::to_string(mat.isVictim()));

        } else if (inmsg == "move") {
            std::string dir;
            str >> dir;
            if (dir == "forth") mat._forward();
            else mat._back();

        } else if (inmsg == "end") {
            std::cout << "Fine? " << mat.allVisited() << std::endl;
            stm._write(std::to_string(mat.allVisited()));

        } else if (inmsg == "getdir") stm._write(std::to_string(mat.getDir()));
        else if (inmsg == "debug") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            std::cout << "Arduino dice: " << msg << std::endl;
        }

    } while (inmsg != "stop");

    std::cout << "ESCO!" << std::endl;
    return 0;
}
