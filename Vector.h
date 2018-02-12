#ifndef MAZE_VECTOR_H
#define MAZE_VECTOR_H

#include <vector>
#include <iostream>

using namespace std;

template<class T>
class Vector {
public:
    Vector() {
        emptyn = emptyp = true;
        positive.resize(1);
        negative.resize(1);
    }

    /*Vector(int neg, unsigned int pos) {
        emptyn = emptyp = true;
        if (neg < 1) {
            if (neg == 0) neg = 1;
            else neg = -neg;
        }
        if (pos == 0) pos = 1;
        positive.resize(pos);
        negative.resize(neg);
    }

    Vector(unsigned int size) {
        emptyn = emptyp = true;
        positive.resize(size);
        negative.resize(1);
    }*/

    T &operator[](int index) {
        if (index < 0) {
            if (-index > negative.size()) negative.resize(-index);
            emptyn = false;
            return negative[-index - 1];
        } else {
            emptyp = false;
            if (index > positive.size() - 1) positive.resize(index + 1);
            return positive[index];
        }
    }

    pair<int, int> limits() {
        return make_pair(emptyn ? 0 : -negative.size(), emptyp ? 0 : positive.size());
    }

    int size() {
        return (emptyp ? 0 : positive.size()) + (emptyn ? 0 : negative.size());
    }

private:
    bool emptyp, emptyn;
    vector<T> positive;
    vector<T> negative;
};


#endif //MAZE_VECTOR_H
