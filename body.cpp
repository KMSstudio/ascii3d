#include "body.hpp"
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
    float newX = result.x * cosP - result.y * sinP;
    float newY = result.x * sinP + result.y * cosP;
    result.x = newX;
    result.y = newY;

    float cosT = cos(angle.t), sinT = sin(angle.t);
    float newZ = result.z * cosT - result.y * sinT;
    result.y = result.z * sinT + result.y * cosT;
    result.z = newZ;

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
    pos.y = (int)(screen.getCenter().y + unit*(y*depthInv));

    if (pos.x < 0 || pos.x >= screen.getSize().x) { return -1; }
    if (pos.y < 0 || pos.y >= screen.getSize().y) { return -1; }

    return 0;
}

int Coor::project(const Camera& camera, const char ch, const float unit, Screen& screen) const {
    Coor rotated = this->rotate(camera.angle);
    Coor2d pos;

    if (rotated.position(screen, camera.depth, unit, pos) == -1) { return -1; }
    else { 
        std::cout << "x pos: " << pos.x << "y pos: " << pos.y << std::endl;
        screen.setPixel(pos, Pixel(ch, rotated.z + camera.depth)); return 0; }
}

// Operator overloads
Coor Coor::operator+(const Coor& other) const { return Coor(x + other.x, y + other.y, z + other.z); }
Coor Coor::operator-(const Coor& other) const { return Coor(x - other.x, y - other.y, z - other.z); }
Coor Coor::operator*(float scalar) const { return Coor(x * scalar, y * scalar, z * scalar); }
Coor Coor::operator/(float scalar) const { return Coor(x / scalar, y / scalar, z / scalar); }

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
    for (const auto& c : coor) { if (c.project(camera, ch, unit, screen) == -1) { res = -1; } }
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

Square::Square(const Coor& coor1, const Coor& coor2, const Coor& coor3, char ch)
    : Face(ch, 3) {
    coor[0] = coor1;
    coor[1] = coor2;
    coor[2] = coor3;
}

int Square::project(const Camera& camera, const float unit, Screen& screen) const {
    int res = 0;
    Coor lastP = coor[2] + (coor[1]-coor[0]);

    float Z = std::max({coor[0].z, coor[1].z, coor[2].z, lastP.z});
    float fillGap = 0.8 * (Z + camera.depth) / unit;

    for (const auto& c : coor) { if (c.project(camera, ch, unit, screen) == -1) { res = -1; } }
    if (lastP.project(camera, ch, unit, screen) == -1) { res = -1; }
    return res;
}