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

Ray* Ray::generateRay(Primitive* p, Vec3 intersectPoint, Material initialEnv) {
    //End the loop here
    if (this->timer == 1) {
        static Ray* result = new Ray(Vec3(0, 0, 0), 1);
        delete this;
        return result;
    } else {
        //Forces us to eventually stop using the same ray
        this->timer -= 1;
    }

    //Transparent objects refract light and Opaque reflects
    static Ray* result = (!p->isTransparent())
            ? new Ray(p->reflect(Vec3(this->vector), intersectPoint), timer)
            : new Ray(p->refract(initialEnv, Vec3(this->vector), intersectPoint), timer);

    return result;
}
