#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"
#include "scene.h"
#include "view.h"
#include "sphere.h"
#include "pointlight.h"
#include "plane.h"
#include "imageplane.h"
#include "material.h"
#include "MaterialConstants.cpp"
#include "basis.h"

#include <stdio.h>

using namespace OpenGP;

float getComponent(string componentName, string componentPurpose) {
    float result;

    //Prompt user
    cout << "Please enter a value for the "
            + componentName + " component for "
            + componentPurpose + ": ";

    //Get and return input
    cin >> result;
    return result;
}

Vec3 getViewLocation() {
    float cameraX, cameraY, cameraZ;
    const string purpose = "the camera position";

    //Get input from user
    cameraX = getComponent("X", purpose);
    cameraY = getComponent("Y", purpose);
    cameraZ = getComponent("Z", purpose);

    return Vec3(cameraX, cameraY, cameraZ);
}

Vec3 getUp() {
    float cameraX, cameraY, cameraZ;
    const string purpose = "the up direction";

    //Get input from user
    cameraX = getComponent("X", purpose);
    cameraY = getComponent("Y", purpose);
    cameraZ = getComponent("Z", purpose);

    return Vec3(cameraX, cameraY, cameraZ);
}

int main(int, char**){
    list<Primitive> primitives = list<Primitive>();

    //Define primitives and add them to the list
    Plane floor = Plane(Vec3(1, 0, 0), Vec3(0, 0, 1), PEARL);
    Sphere sphere = Sphere(Vec3(5, 5, -5), 2, CHROME);
    primitives.push_front(floor);
    primitives.push_front(sphere);

    //Get our bearings
    Vec3 viewLocation = getViewLocation();
    View camera = View(getUp(), sphere.position - viewLocation, viewLocation);
    Basis b = Basis(camera);

    //Place image plane half-way between sphere and camera
    Vec3 centreOfImPlane = ((sphere.center - camera.viewLocation).norm() / 2) * b.z;
    float imPlaneDimensions = 5.0f; //Put this here because I easily could scale this if desired

    ImagePlane img = ImagePlane(centreOfImPlane + imPlaneDimensions * (b.x + b.y), //Gives me an
                                centreOfImPlane - imPlaneDimensions * (b.x + b.y), //imPlaneDimensions x imPlaneDimension
                                1000, 1000);//Resolution                           //ImagePlane

    //For each piece of the image generate a ray
    for (int row = 0; row < img.rows(); ++row) {
        for (int col = 0; col < img.cols(); ++col) {

        }
    }

    return EXIT_SUCCESS;
}



