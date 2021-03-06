
#include "Matrix.h"

Matrix::Matrix() {
    direction = NORTH;
    row = col = 0;
    visited[0] = 0;
    floor = false;
}

void Matrix::check(uint16_t dist[], float temperatureL, float temperatureR, uint8_t color, float inc) {
    std::string posInfo = "row: ";
    posInfo += std::to_string(row);
    posInfo += " col: ";
    posInfo += std::to_string(col);
    posInfo += " floor: ";
    posInfo += std::to_string(floor);
    Log::writeLog(posInfo, Log::INFORMATION);
    logStr = "Check: |---|           |___|    ";
    if (moved) {
        moved = false;
        isnew = !mazepos.visited;
    }
    if (zeroinc == 200) zeroinc = inc;

    if (-incl > INCLIMIT || incl > INCLIMIT) {
        if (!changingflr) {
            //slope[floor] = std::make_pair(row, col);
            last[floor] = std::make_pair(prow, pcol);

            intint slope(row, col);
            std::set<intint > nodes = graph[floor][slope];
            for (intint i : nodes) graph[floor][i].erase(slope);
            graph[floor].erase(slope);

            changingflr = true;
            if (incl > 0) floor++;
            else floor--;
            //Se sto andando in un nuovo piano inizializzo le celle visitate
            if (visited.limits().first > floor || visited.limits().second <= floor) {
                visited[floor] = 0;
            }
        }
        return;
    } else if (changingflr) {
        row = last[floor].first;
        col = last[floor].second;
        changingflr = false;
    }

    if (!changingflr && !mazepos.visited) visited[floor]++; // Se la cella è nuova conto una visitata in più

    mazepos.visited = true;


    if (color == BLACK) {
        logStr[16] = 'B';
        mazepos.black = true;
        intint black(row, col);
        std::set<intint > nodes = graph[floor][black];
        for (intint i : nodes) {
            graph[floor][i].erase(black);
        }
        graph[floor].erase(black);
        visited[floor]--;
        return;
    } else if (color == MIRROR) {
        mazepos.mirror = true;
        logStr[16] = 'M';
        lastcp = checkpoint(floor, row, col, direction, dist[FRONT], dist[RIGHT], dist[LEFT]);
    }

// Se non ho il muro davanti
    if (dist[FRONT] > DISTWALL) {
        mazepos[direction] = true;
        intint p = getCoords(FRONT);
        if (!flr[p.first][p.second].black) {
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
            logStr[8] = logStr[9] = logStr[10] = ' ';
        }
    }
// Se non ho il muro a destra
    if (dist[RIGHT] > DISTWALL) {
        mazepos[getSideDir(direction, 1)] = true;
        intint p = getCoords(RIGHT);
        if (!flr[p.first][p.second].black) {
            logStr[11] = logStr[27] = ' ';
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
        }
    }
// Se non ho il muro a sinistra
    if (dist[LEFT] > DISTWALL) {
        mazepos[getSideDir(direction, 0)] = true;
        intint p = getCoords(LEFT);
        if (!flr[p.first][p.second].black) {
            logStr[7] = logStr[23] = ' ';
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
        }
    }
// Se ho muri in tutte le direzioni in cui posso controllare di sicuro posso andare indietro quindi collego nel grafo
    if (!mazepos[direction] && !mazepos[getSideDir(direction, 1)] && !mazepos[getSideDir(direction, 0)]) {
        intint p = getCoords(BACK);
        if (!flr[p.first][p.second].black) {
            logStr[24] = logStr[25] = logStr[26] = ' ';
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
        }
    }

// Verifica temperatura
//TODO tipo di vittima
    if (temperatureR > DELTATEMP && dist[RIGHT] <= DISTWALL || temperatureL > DELTATEMP && dist[LEFT] <= DISTWALL) {
        mazepos.victim = true;
        logStr[17] = 'V';
    }
}

int Matrix::getDir() {
    if (changingflr) {
        while (!steps.empty()) steps.pop();
        return FRONT;
    }

    if (steps.empty()) pathToNonVisited(std::make_pair(row, col));
    if (steps.empty()) {
        flr[0][0].visited = false;
        pathToNonVisited(std::make_pair(row, col));
        flr[0][0].visited = true;
    }
    int dire = -1;
    for (int j = 0; j < 4 && dire == -1; ++j) {
        if (getCoords(j) == steps.top()) dire = j;
    }
    steps.pop();
    switch (dire) {
        case BACK:
            direction = getSideDir(getSideDir(direction, true), true);
            break;
        case LEFT:
            direction = getSideDir(direction, false);
            break;
        case RIGHT:
            direction = getSideDir(direction, true);
            break;
    }
    return dire;
}

void Matrix::_forward() {
    if (!changingflr) {
        moved = true;
        prow = row;
        pcol = col;
        intint cell = getCoords(FRONT);
        row = cell.first;
        col = cell.second;
    }
}

bool Matrix::compareCP(uint16_t dist[]) {
    bool frn = dist[FRONT] > lastcp.front - 50 && dist[FRONT] < lastcp.front + 50;
    bool lft = dist[LEFT] > lastcp.left - 50 && dist[LEFT] < lastcp.left + 50;
    bool rgh = dist[RIGHT] > lastcp.right - 50 && dist[RIGHT] < lastcp.right + 50;
    return frn && lft && rgh;
}

void Matrix::backToCheck() {
    floor = lastcp.floor;
    row = lastcp.row;
    col = lastcp.col;
    direction = lastcp.direction;
}

void Matrix::_back() {
    if (!changingflr) {
        prow = row;
        pcol = col;
        intint cell = getCoords(BACK);
        row = cell.first;
        col = cell.second;
    }
}

bool Matrix::isBlack() {
    return mazepos.black;
}

bool Matrix::isVictim() {
    return mazepos.victim && isnew;
}

bool Matrix::allVisited() {
    if (changingflr) return false;
    bool allv = graph[floor].size() == visited[floor];
    if (allv) {
        if (!backhome) {
            backhome = true;
            allv = false;
            backToHome();
        } else {
            allv = false;
            if (floor != 0) backToHome();
            else if (col != 0 || row != 0) backToHome();
            else allv = true;
        }
    }
    return allv;
}


void Matrix::backToHome() {
    Log::writeLog("Back to home!!", Log::INFORMATION);
    if (floor == 0) {
        if (row != 0 || col != 0) {
            flr[0][0].visited = false;
            visited[floor]--;
        }
    } else if (row != last[floor].first || col != last[floor].second) {
        flr[last[floor].first][last[floor].second].visited = false;
        visited[floor]--;
    }
}

/*PRIVATE*/
int Matrix::getSideDir(int dir, bool right) {
    if (right) return (dir + 1) % 4;
    else return dir == NORTH ? WEST : dir - 1;
}

intint Matrix::getCoords(int dir) {
    if (direction == NORTH) {
        switch (dir) {
            case FRONT:
                return std::make_pair(row - 1, col);
            case RIGHT:
                return std::make_pair(row, col + 1);
            case LEFT:
                return std::make_pair(row, col - 1);
            case BACK:
                return std::make_pair(row + 1, col);
        }
    } else if (direction == EAST) {
        switch (dir) {
            case FRONT:
                return std::make_pair(row, col + 1);
            case RIGHT:
                return std::make_pair(row + 1, col);
            case LEFT:
                return std::make_pair(row - 1, col);
            case BACK:
                return std::make_pair(row, col - 1);
        }
    } else if (direction == SOUTH) {
        switch (dir) {
            case FRONT:
                return std::make_pair(row + 1, col);
            case RIGHT:
                return std::make_pair(row, col - 1);
            case LEFT:
                return std::make_pair(row, col + 1);
            case BACK:
                return std::make_pair(row - 1, col);
        }
    } else {
        switch (dir) {
            case FRONT:
                return std::make_pair(row, col - 1);
            case RIGHT:
                return std::make_pair(row - 1, col);
            case LEFT:
                return std::make_pair(row + 1, col);
            case BACK:
                return std::make_pair(row, col + 1);
        }
    }
}

void Matrix::connect(int row1, int col1, int row2, int col2) {
    graph[floor][std::make_pair(row1, col1)].insert(std::make_pair(row2, col2));
}

void Matrix::pathToNonVisited(intint start) {
    std::map<intint, intint > chiamanti;
    std::set<intint > visitati;
    std::queue<intint > q;
    q.push(start);
    chiamanti.insert(std::make_pair(start, std::make_pair(std::numeric_limits<int>::min(), 0)));
    while (q.size() > 0) {
        intint p = static_cast<intint &&>(q.front());
        visitati.insert(p);
        q.pop();
        if (!flr[p.first][p.second].visited) {
            intint *curs = &p;
            while (chiamanti[*curs].first != std::numeric_limits<int>::min()) {
                steps.push(std::make_pair(curs->first, curs->second));
                curs = &chiamanti[*curs];
            }
            return;
        } else {
            std::set<intint >::iterator i;
            for (i = graph[floor][p].begin(); i != graph[floor][p].end(); ++i) {
                intint coll = *i;
                if (visitati.find(coll) == visitati.end()) {
                    chiamanti.insert(std::make_pair(coll, std::make_pair(p.first, p.second)));
                    q.push(coll);
                }
            }
        }
    }
}

const std::string &Matrix::getLogStr() const {
    return logStr;
}

void Matrix::setLogStr(const std::string &lcdstr) {
    Matrix::logStr = lcdstr;
}
