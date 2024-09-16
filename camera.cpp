#include "camera.hpp"
#include <iostream>

// ************************************ /&
//                Camera                //
// ************************************ //

Camera::Camera(float depth, float depthMin, float depthMax) : angle(0, 0), depth(depth), depthMin(depthMin), depthMax(depthMax) {}

void Camera::setDepthMin(float newDepthMin) { depthMin = newDepthMin; }
float Camera::getDepthMin() const { return depthMin; }

void Camera::setDepthMax(float newDepthMax) { depthMax = newDepthMax; }
float Camera::getDepthMax() const { return depthMax; }

Angle Camera::getAngle() const { return angle; }
float Camera::getDepth() const { return depth; }

int Camera::act(char move) {
    static const float unit = 3.0;
    switch (move) {
        case 'a': case 'A':
            angle.p -= unit; break;
        case 'd': case 'D':
            angle.p += unit; break;
        case 'w': case 'W':
            angle.t -= unit; break;
        case 's': case 'S':
            angle.t += unit; break;
        case 'i': case 'I':
            depth += unit;
            if (depth > depthMax) { depth = depthMax; }
            break;
        case 'j': case 'J':
            depth -= unit;
            if (depth < depthMin) { depth = depthMin; }
            break;
        default:
            return 0;
    }
    return 1;
}

void Camera::reset(float newDepth) {
    angle.p = 0;
    angle.t = 0;
    depth = newDepth;
}