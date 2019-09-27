#include "plane.h"
#include "view.h"

const float PRECISION = 0.0000001f;

Plane::Plane(Vec3 vectorOne, Vec3 vectorTwo, Vec3 point, Material newMat) {
    this->vectorOne = vectorOne;
    this->vectorTwo = vectorTwo;
    this->center = point;
    Primitive::mat = newMat;
}

Plane::Plane(Vec3 vectorOne, Vec3 vectorTwo, Material newMat) {
    if (abs(vectorOne.dot(vectorTwo)) < PRECISION) { //Cannot be collinear
        *this = Plane(Vec3(1, 0, 0), Vec3(0, 0, 0), mat);
    } else {
        *this = Plane(vectorOne, vectorTwo, Vec3(0, 0, 0), newMat);
    }
}

Plane::Plane(Material newMat) {
    *this = Plane(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 0), newMat);
}

Vec3 Plane::getNormal() const {
    return Vec3(this->vectorOne.cross(vectorTwo));
}

float Plane::calculateIntersectDistance(Vec3 ray, View camera) const {
    Vec3 normal = getNormal();

    //Calculate two parts of the equation
    float numerator = this->center.dot(normal)
            - camera.viewLocation.dot(normal); //As seen in the notes
    float denominator = normal.dot(ray);

    //Verify the ray isn't parallel
    if (normal.dot(ray) < PRECISION) {

        //If line is parallel, may lie on the plane
        if (this->center.dot(normal) < PRECISION) {
            return 0.0f;
        } else {
            return -1.0f;
        }

    } else {
        //At this point we know we have one
        //honest-to-goodness intersection
        return numerator / denominator;
    }
}

Vec3 Plane::calculateNormal(Vec3 point) const {
    return point + this->getNormal();
}
