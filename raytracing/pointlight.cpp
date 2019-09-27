#include "pointlight.h"
static const float PRECISION = 0.000001f;

PointLight::PointLight(Vec3 newCenter, Vec3 newColor) {
    this->center = Vec3(newCenter);
    this->color = newColor;
}

PointLight::PointLight(Vec3 newCenter) {
    *this = PointLight(newCenter, Vec3(1.0f, 1.0f, 1.0f));
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
