#ifndef LIGHT_H
#define LIGHT_H

#include "OpenGP/Eigen/Image.h"

using namespace OpenGP;
using Colour = Vec3;

class Light
{
public:
    virtual float calculateIntersectDistance(Vec3 ray, Vec3 point) = 0;

    virtual ~Light() {}
public:
    Vec3 center;
    Vec3 diffuseIntensity, specularIntensity;
};

#endif // LIGHT_H
