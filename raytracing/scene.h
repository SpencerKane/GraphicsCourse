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
    Scene(list<Primitive> primitives, Vec3 lightPosition, Colour ambientColor,
          float lightIntensity, View camera);

    Scene(list<Primitive> primitives, Vec3 lightPosition, View camera);

public:
    list<Primitive> primitives;

    //Light info
    Light light;

    View camera;

    ImagePlane imagePlane;
};

#endif // SCENE_H
