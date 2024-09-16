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

    float abs(void) const;
    Coor unit(void) const;

    Coor rotate(const Angle angle) const;
    Coor rotate(const Coor& center, const Angle angle) const;
    int position(const Screen& screen, const float cameraDepth, const float unit, Coor2d& pos) const;
    int project(const Camera& camera, const char ch, const float unit, Screen& screen) const;
    
    // Operator overloads
    Coor operator+(const Coor& other) const;
    Coor operator-(const Coor& other) const;
    Coor operator*(float scalar) const;
    Coor operator/(float scalar) const;
};

class Face {
protected:
    char ch;
    std::vector<Coor> coor;

public:
    Face(char ch, int coorSize) : ch(ch), coor(coorSize) {}
    virtual ~Face() = default;

    void rotate(const Angle angle);
    void rotate(const Coor& center, const Angle angle);

    virtual int project(const Camera& camera, const float unit, Screen& screen) const;
};

#define DEFAULT_CH_SQ   '@'
class Square : public Face {
public:
    Square(char ch=DEFAULT_CH_SQ);
    Square(const Coor& coor1, const Coor& coor2, const Coor& coor3, char ch=DEFAULT_CH_SQ);

    int project(const Camera& camera, const float unit, Screen& screen) const override;
};

#endif