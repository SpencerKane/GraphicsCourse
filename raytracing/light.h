#ifndef LIGHT_H
#define LIGHT_H

#include "OpenGP/Eigen/Image.h"

using namespace OpenGP;
using Colour = Vec3;

class Light
{
public:
    Light(Vec3 center, Vec3 color);

    Light(Vec3 center);

    Vec3 calculateIntersectPoint(Vec3 ray);
public:
    Vec3 center;
    Vec3 color;
};

#endif // LIGHT_H
