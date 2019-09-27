#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"

class SpotLight : public Light
{
public:
    SpotLight(Vec3 center, Vec3 direction, float angle);

    calculateIntersectPoint()

public:
    Vec3 direction;
    float angle;
};

#endif // SPOTLIGHT_H
