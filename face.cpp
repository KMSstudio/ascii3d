#include "face.hpp"
#include <cmath>
#include <algorithm>

// ********************************** /&
//                Coor                //
// ********************************** //

Coor::Coor() : x(0), y(0), z(0) {}
Coor::Coor(float x, float y, float z) : x(x), y(y), z(z) {}

float Coor::abs(void) const { return sqrtf(x*x + y*y + z*z); }
Coor Coor::unit(void) const { return (*this)/this->abs(); }

Coor Coor::rotate(const Angle angle) const {
    Coor result = *this;
    float cosP = cos(angle.p), sinP = sin(angle.p);
    float newX = result.x * cosP - result.z * sinP;
    float newZ = result.x * sinP + result.z * cosP;
    result.x = newX;
    result.z = newZ;

    float cosT = cos(angle.t), sinT = sin(angle.t);
    float newY = result.y * cosT + result.z * sinT;
    result.z = -result.y * sinT + result.z * cosT;
    result.y = newY;

    return result;
}

Coor Coor::rotate(const Coor& center, const Angle angle) const {
    Coor translated = *this;
    translated.x -= center.x;
    translated.y -= center.y;
    translated.z -= center.z;

    Coor rotated = translated.rotate(angle);

    rotated.x += center.x;
    rotated.y += center.y;
    rotated.z += center.z;

    return rotated;
}

int Coor::position(const Screen& screen, const float cameraDepth, const float unit, Coor2d& pos) const {
    float depthInv = 1 / (z + cameraDepth);

    if (z >= cameraDepth) { return -1; }
    
    pos.x = (int)(screen.getCenter().x + unit*(x*depthInv));
    pos.y = (int)(screen.getCenter().y - unit*(y*depthInv));

    if (pos.x < 0 || pos.x >= screen.getSize().x) { return -1; }
    if (pos.y < 0 || pos.y >= screen.getSize().y) { return -1; }

    return 0;
}

int Coor::project(const Camera& camera, const char ch, const float unit, Screen& screen) const {
    Coor rotated = this->rotate(camera.angle);
    Coor2d pos;

    if (rotated.position(screen, camera.depth, unit, pos) == -1) { return -1; }
    else { screen.setPixel(pos, Pixel(ch, rotated.z + camera.depth)); return 0; }
}

// Operator overloads
Coor Coor::operator+(const Coor& other) const { return Coor(x + other.x, y + other.y, z + other.z); }
Coor Coor::operator-(const Coor& other) const { return Coor(x - other.x, y - other.y, z - other.z); }
Coor Coor::operator*(float scalar) const { return Coor(x * scalar, y * scalar, z * scalar); }
Coor Coor::operator/(float scalar) const { return Coor(x / scalar, y / scalar, z / scalar); }

Coor Coor::operator-() const { return (*this)*(-1); }

// ********************************** /&
//                Face                //
// ********************************** //

void Face::rotate(const Angle angle) {
    for (auto& c : coor) { c = c.rotate(angle); } }
void Face::rotate(const Coor& center, const Angle angle) {
    for (auto& c : coor) { c = c.rotate(center, angle); } }
//

int Face::project(const Camera& camera, const float unit, Screen& screen) const {
    int res = 0;
    for (const auto& c : coor) {
        if (c.project(camera, ch, unit, screen) == -1) { res = -1; } }
    return res;
}

// ******************************************* /&
//                Square(:Face)                //
// ******************************************* //

Square::Square(char ch) : Face(ch, 3) {
    coor[0] = Coor(0, 0, 0);
    coor[1] = Coor(1, 0, 0);
    coor[2] = Coor(0, 1, 0);
}

Square::Square(const Coor& st, const Coor& v0, const Coor& v1, char ch) : Face(ch, 3) {
    coor[0] = st;
    coor[1] = st + v0;
    coor[2] = st + v1;
}

int Square::project(const Camera& camera, const float unit, Screen& screen) const {
    int res = 0;

    Coor lastP = coor[2] + (coor[1] - coor[0]);
    float Z = std::min({coor[0].z, coor[1].z, coor[2].z, lastP.z});
    float fillGap = SQ_FILL_GAP * (Z + camera.depth) / unit;
    
    Coor v[2] = { coor[1] - coor[0], coor[2] - coor[0] };
    Coor enc[2] = { v[0].unit() * fillGap, v[1].unit() * fillGap };

    float vs[2] = { v[0].abs(), v[1].abs() };
    float encs[2] = { enc[0].abs(), enc[1].abs() };

    int i, j;

    for (i=0; encs[0]*i <= vs[0]; i++) {
        for (j=0; encs[1]*j <= vs[1]; j++) {
            Coor current = coor[0] + (enc[0] * i) + (enc[1] * j);
            if (current.project(camera, ch, unit, screen) == -1) { res = -1; }
        }
    }
    
    return res;
}

// ********************************************* /&
//                Triangle(:Face)                //
// ********************************************* //

Triangle::Triangle(char ch) : Face(ch, 3) {
    coor[0] = Coor(0, 0, 0);
    coor[1] = Coor(1, 0, 0);
    coor[2] = Coor(0, 1, 0);
}

Triangle::Triangle(const Coor& st, const Coor& v0, const Coor& v1, char ch) : Face(ch, 3) {
    coor[0] = st;
    coor[1] = st + v0;
    coor[2] = st + v1;
}

int Triangle::project(const Camera& camera, const float unit, Screen& screen) const {
    int res = 0;

    Coor lastP = coor[2] + (coor[1] - coor[0]);
    float Z = std::min({coor[0].z, coor[1].z, coor[2].z, lastP.z});
    float fillGap = TR_FILL_GAP * (Z + camera.depth) / unit;
    
    Coor v[2] = { coor[1] - coor[0], coor[2] - coor[0] };
    Coor enc[2] = { v[0].unit() * fillGap, v[1].unit() * fillGap };

    float vs[2] = { v[0].abs(), v[1].abs() };
    float encs[2] = { enc[0].abs(), enc[1].abs() };

    int i, j;

    for (i=0; encs[0]*i <= vs[0]; i++) {
        for (j=0; (i*encs[0]/vs[0]) + (j*encs[1]/vs[1]) <= 1.0; j++) {
            Coor current = coor[0] + (enc[0] * i) + (enc[1] * j);
            if (current.project(camera, ch, unit, screen) == -1) { res = -1; }
        }
    }
    
    return res;
}