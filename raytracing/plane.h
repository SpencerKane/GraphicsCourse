#ifndef PLANE_H
#define PLANE_H

#include "primitive.h"

class Plane : public Primitive
{
public:
    /* Constructors */
    Plane(Vec3 vectorOne, Vec3 vectorTwo, Vec3 point, Material mat);

    Plane(Vec3 vectorOne, Vec3 vectorTwo, Material mat);

    Plane(Material mat);

    /**
     * @brief getNormal Finds a vector that is normal to the plane
     * @return A normalized vector orthonal to this plane
     */
    Vec3 getNormal() const;

    /**
     * @brief calculateNormal gets a normal to the plane at point
     * @param point The point the normal will "sprout" from
     * @return A vector normal to this plane and based at point
     */
    Vec3 calculateNormal(Vec3 point) const override;

    float calculateIntersectDistance(Vec3 ray, View camera) const override;

public:
    Vec3 vectorOne, vectorTwo;
};

#endif // PLANE_H
