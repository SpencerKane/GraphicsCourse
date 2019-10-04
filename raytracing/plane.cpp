#include "plane.h"

const float PRECISION = 0.0000001f;

Plane::Plane(Vec3 vectorOne, Vec3 vectorTwo, Vec3 point, Material newMat) {
    this->vectorOne = Vec3(vectorOne);
    this->vectorTwo = Vec3(vectorTwo);
    this->center = Vec3(point);
    Primitive::mat = newMat;
}

Plane::Plane(Vec3 vectorOne, Vec3 vectorTwo, Material newMat) {
    Plane* p;
    if (vectorOne.cross(vectorTwo).isApprox(Vec3(0.f, 0.f, 0.f))) { //Cannot be collinear
        p = new Plane(Vec3(1, 0, 0), Vec3(0, 0, 0), mat);
    } else {
        p = new Plane(vectorOne, vectorTwo, Vec3(0, 0, 0), newMat);
    }

    this->vectorOne = p->vectorOne;
    this->vectorTwo = p->vectorTwo;
    this->center = p->center;
    Primitive::mat = p->mat;
    delete p;
}

Plane::Plane(Material newMat) {
    *this = Plane(Vec3(1, 0, 0), Vec3(0, 1, 0), Vec3(0, 0, 0), newMat);
}

Vec3 Plane::getNormal() const {
    return Vec3(this->vectorOne.cross(vectorTwo));
}

float Plane::calculateIntersectDistance(Vec3 ray, Vec3 point) const {
    Vec3 normal = getNormal();

    //Calculate two parts of the equation
    float numerator = this->center.dot(normal)
            - point.dot(normal); //As seen in the notes
    float denominator = normal.dot(ray);

    //Verify the ray isn't parallel
    if (abs(denominator) < PRECISION) {

        //If line is parallel, may lie on the plane
        if (abs(this->center.dot(normal)) < PRECISION) {
            return 1.0f;
        } else {
            return -1.0f;
        }

    } else {
        //At this point we know we have one
        //honest-to-goodness intersection
        return (float) numerator / denominator;
    }
}

Vec3 Plane::calculateNormal(Vec3 point) const {
    return point + this->getNormal();
}
