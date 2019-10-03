#include "sphere.h"

/* Constructors */
Sphere::Sphere(Vec3 position, float radius) {
    Sphere(position, radius, Material());
}
Sphere::Sphere(Vec3 position, float radius, Material newMat) {
    this->center = Vec3(position);
    this->radius = radius;
    Sphere::mat = newMat;
}

float Sphere::calculateIntersectDistance(Vec3 ray, Vec3 point) const {
    //Set up quadratic formula coefficients
    float A = ray.dot(ray);
    float B = 2 * ((point.dot(ray)) - (this->center).dot(ray));
    float C = point.dot(point)
            + this->center.dot(this->center)
            - (2 * point.dot(this->center))
            - pow(this->radius, 2);

    //Prepare to find the length of the ray
    float discriminant = (B * B) - (4 * A * C);

    //Find the distance from the intersection to the origin
    if (discriminant < 0.0f) {
        return -1.0f; //No intesection.
    } else if (discriminant < 0.000001f && discriminant > -0.000001f) {
        return -1 * (B) / (2 * A); //Only a tangential intersection
    } else {
        //Two intersections here; we only want the smaller distance
        float solution1 = (sqrt(discriminant) - B) / (2 * A);
        float solution2 = -1 * (sqrt(discriminant) + B) / (2 * A);
        return (solution1 > 0.0f && solution2 > 0.0f) ? min(solution1, solution2)
                        : max(solution1, solution2) ;
    }
}

Vec3 Sphere::calculateNormal(Vec3 point) const{
    Vec3 n = this->center - point;
    n *= -1;
    n.normalize();
    return n;
}
