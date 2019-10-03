#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"

class SpotLight : public Light
{
public:
    SpotLight(Vec3 center, Vec3 direction, Vec3 color, float angle);

    float calculateIntersectDistance(Vec3 ray, Vec3 point) override;

    ~SpotLight() override{

    }

public:
    Vec3 direction;
    float angle;
};

#endif // SPOTLIGHT_H
