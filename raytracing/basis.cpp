#include "basis.h"

Basis::Basis(View camera)
{
    x = -1 * camera.viewDirection;
    z = camera.up.cross(camera.viewDirection);
    y = x.cross(z);
}
