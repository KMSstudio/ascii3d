#include "base.hpp"
#include <cmath>
#include <iostream>

#define PI = 3.14159265358979

// ************************************ /&
//                Coor2d                //
// ************************************ //

Coor2d::Coor2d() : x(0), y(0) {}
Coor2d::Coor2d(int x, int y) : x(x), y(y) {}

// *********************************** /&
//                Angle                //
// *********************************** //

Angle::Angle() : p(0), t(0) {}
Angle::Angle(float p, float t) : p(p), t(t) {}