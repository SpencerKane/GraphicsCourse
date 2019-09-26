#include "imageplane.h"

ImagePlane::ImagePlane()
{
    lowerLeft = Vec3(-1, -1, -1);
    upperRight = Vec3(1, 1, -1);
    resW = 1000;
    resH = 1000;
}

ImagePlane::ImagePlane(Vec3 ll, Vec3 ur, uint resW, uint resH){
    lowerLeft = Vec3(ll);
    upperRight = Vec3(ur);
    this->resH = resH;
    this->resW = resW;
}
