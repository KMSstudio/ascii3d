#ifndef BODY_HPP
#define BODY_HPP

#include "base.hpp"
#include "camera.hpp"
#include "screen.hpp"

class Coor {
public:
    float x, y, z;

    Coor();
    Coor(float x, float y, float z);

    Coor rotate(const Angle angle) const;
    Coor rotate(const Coor& center, const Angle angle) const;
    int position(const Screen& screen, const float cameraDepth, const float unit, Coor2d& pos) const;
    int project(const Camera& camera, const char ch, const float unit, Screen& screen);
    
    // Operator overloads
    Coor operator+(const Coor& other) const;
    Coor operator-(const Coor& other) const;
    Coor operator*(float scalar) const;
};

#endif