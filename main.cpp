#include <iostream>
#include <time.h>
#include <sstream>
#include "Matrix.h"
#include "STMConnect.h"

using namespace std;

int main() {
    STMConnect stm("/dev/ttyACM1");

    srand((unsigned) time(NULL));
    string handshake, response;
    do {
        handshake = "start";
        handshake += rand() % 100;
        stm._write(handshake);
        response = stm._read();
	cout << handshake << " risp " << response<<" "<< (handshake == response) <<endl;
        if (handshake == response) stm._write("ok");
        else stm._write("errore");
	usleep(1000000);
    } while (response != handshake);

    cout << stm._read();
    return  0;

    Matrix mat;

    string inmsg;
    do {
        stringstream str(stm._read());
        str >> inmsg;
        if (inmsg == "check") {
            int dists[3];
            int templ, tempr, c;
            str >> dists[0] >> dists[1] >> dists[2] >> templ >> tempr >> c;
            mat._check(dists, templ, tempr, c);
        } else if (inmsg == "getinfo") {
            /* black victim*/
            stm._write(mat.isBlack() + " " + mat.isVictim());
        } else if (inmsg == "move") {
            string dir;
            str >> dir;
            if (dir == "forth") mat._forward();
            else mat._back();
        } else if (inmsg == "end") {
            stm._write(mat.allVisited() + "");
        } else if (inmsg == "getdir") {
            stm._write(mat.getDir() + "");
        } else if (inmsg == "tostart") {
            mat.backToStart();
        }
    } while (inmsg != "stop");
    return 0;
}