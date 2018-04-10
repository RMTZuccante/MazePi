#include <iostream>
#include "STMConnect.h"
#include "Matrix.h"
#include "Log.h"
#include "Camera.h"

int main(int argc, char **argv) {

    std::string port = "Maple";
    int debuglevel = 2;
    bool paused = false;

    for (int i = 0; i < argc; ++i) {
        if (argv[i] == "-p") port = argv[i + 1];
        else if (argv[i] == "-d") debuglevel = atoi(argv[i + 1]);
    }

    std::string fname = "logN" + RTMUtils::exec("tr -cd ' ' < '/home/nico/MazeLogs/llist' | wc -c");

    fname.pop_back();

    Log::setLogFile(fname);

    STMConnect stm;

    bool keep = true;

    int nf = 0, ni = 0;

    while (keep) {
        RTMUtils::loadPorts();

        switch (stm.init(port, 115200)) {
            case 1:
                if (nf > 15) {
                    Log::writeLog(std::string("No serial port available"), Log::WARNING);
                    Log::close();
                    exit(1);
                } else {
                    nf++;
                    usleep(1000000);
                }
                break;
            case 2:
                if (ni > 5) {
                    Log::writeLog(std::string("Error during handshaking at port " + stm.getPort()), Log::WARNING);
                    Log::close();
                    exit(2);
                } else {
                    ni++;
                    usleep(1000000);
                }
                break;
            case 0:
                Log::writeLog(std::string("Connection established with device at port " + stm.getPort()),
                              Log::INFORMATION);
                keep = false;
                break;
        }
    }

    //Camera leftcam(RTMUtils::getPort("Microsoft"));

    Matrix mat;

    std::string inmsg;
    do {
        std::string re = stm._read();
        Log::writeLog(re, Log::UNIMPORTANT);
        std::stringstream str(re);
        str >> inmsg;

        if (inmsg == "check") {
            mat.setLogStr("null");
            uint16_t dists[3];
            float templ = -1, tempr = -1, inc = -1;
            uint8_t c = -1;
            str >> dists[0] >> dists[1] >> dists[2] >> templ >> tempr >> c >> inc;
            mat.check(dists, templ, tempr, c, inc);
            if (mat.getLogStr() != "null") {
                std::string tolcd = mat.getLogStr().substr(0, 16) + "\n" + mat.getLogStr().substr(16);
                Log::writeLog(tolcd, Log::DEBUG);
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
            bool finish = mat.allVisited();
            Log::writeLog(("End? -> " + std::string(finish ? "YES" : "NO")), Log::DEBUG);
            stm._write(std::to_string(finish));

        } else if (inmsg == "getdir") {
            int dir = mat.getDir();
            std::string sdir;
            switch (dir) {
                case FRONT:
                    sdir = "FRONT";
                    break;
                case LEFT:
                    sdir = "LEFT";
                    break;
                case RIGHT:
                    sdir = "RIGHT";
                    break;
                case BACK:
                    sdir = "BACK";
                    break;
            }
            Log::writeLog(("Dir = " + sdir), Log::DEBUG);
            stm._write(std::to_string(dir));

        } else if (inmsg == "debug") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            Log::writeLog(msg, Log::DEBUG);

        } else if (inmsg == "warning") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            Log::writeLog(msg, Log::WARNING);

        } else if (inmsg == "information") {
            std::string spc, msg;
            while (str >> spc) {
                msg += spc + ' ';
            }
            Log::writeLog(msg, Log::INFORMATION);

        } else if (inmsg == "debuglevel") {
            stm._write(std::to_string(debuglevel));

        } else if (inmsg == "checkpoint") {
            paused = true;
            mat.backToCheck();

        } else if (inmsg == "paused") {
            stm._write(std::to_string(paused));
            paused = false;
        }

    } while (inmsg != "stop");
    Log::close();
    return 0;
}
