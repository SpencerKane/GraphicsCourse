#include "pointlight.h"
#include <stdio.h>

static const float PRECISION = 0.000001f;

PointLight::PointLight(Vec3 center, Vec3 diffuseIntensity, Vec3 specularIntensity) {
    this->center = Vec3(center);
    this->diffuseIntensity = Vec3(diffuseIntensity);
    this->specularIntensity = Vec3(specularIntensity);
}

PointLight::PointLight(Vec3 newCenter) {
    this->center = newCenter;
    this->diffuseIntensity = Vec3(1.0f, 1.0f, 1.0f);
    this->specularIntensity = Vec3(1.0f, 1.0f, 1.0f);
}

float PointLight::calculateIntersectDistance(Vec3 ray, Vec3 rayOrigin) {
    Vec3 difference = this->center - rayOrigin;

    float t = 0.0f;

    //Check for the first non-zero value and solve for scalar
    for (int i = 0; i < 3; ++i) {
        if (abs(ray[i]) >= PRECISION) {
            t = difference[i] / ray[i];
            break;
        }
    }

    Vec3 checkVector = t * ray;

    //Ensure scalar works for all components
    if (checkVector.isApprox(difference)) {
        return t;
    } else {
        return 0.0f;
    }
}

PointLight::~PointLight() {
    std::cout << "Destructing pointlight" << std::endl;
}
