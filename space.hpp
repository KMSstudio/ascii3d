#ifndef SPACE_HPP
#define SPACE_HPP

#include "body.hpp"
#include "camera.hpp"
#include "screen.hpp"
#include <cmath>
#include <conio.h>
#include "windows.h"

class Space {
public:
    Body* body[16];
    Body* showBody[16];
    Camera* camera;
    Screen* screen;
    Coor size;
    float unit;

    Space(const Coor& size);
    ~Space();

    void setScreen(const Coor2d& screenSize);
    void setCamera(float depth, float minDepth, float maxDepth);
    int calcUnit();

private:
    void _move(const char move);

public:
    int show();
    int make(const Body& newBody, int index = -1);
};

#endif