#include "scene.h"

Scene::Scene(list<Primitive*> primitives, Light *light, Colour ambientColor, View camera) {
    this->primitives = primitives;
    this->light = light;
    this->ambientColor = ambientColor;
    this->camera = View(camera.up, camera.viewDirection, camera.viewLocation);
}

Scene::Scene(list<Primitive*> primitives, Light *light, View camera) {
    *this = Scene(primitives, light, Colour(1.0f, 1.0f, 1.0f), camera);
}
