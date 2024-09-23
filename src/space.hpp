#ifndef SPACE_HPP
#define SPACE_HPP

#include "body.hpp"
#include "camera.hpp"
#include "screen.hpp"
#include <cmath>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include "windows.h"

using namespace std;

class Space {
private:
    Body* body[16];
    Body* showBody[16];
    Camera* camera;
    Screen* screen;
    Coor size;
    float unit;

public:
    Space(const Coor& size);
    ~Space();

    void setScreen(const Coor2d& screenSize);
    void setCamera(float depth, float minDepth, float maxDepth);

private:
    int _calc();
    void _move(const char move);
    void _config(const string& config);
    void _make(int index = -2);

public:
    int show(int verbose = 0);
    int config();

    int make(const Body& newBody, int index = -1);
};

#endif