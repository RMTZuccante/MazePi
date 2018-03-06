#include "STMConnect.h"
#include "Matrix.h"

using namespace std;

int main() {
    STMConnect stm(115200);

    Matrix mat;

    string inmsg;
    do {
        stringstream str(stm._read());
        str >> inmsg;
        if (inmsg == "debug") {
            string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            cout << "Arduino dice: " << msg << endl;
        } else if (inmsg == "check") {
            int dists[3];
            int templ, tempr, c;
            str >> dists[0] >> dists[1] >> dists[2] >> templ >> tempr >> c;
            mat._check(dists, templ, tempr, c);
        } else if (inmsg == "getinfo") {
            stm._write(mat.isBlack() + " " + mat.isVictim());
        } else if (inmsg == "move") {
            string dir;
            str >> dir;
            if (dir == "forth") mat._forward();
            else mat._back();
        } else if (inmsg == "end") {
            cout << "Fine? " << mat.allVisited() << endl;
            stm._write(mat.allVisited() + "");
        } else if (inmsg == "getdir") {
            stm._write(mat.getDir() + "");
        } else if (inmsg == "tostart") {
            mat.backToStart();
        }
    } while (inmsg != "stop");

    cout << "ESCO!" << endl;
    return 0;
}
