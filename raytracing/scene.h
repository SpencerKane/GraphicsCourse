#ifndef SCENE_H
#define SCENE_H

#include <list>
#include "primitive.h"
#include "view.h"
#include "imageplane.h"
#include "light.h"

using namespace std;

class Scene
{
public:
    Scene(list<Primitive*> primitives, Light* light, Colour ambientColor,
          View camera);

    Scene(list<Primitive*> primitives, Light* light, View camera);

public:
    list<Primitive*> primitives;

    //Light info
    Light* light;

    View camera;

    ImagePlane imagePlane;

    Vec3 ambientColor;
};

#endif // SCENE_H
