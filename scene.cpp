#include "scene.h"

Scene::Scene(list<Primitive> primitives, Vec3 lightPosition, Colour ambientColor,
      float lightIntensity, View camera) {
    this->primitives = primitives;
    this->lightPosition = lightPosition;
    this->ambientColor = ambientColor;
    this->ambientIntensity = lightIntensity;
    this->camera = camera;
}

Scene::Scene(list<Primitive> primitives, Vec3 lightPosition, View camera) {
    *this = Scene(primitives, lightPosition, Colour(1.0f, 1.0f, 1.0f),
                  1.0f, camera);
}
