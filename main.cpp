#include <iostream>
#include "STMConnect.h"
#include "Matrix.h"

using namespace std;

int main() {
    STMConnect stm(115200);

    Matrix mat;

    stm.lcd("Funziona!");

    string inmsg;
    do {

        stringstream str(stm._read());
        str >> inmsg;

        if (inmsg == "check") {
            uint16_t dists[3];
            float templ, tempr, c, inc;
            str >> dists[0] >> dists[1] >> dists[2] >> templ >> tempr >> c >> inc;
            mat.check(dists, templ, tempr, c, inc);

        } else if (inmsg == "getinfo") {
            stm._write(to_string(mat.isBlack()) + " " + to_string(mat.isVictim()));

        } else if (inmsg == "move") {
            string dir;
            str >> dir;
            if (dir == "forth") mat._forward();
            else mat._back();

        } else if (inmsg == "end") {
            cout << "Fine? " << mat.allVisited() << endl;
            stm._write(to_string(mat.allVisited()));

        } else if (inmsg == "getdir") stm._write(to_string(mat.getDir()));

        else if (inmsg == "tostart") mat.backToStart();

        else if (inmsg == "debug") {
            string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            cout << "Arduino dice: " << msg << endl;
        }

    } while (inmsg != "stop");

    cout << "ESCO!" << endl;
    return 0;
}
