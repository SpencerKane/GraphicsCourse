#include "sphere.h"

/* Constructors */
Sphere::Sphere(Vec3 position, float radius) {
    Sphere(position, radius, Material("", Colour(1.0f, 1.0f, 1.0f)));
}
Sphere::Sphere(Vec3 position, float radius, Material newMat) {
    this->position = position;
    this->radius = radius;
    Sphere::mat = newMat;
}

float Sphere::calculateIntersectDistance(Vec3 ray, View camera) const {
    //Set up quadratic formula coefficients
    float A = ray.dot(ray);
    float B = 2 * ((camera.viewLocation.dot(ray)) - this->center.dot(ray));
    float C = camera.viewLocation.dot(camera.viewLocation)
            + this->center.dot(this->center)
            - (2 * camera.viewLocation.dot(this->center))
            - this->radius * this->radius;

    //Prepare to find the length of the ray
    float discriminant = (B * B) - (4 * A * C);

    //Find the distance from the intersection to the origin
    if (discriminant < 0) {
        return -1.0f; //No intesection.
    } else if (discriminant < 0.000001f && discriminant > -0.000001f) {
        return (-B) / (2 * A); //Only a tangential intersection
    } else {
        //Two intersections here; we only want the smaller distance
        float solution1 = (sqrt(discriminant) - B) / (2 * A);
        float solution2 = (-sqrt(discriminant) - B) / (2 * A);
        return min(solution1, solution2);

        //Note: If one sol'n is negative and the other is positive....
        //We're inside the sphere!!
    }
}

Vec3 Sphere::calculateNormal(Vec3 point) const{
    Vec3 n = this->position - point;
    n *= -1;
    n.normalize();
    return n;
}
