#include "body.hpp"
#include <vector>
#include <algorithm>
#include <string>

// ********************************** /&
//                Body                //
// ********************************** //

Body::Body() : center(0, 0, 0) {
    coor[0] = Coor(0, 0, 0);
    coor[1] = Coor(1, 1, 1);
}
Body::Body(const Body& other) {
    // DeepCopy
    coor[0] = other.coor[0]; coor[1] = other.coor[1]; center = other.center;
    for (Face* f : other.face) { face.push_back(f->clone()); }
}
Body::~Body() { for (auto f : face) { delete f; } }

// Rotate around (0, 0, 0) or this->center
void Body::rotate(const Angle& angle, const int byCenter) {
    if (byCenter) {
        for (auto& f : face) { f->rotate(center, angle); }
        coor[0] = coor[0].rotate(center, angle);
        coor[1] = coor[1].rotate(center, angle);
        center = center.rotate(center, angle);
    }
    else {
        for (auto& f : face) { f->rotate(angle); }
        coor[0] = coor[0].rotate(angle);
        coor[1] = coor[1].rotate(angle);
        center = center.rotate(angle);
    }
}

// Rotate around Param center
void Body::rotate(const Coor& center, const Angle angle) {
    for (auto& f : face) { f->rotate(center, angle); }
    coor[0] = coor[0].rotate(center, angle);
    coor[1] = coor[1].rotate(center, angle);
    this->center = this->center.rotate(center, angle);
}

// Project all face to screen
int Body::project(const Camera& camera, const float unit, Screen& screen) {
    int res = 0;
    for (auto& f : face) {
        if (f->project(camera, unit, screen) == -1) { res = -1; } }
    return res;
}

// copy. DeepCopy this->face.
Body& Body::operator=(const Body& other) {
    if (this != &other) {
        for (Face* f : face) { delete f; } face.clear();
        coor[0] = other.coor[0]; coor[1] = other.coor[1]; center = other.center;    // Copy
        for (Face* f : other.face) { face.push_back(f->clone()); }                  // DeepCopy
    }
    return *this;
}

// ********************************** /&
//                Cube                //
// ********************************** //

// Cube object that st + av0 + bv1 + cv1. 0 <= a, b, c <= 1. Letter of each face comes from str[0] ~ str[5].
Cube::Cube(const Coor& st, const Coor& v0, const Coor& v1, const Coor& v2, const std::string& str) {
    Coor fn = st + v0 + v1 + v2;
    _initFace(st, fn, v0, v1, v2, str);
}

void Cube::_initFace(const Coor& st, const Coor& fn, const Coor& v0, const Coor& v1, const Coor& v2, const std::string& str) {
    char faceChars[6];

    coor[0] = st; coor[1] = fn;
    center = (st + fn) / 2;

    if (str.length() >= 6) { for (int i=0; i<6; i++) { faceChars[i] = str[i]; } }
    else { std::fill(std::begin(faceChars), std::end(faceChars), str[0]); }

    face.push_back(new Square(st, v0, v1, faceChars[0]));
    face.push_back(new Square(st, v0, v2, faceChars[1]));
    face.push_back(new Square(st, v1, v2, faceChars[2]));
    face.push_back(new Square(fn, -v0, -v1, faceChars[3]));
    face.push_back(new Square(fn, -v0, -v2, faceChars[4]));
    face.push_back(new Square(fn, -v1, -v2, faceChars[5]));
}

// ************************************** /&
//                Facebody                //
// ************************************** //

// Body object that shown like Face object.
Facebody::Facebody(const Face* face) { this->face.push_back(face->clone()); }