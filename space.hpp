#ifndef SPACE_HPP
#define SPACE_HPP

#include "body.hpp"
#include "camera.hpp"
#include "screen.hpp"
#include <cmath>
#include <conio.h>

class Space {
public:
    Body* body[16];       // 공간 내부에 존재하는 입체들
    Body* showBody[16];   // 보여지는 입체들
    Camera* camera;       // 공간의 카메라
    Screen* screen;       // 카메라에 의해 촬영되는 스크린
    Coor size;            // 공간의 크기
    float unit;           // 3D -> 2D 변환에 사용되는 상수

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