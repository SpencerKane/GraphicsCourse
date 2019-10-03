#include "view.h"

View::View(Vec3 up, Vec3 viewDir, Vec3 viewLoc) {
    up.normalize();
    viewDir.normalize();
    viewLocation.normalize();

    this->up = Vec3(up);
    this->viewLocation = Vec3(viewLoc);
    this->viewDirection = Vec3(viewDir);
}

View::View() {
    this->up = Vec3(0, 1, 0);
    this->viewDirection = Vec3(0, 0, -1);
    this->viewLocation = Vec3(0, 0, 0);
}
