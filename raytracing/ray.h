#ifndef RAY_H
#define RAY_H

#include "OpenGP/Eigen/Image.h"
#include "primitive.h"
#include "light.h"
using namespace OpenGP;

class Ray
{
public:
    /**
     * @brief Ray Constructs an initial ray with maximum lifespan
     * @param vector The direction of the ray
     */
    Ray(Vec3 vector);

    /**
     * @brief Ray Generates a ray from a ray, auto-decrementing the timer
     * @param ray
     */
    Ray(Ray *ray);

    /**
     * @brief generateRay Given a primitive and an intersection point on its
     * surface, along with the medium the ray was travelling through prior to
     * the intersection, it generates either a reflector ray or a refractor
     * ray aimed in the proper direction. If timer is 0, (0, 0, 0) will
     * always be returned
     * @param p The primitive the ray intersected
     * @param intersectPoint The point at which the ray intersected the primitive
     * @param intialMedium The material (medium) the ray was travelling through
     * @return A Ray aimed in a suitable direction caused by an interssection
     */
    Ray generateRay(Primitive p, Vec3 intersectPoint, Material intialMedium);

public:
    Vec3 vector;
    uint timer = 3; //Can't be under 0

private:
    /**
     * @brief Ray A constructor that assigns a timer to the
     * @param vector
     * @param timer
     */
    Ray(Vec3 vector, uint timer);
};

#endif // RAY_H
