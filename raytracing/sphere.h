#ifndef SPHERE_H
#define SPHERE_H
#include "OpenGP/Eigen/Image.h"
#include "primitive.h"

using namespace OpenGP;
class Sphere : public Primitive
{
public:
    /* Constructors */
    Sphere(Vec3 position, float radius, Material newMat);
    Sphere(Vec3 position, float radius);

    Vec3 calculateNormal(Vec3 point) const override;

    /**
     * @brief calculateIntersectDistance Calculates the distance between the
     * camara and the sphere using the given ray. Negative results
     * implies the either no intersection, or the sphere is behind the
     * View Point
     * @param ray The ray we're checking
     * @param camera The origin of the ray
     * @return A distance between the ray and the sphere
     */
    float calculateIntersectDistance(Vec3 ray, Vec3 point) const override;

    ~Sphere() override {}

public:
    float radius;
};

#endif // SPHERE_H
