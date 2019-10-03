#include "imageplane.h"

ImagePlane::ImagePlane()
{
    lowerLeft = Vec3(-1, -1, -1);
    upperRight = Vec3(1, 1, -1);
    img = Image<Vec3>(1000, 1000);
}

ImagePlane::ImagePlane(Vec3 ll, Vec3 ur, uint resW, uint resH){
    lowerLeft = Vec3(ll);
    upperRight = Vec3(ur);

    this->img = Image<Vec3>(resW, resH);
}

long long ImagePlane::rows() {
    return this->img.rows();
}

long long ImagePlane::cols() {
    return this->img.cols();
}


