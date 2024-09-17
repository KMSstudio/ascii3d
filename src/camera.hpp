#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "base.hpp"

class Camera {
public:
    Angle angle;
    float depth;

private:
    float depthMin;
    float depthMax;

public:
    Camera(float depth = 100, float depthMin = 20, float depthMax = 200);

    void setDepthMin(float depthMin);
    float getDepthMin() const;
    
    void setDepthMax(float depthMax);
    float getDepthMax() const;

    Angle getAngle() const;
    float getDepth() const;
    
    int act(char move);
    void reset(float depth = 100);
};

#endif