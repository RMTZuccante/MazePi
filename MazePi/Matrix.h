#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <iostream>
#include <map>
#include <set>
#include <stack>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define FRONT 0
#define RIGHT 1
#define LEFT 2
#define BACK 3

#define DELTATEMP 7 // Delta minima di temperatorua perchè la parete sia calda
#define DISTWALL 18 // Distanza massima del robot dal muro vicino
#define BLACK 23

#define flr maze[floor]
#define pos maze[floor][row][col]

#define intint pair<int, int>

using namespace std;

class Matrix {
public:
    Matrix();

    //TODO Non so di che tipo sono le variabili
    /**
     * @param dist array of distances {front, right, left}
     * @param temperatureL the temperature measured by the left sensor
     * @param temperatureR the temperature measured by the right sensor
     * @param color the color of the floor
     */
    void _check(int dist[], int temperatureL, int temperatureR, int color);

    /**
     * @return direction
     */
    int getDir();

    void _forward();

    void _back();

    bool isBlack();

    bool isVictim();

    bool allVisited();

    void backToStart();

private:
    unsigned int direction;
    unsigned int visited;
    int row, col;
    bool floor;
    stack<intint > steps;

    /**
     * @param right right or left
     * @return the "cardinal point" on the right / left of the actual direction
     */
    int getSideDir(int i, bool right);

    intint getCoords(int dir);

    void connect(int row1, int col1, int row2, int col2);

    void pathToNonVisited(intint start);

    //bool has(int, int);

    //void newNode(int row1, int col1);

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

    Vector<Vector<Cell>> maze[2];
    map<intint, set<intint>> graph[2];
    //vector<pair<pair<int, int>, vector<pair<int, int>>>> graph;
};

#endif //MATRIX_H
