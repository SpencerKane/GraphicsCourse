#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "OpenGP/Eigen/Image.h"

using namespace OpenGP;

class ImagePlane
{
public:
    ImagePlane();

    ImagePlane(Vec3 ll, Vec3 ur, uint resW, uint resH);
public:
    Vec3 lowerLeft, upperRight;
    uint resW, resH;
};

#endif // IMAGEPLANE_H
