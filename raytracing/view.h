#ifndef VIEW_H
#define VIEW_H
#include "OpenGP/Eigen/Image.h"
using namespace OpenGP;

class View
{
public:
    View(Vec3 up, Vec3 viewDir, Vec3 viewLoc);
    View();

public:
    Vec3 up, viewDirection, viewLocation;
};

#endif // VIEW_H
