#ifndef BASE_HPP
#define BASE_HPP

#include <cmath>
#include <iostream>
#include <vector>

class Coor2d {
public:
    int x, y;

    Coor2d();
    Coor2d(int x, int y);
};

class Angle {
public:
    float p, t;  // Phi, Theta

    Angle();
    Angle(float p, float t);
};

#endif