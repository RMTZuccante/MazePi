#ifndef MAZE_VECTOR_H
#define MAZE_VECTOR_H

#include <vector>
#include <iostream>

template<class T>
class Vector {
public:
    Vector() {
        emptyn = emptyp = true;
        positive.resize(1);
        negative.resize(1);
    }

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

    std::pair<int, int> limits() {
        return std::make_pair<int, int >(emptyn ? 0 : -negative.size(), emptyp ? 0 : positive.size());
    }

    int size() {
        return (emptyp ? 0 : positive.size()) + (emptyn ? 0 : negative.size());
    }

private:
    bool emptyp, emptyn;
    std::vector<T> positive;
    std::vector<T> negative;
};


#endif //MAZE_VECTOR_H
