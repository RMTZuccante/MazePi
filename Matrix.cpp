
#include "Matrix.h"

Matrix::Matrix() {
    direction = NORTH;
    row = col = visited = 0;
    floor = false;
}

void Matrix::check(uint16_t dist[], float temperatureL, float temperatureR, uint8_t color, float inc) {
    lcdstr = "Check: |--|            |--|     ";

    if (zeroinc == NAN) zeroinc = inc;

    if (incl < -INCLIMIT || incl > INCLIMIT) {
        if (!changingflr) {
            slope[floor] = make_pair(prow, pcol);

            intint black(row, col);
            set<intint > nodes = graph[floor][black];
            for (intint i : nodes) {
                graph[floor][i].erase(black);
            }
            graph[floor].erase(black);
            visited--;

            changingflr = true;
            if (incl > 0) floor++;
            else floor--;
        }
        return;
    } else if (changingflr) {
        row = slope[floor].first;
        col = slope[floor].second;
        changingflr = false;
    }

    if (!pos.visited) visited++; // Se la cella è nuova conto una visitata in più

    pos.visited = true;


    if (color == BLACK) {
        lcdstr[16] = 'B';
        pos.black = true;
        intint black(row, col);
        set<intint > nodes = graph[floor][black];
        for (intint i : nodes) {
            graph[floor][i].erase(black);
        }
        graph[floor].erase(black);
        visited--;
        return;
    } else if (color == MIRROR) {
        pos.mirror = true;
        lcdstr[16] = 'M';
    }

// Se non ho il muro davanti
    if (dist[FRONT] > DISTWALL) {
        pos[direction] = true;
        intint p = getCoords(FRONT);
        if (!flr[p.first][p.second].black) {
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
            lcdstr[10] = ' ';
            lcdstr[26] = ' ';
        }
    }
// Se non ho il muro a destra
    if (dist[RIGHT] > DISTWALL) {
        pos[getSideDir(direction, 1)] = true;
        intint p = getCoords(RIGHT);
        if (!flr[p.first][p.second].black) {
            lcdstr[24] = lcdstr[25] = ' ';
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
        }
    }
// Se non ho il muro a sinistra
    if (dist[LEFT] > DISTWALL) {
        pos[getSideDir(direction, 0)] = true;
        intint p = getCoords(LEFT);
        if (!flr[p.first][p.second].black) {
            lcdstr[8] = lcdstr[9] = ' ';
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
        }
    }
// Se ho muri in tutte le direzioni in cui posso controllare di sicuro posso andare indietro quindi collego nel grafo
    if (!pos[direction] && !pos[
            getSideDir(direction, 1)] && !pos[getSideDir(direction, 0)]) {
        intint p = getCoords(BACK);
        if (!flr[p.first][p.second].black) {
            lcdstr[7] = ' ';
            lcdstr[23] = ' ';
            connect(row, col, p.first, p.second);
            connect(p.first, p.second, row, col);
        }
    }

// Verifica temperatura
//TODO tipo di vittima
    if (temperatureR > DELTATEMP && dist[RIGHT] <= DISTWALL || temperatureL > DELTATEMP && dist[LEFT] <= DISTWALL) {
        pos.victim = true;
        lcdstr[17] = 'V';
    }
}

int Matrix::getDir() {
    if (changingflr) {
        while (!steps.empty()) steps.pop();
        return FRONT;
    }

    if (steps.empty()) pathToNonVisited(make_pair(row, col));
    if (steps.empty()) {
        flr[0][0].visited = false;
        pathToNonVisited(make_pair(row, col));
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
    prow = row;
    pcol = col;
    intint cell = getCoords(FRONT);
    row = cell.first;
    col = cell.second;
}

void Matrix::_back() {
    prow = row;
    pcol = col;
    intint cell = getCoords(BACK);
    row = cell.first;
    col = cell.second;
}

bool Matrix::isBlack() {
    return pos.black;
}

bool Matrix::isVictim() {
    return pos.victim;
}

bool Matrix::allVisited() {
    return graph[floor].size() == visited;
}


void Matrix::backToStart() {
    if (row != 0 || col != 0) {
        flr[0][0].visited = false;
        visited--;
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
                return make_pair(row - 1, col);
            case RIGHT:
                return make_pair(row, col + 1);
            case LEFT:
                return make_pair(row, col - 1);
            case BACK:
                return make_pair(row + 1, col);
        }
    } else if (direction == EAST) {
        switch (dir) {
            case FRONT:
                return make_pair(row, col + 1);
            case RIGHT:
                return make_pair(row + 1, col);
            case LEFT:
                return make_pair(row - 1, col);
            case BACK:
                return make_pair(row, col - 1);
        }
    } else if (direction == SOUTH) {
        switch (dir) {
            case FRONT:
                return make_pair(row + 1, col);
            case RIGHT:
                return make_pair(row, col - 1);
            case LEFT:
                return make_pair(row, col + 1);
            case BACK:
                return make_pair(row - 1, col);
        }
    } else {
        switch (dir) {
            case FRONT:
                return make_pair(row, col - 1);
            case RIGHT:
                return make_pair(row - 1, col);
            case LEFT:
                return make_pair(row + 1, col);
            case BACK:
                return make_pair(row, col + 1);
        }
    }
}

void Matrix::connect(int row1, int col1, int row2, int col2) {
    graph[floor][make_pair(row1, col1)].insert(make_pair(row2, col2));
}

void Matrix::pathToNonVisited(intint start) {
    map<intint, intint > chiamanti;
    set<intint > visitati;
    queue<intint > q;
    q.push(start);
    chiamanti.insert(make_pair(start, make_pair(numeric_limits<int>::min(), 0)));
    while (q.size() > 0) {
        intint p = static_cast<intint &&>(q.front());
        visitati.insert(p);
        q.pop();
        if (!flr[p.first][p.second].visited) {
            intint *curs = &p;
            while (chiamanti[*curs].first != numeric_limits<int>::min()) {
                steps.push(make_pair(curs->first, curs->second));
                curs = &chiamanti[*curs];
            }
            return;
        } else {
            set<intint >::iterator i;
            for (i = graph[floor][p].begin(); i != graph[floor][p].end(); ++i) {
                intint coll = *i;
                if (visitati.find(coll) == visitati.end()) {
                    chiamanti.insert(make_pair(coll, make_pair(p.first, p.second)));
                    q.push(coll);
                }
            }
        }
    }
}

const string &Matrix::getLcdstr() const {
    return lcdstr;
}

void Matrix::setLcdstr(const string &lcdstr) {
    Matrix::lcdstr = lcdstr;
}
