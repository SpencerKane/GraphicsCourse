#include "spotlight.h"

SpotLight::SpotLight(Vec3 newCenter, Vec3 direction, Vec3 newColor, float angle) {
    this->center = newCenter;
    this->direction = direction;
    this->color = newColor;
    
    //Angle is bounded between 0 and 90
    if (angle > 0 && angle < 90) {
        this->angle = angle;
    } else if (angle < 90) {
        this->angle = 0.0f;
    } else {
        this->angle = 90.0f;
    }
}

float SpotLight::calculateIntersectDistance(Vec3 ray, Vec3 point) {
    return 0;
}
