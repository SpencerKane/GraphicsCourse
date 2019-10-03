#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

class PointLight : public Light
{
public:
    PointLight(Vec3 center);
    PointLight(Vec3 center, Vec3 color);

    float calculateIntersectDistance(Vec3 ray, Vec3 point) override;
    ~PointLight() override;
};

#endif // POINTLIGHT_H
