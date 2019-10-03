#include "basis.h"

Basis::Basis(View camera)
{
    z = -1 * camera.viewDirection;
    x = camera.up.cross(z);
    y = x.cross(z);
}
