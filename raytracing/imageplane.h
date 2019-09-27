#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "OpenGP/Eigen/Image.h"
#include "OpenGP/Image/Image.h"

using namespace OpenGP;

class ImagePlane
{
public:
    ImagePlane();

    ImagePlane(Vec3 ll, Vec3 ur, uint resW, uint resH);

    long long rows();

    long long cols();
public:
    Vec3 lowerLeft, upperRight;
    Image<Vec3> img;
};

#endif // IMAGEPLANE_H
