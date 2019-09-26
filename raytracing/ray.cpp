#include "ray.h"

Ray::Ray(Vec3 vector){
    this->vector = Vec3(vector);
}

Ray::Ray(Vec3 vector, uint timer) {
    this->vector = Vec3(vector);
    this->timer = timer;
}

Ray::Ray(Ray *ray) {
    Ray(ray->vector, ray->timer - 1);
}

Ray Ray::generateRay(Primitive p, Vec3 intersectPoint, Material initialEnv) {
    //End the loop here
    if (this->timer == 0) {
        return Vec3(0, 0, 0);
    } else {
        //Forces us to eventually stop using the same ray
        --this->timer;
    }

    //Transparent objects refract light and Opaque reflects
    return (!p.isTransparent())
            ? Ray(p.reflect(this->vector, intersectPoint), this->timer - 1)
            : Ray(p.refract(initialEnv, this->vector, intersectPoint));
}
