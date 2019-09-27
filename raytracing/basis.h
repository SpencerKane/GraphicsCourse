#ifndef BASIS_H
#define BASIS_H

#include "view.h"

class Basis
{
public:
    Basis(View camera);

    Vec3 x, y, z;
};

#endif // BASIS_H
