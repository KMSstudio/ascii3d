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

int Camera::act(char move) {
    static const float unit = 2.0;
    switch (move) {
        case 'a':
            angle.p -= unit; break;
        case 'd':
            angle.p += unit; break;
        case 'w':
            angle.t -= unit; break;
        case 's':
            angle.t += unit; break;
        case 'i':
            depth += unit;
            if (depth > depthMax) { depth = depthMax; }
            break;
        case 'j':
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