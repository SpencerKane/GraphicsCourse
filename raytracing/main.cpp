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
#include "ray.h"

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

bool getIsInShadow(Vec3 intersectPoint, Scene scene) {
    Vec3 shadowRay = intersectPoint - scene.light->center;
    shadowRay.normalize();

    //Check to see if any primitives lie between thisone and the
    for (std::list<Primitive*>::iterator iter = scene.primitives.begin();
         iter != scene.primitives.end(); ++iter) {

        if((*iter)->calculateIntersectDistance(shadowRay, intersectPoint) > 0.00001f) {
            return true; //Something is in the way
        }
    }

    return false; //No intersections in the direction of the ray
}

Vec3 doPhongShading(Scene scene, Primitive* p, Vec3 point, Vec3 ray) {
    Vec3 normal = p->calculateNormal(point);
    Vec3 lightdir = Vec3(scene.light->center);
    float angle = (normal.dot(lightdir));
    //float newangle = max(angle, 2.0f * 3.1415f - angle);
    //cout << normal.x() << ", " << normal.y() << ", " << normal.z() <<endl;
    //Calculate the shading of a point component-wise
    return p->mat.getColor() * p->mat.getDiffuseConstant() * angle
            + Vec3(1.0f, 1.0f, 1.0f) * p->mat.getSpecularConstant() * static_cast<float>(pow(p->reflect(ray, point).dot(scene.camera.viewDirection), p->mat.getGlossinessFactor()));
}

Vec3 sampleColors(Scene scene, Ray* ray) {
    //Extract variables from the scene
    list<Primitive*> primitives = scene.primitives;
    View camera = scene.camera;

    Vec3 color = Vec3(0, 0, 0);

    //Check each primitive for an intersection with ray
    for (std::list<Primitive*>::iterator iter = primitives.begin();
         iter != primitives.end(); ++iter) {
        //Get distance between vectors
        float t = (*iter)->calculateIntersectDistance(Vec3(ray->vector), camera.viewLocation);

        //cout << "Type of iter: " << typeid ((*(*iter))).name() << endl;

        //cout << "Calculated the t, ray timer = " << ray->timer <<endl;

        if (t < 0.00001f) { //No visible interection, check next primtive
            //cout << "No intersection" << endl;
            continue;
        } else {
            //Opaque objects need to worry about shadow
            if (!(*iter)->isTransparent()
                       || !(*iter)->mat.getColor().isApprox(Vec3(1.0f, 1.0f, 1.0f))){
                //Sample color here
                color += doPhongShading(scene, (*iter), Vec3(ray->vector * t), Vec3(ray->vector));
            }

            //cout << "An intersect occurred, ray timer: " << ray->timer << endl;

            //If new ray is 0, then timer expired
            if (ray->timer == 1) {
                //cout <<"Timed out" <<endl;
                return color;
            }

            //Recurse through the scene
            Ray* newRay = ray->generateRay(*(iter), Vec3(ray->vector * t), AIR);
            if (ray != nullptr) {
                delete ray;
            }
            return color + sampleColors(scene, newRay);
        }
    }

    return color;
}

int main(int, char**){
    list<Primitive*> primitives = list<Primitive*>();

    //Define primitives and add them to the list
    Sphere* sphere = new Sphere(Vec3(1, 0, -10), 1.0f, CHROME);
    Plane* floor = new Plane(Vec3(1, 0, 0), Vec3(0, 0, 1), PEARL);

    cout << "Sphere position after init: " << Vec3(sphere->position) <<endl;
    primitives.push_front(floor);
    primitives.push_front(sphere);

    //Get our bearings
    Vec3 viewLocation = Vec3(0, 0, 0);//getViewLocation();
    View camera = View(Vec3(0, 1, 0)/*getUp()*/,  -1 * sphere->position - viewLocation, viewLocation);
    Basis b = Basis(camera);

    //Place image plane half-way between sphere and camera
    Vec3 centreOfImPlane = -1 * ((sphere->center - camera.viewLocation).norm() / (float) 6) * b.z;
    float imPlaneDimensions = 6.0f; //Scalable

    ImagePlane img = ImagePlane(Vec3(-1, -1, -1), //Gives me an
                                Vec3(1, 1, -1), //4 * imPlaneDimensions x imPlaneDimension
                                640, 640);//Resolution

    //Make a scene
    Light *pl = new PointLight(Vec3(-5, -5, -5));
    Scene scene = Scene(primitives, pl, Vec3(0.5f, 0.5f, 0.5f), camera);


    //For each piece of the image generate a ray
    for (int row = 0; row < img.rows(); ++row) {
        for (int col = 0; col < img.cols(); ++col) {
            float percentOfColumns = (float) col / img.cols();
            float percentOfRows = (float) row/img.rows();
            float widthOfImPlane = img.upperRight.x() - img.lowerLeft.x();
            float heightOfImPlane = widthOfImPlane;
            Ray* ray = new Ray(Vec3(img.lowerLeft + camera.viewLocation
                          + (percentOfColumns) * widthOfImPlane * Vec3(1, 0, 0)
                          + (percentOfRows) * (heightOfImPlane) * Vec3(0, 1, 0)));
            //cout << "Made a ray" << endl;
            float t = sphere->calculateIntersectDistance(Vec3(ray->vector), Vec3(camera.viewLocation));
            if (t < 0.00001f) {
                img.img(row, col) = Vec3(0, 0, 0);
                delete ray;
                continue;
            }

            img.img(row, col) = Vec3(1.5f, 0.5f, 0.5f);//+ doPhongShading(scene, sphere, Vec3(t * ray->vector), Vec3(ray->vector));

            delete ray;
        }
    }

    bmpwrite("../../out.bmp", img.img);
    imshow(img.img, "junk");

    return EXIT_SUCCESS;
}



