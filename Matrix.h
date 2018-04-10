#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include "Log.h"

#include <string>
#include <map>
#include <set>
#include <stack>
#include <fstream>
#include <queue>
#include <limits>
#include <cfloat>
#include <cmath>

#define BLACK 2
#define WHITE 1
#define MIRROR 0

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define FRONT 0
#define RIGHT 1
#define LEFT 2
#define BACK 3

#define INCLIMIT 10

#define incl (inc - zeroinc)

#define DELTATEMP 7 // Delta minima di temperatorua perchè la parete sia calda
#define DISTWALL 150 // Distanza massima del robot dal muro vicino

#define flr maze[floor]
#define mazepos maze[floor][row][col]

#define intint std::pair<int, int>

struct Cell {
    bool *directions = new bool[4]{false, false, false, false};
    bool visited = false, black = false, mirror = false, victim = false;

    Cell() {};

    Cell(bool dirs[]) {
        directions = dirs;
    };

    bool &operator[](unsigned int index) {
        return directions[index];
    };
};

struct checkpoint {
    int floor, row, col, direction;
    uint16_t front, right, left;

    checkpoint() {};

    checkpoint(int floor, int row, int col, int direction, uint16_t front, uint16_t right, uint16_t left) {
        this->floor = floor;
        this->row = row;
        this->col = col;
        this->direction = direction;
        this->front = front;
        this->right = right;
        this->left = left;
    }
};

class Matrix {
public:

    Matrix();

    /**
     * @param dist array of distances {front, right, left}
     * @param temperatureL the temperature measured by the left sensor
     * @param temperatureR the temperature measured by the right sensor
     * @param color the color of the floor
     */
    void check(uint16_t dist[], float temperatureL, float temperatureR, uint8_t color, float inc);

    /**
     * @return direction
     */
    int getDir();

    void _forward();

    void _back();

    bool isBlack();

    bool isVictim();

    bool allVisited();

    const std::string &getLogStr() const;

    void setLogStr(const std::string &lcdstr);

    void backToCheck();

    bool compareCP(uint16_t dist[]);

private:
    float zeroinc = 200;
    unsigned int direction;
    bool backhome = false;
    int row, col, prow, pcol;
    std::string logStr;
    bool changingflr = false, waschanging = false;
    int floor;
    std::stack<intint > steps;
    bool isnew = false;
    bool moved = true;
    checkpoint lastcp;

    /**
     * @param right right or left
     * @return the "cardinal point" on the right / left of the actual direction
     */
    int getSideDir(int i, bool right);

    intint getCoords(int dir);

    void connect(int row1, int col1, int row2, int col2);

    void pathToNonVisited(intint start);


    void backToHome();

    Vector<Vector<Vector<Cell>>> maze;
    //Vector<intint > slope;
    Vector<intint > last;
    Vector<std::map<intint, std::set<intint>>> graph;
    Vector<unsigned int> visited;
};

#endif //MATRIX_H
