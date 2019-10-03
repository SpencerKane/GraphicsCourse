#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "OpenGP/Eigen/Image.h"
#include "material.h"
#include "view.h"

using namespace OpenGP;

class Primitive {
public:
    /*
     * Given a point on the primitive object,
     * a normalized vector that is orthogonal to
     * the primitive's surface is generated
     *
     * @return A Vector normal to the primitive's surface
     * at the point and who's norm is 1
     */
    virtual Vec3 calculateNormal(Vec3 point) const = 0;

    /*
     * Given a ray, calculates the multiple needed to intersect
     * the primitive. Negative return values implies the ray doesn't
     * intersect the primitive
     */
    virtual float calculateIntersectDistance(Vec3 ray, Vec3 camera) const = 0;

    /* Virtual Destructor */
    virtual ~Primitive() {}

    Vec3 reflect(Vec3 ray, Vec3 point) const {
        Vec3 normal = calculateNormal(point);

        Vec3 reflection = ray - (2 * ray.dot(normal) * normal);
        return reflection;
    }

    bool isTransparent() {
        return mat.getIsTransparent();
    }

    /**
     * @brief refract Either returns a refractor ray, or (0, 0, 0)
     * if the materials aren't transparent
     * @param other The other material the light is passing through
     * @return A vector that results from bending through this material
     */
    Vec3 refract(Material other, Vec3 light, Vec3 point) {
        //Refract doesn't really happen if the two materials are opaque
        if (!this->isTransparent() || !other.getIsTransparent()) {
            return Vec3(0, 0, 0);
        }

        //No rafraction between two objects of the same material
        if (!this->mat.willRefract(other)) {
            return light;
        }

        //Rename variables, get a normal
        float n1 = this->mat.getRefractiveIndex(),
                n2 = other.getRefractiveIndex(),
                refRatio = n1 / n2; //Refractive ratio

        Vec3 normal = this->calculateNormal(point);
        float dotProduct = light.dot(normal);

        return Vec3(refRatio * (light + (dotProduct * normal))
                    - (normal *
                       sqrt(1 - pow(refRatio, 2)
                            * sqrt(1 - pow(dotProduct, 2))//End Inner sqrt
                            )//End outer sqrt
                       )//End 2nd operand for "-"
                    );

    }


public:
    Material mat;
    Vec3 center;
};

#endif // PRIMITIVE_H
