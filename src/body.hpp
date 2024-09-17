#ifndef BODY_HPP
#define BODY_HPP

#include "base.hpp"
#include "camera.hpp"
#include "screen.hpp"
#include "face.hpp"

class Body {
protected:
    std::vector<Face*> face;
    Coor coor[2];
    Coor center;

public:
    Body();
    Body(const Body& other);
    ~Body();

    void rotate(const Angle angle, const int byCenter = 0);
    void rotate(const Coor& center, const Angle angle);
    virtual int project(const Camera& camera, const float unit, Screen& screen);

    Body& operator=(const Body& other);
};

class Cube : public Body {
public:
    Cube(const Coor& st, const Coor& v0, const Coor& v1, const Coor& v2, const std::string& str);

private:
    void _initFace(const Coor& st, const Coor& v0, const Coor& fn, const Coor& v1, const Coor& v2, const std::string& str);
};

#endif