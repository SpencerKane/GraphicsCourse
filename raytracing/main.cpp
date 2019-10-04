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

enum ColorCoordinate {
    Red = 0,
    Green = 1,
    Blue = 2
};

const Vec3 ambientLightColor = Vec3(.75f, 1.0f, .55f);
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

float calculateAmbientEffect(Primitive* p, ColorCoordinate color) {
    return p->mat.getAmbientConstant()[color] * ambientLightColor[color];
}

float calculateDiffuseEffect(Primitive* p, Vec3 point, Light* light, ColorCoordinate color) {
    Vec3 lightDir = light->center - point;
    lightDir.normalize();
    float coefficient = p->mat.getDiffuseConstant()[color]
            * p->calculateNormal(point).dot(lightDir);
    return coefficient * light->diffuseIntensity[color];
}

float calculateSpecularEffect(Primitive* p, Vec3 ray, Vec3 point,
                              Vec3 viewDir, Light* light, ColorCoordinate color) {
    Vec3 reflector = p->reflect(ray, point);
    reflector.normalize();

    float glossEffect = (float) pow(reflector.dot(viewDir), p->mat.getGlossinessFactor());

    return p->mat.getSpecularConstant()[color] * glossEffect * light->specularIntensity[color];
}

float doPhongShadingComponent(Primitive* p, Light* light, Vec3 ray,
                              Vec3 intersectionPoint, Vec3 viewDir,
                              ColorCoordinate color, bool isInShadow) {
    float ambientValue = calculateAmbientEffect(p, color);
    float diffuseValue, specularValue;

    //If in shadow we only use ambient
    if (isInShadow) {
        diffuseValue = 0.0f;
        specularValue = 0.0f;
    } else {
        diffuseValue = calculateDiffuseEffect(p, intersectionPoint, light, color);
        specularValue = calculateSpecularEffect(p, ray, intersectionPoint, viewDir, light, color);
    }

    //Phong shading is sum of components
    return ambientValue + diffuseValue + specularValue;
}

Vec3 doPhongShading(Primitive* p, Light* light, Vec3 ray,
                    Vec3 intersectionPoint, Vec3 viewDir, bool isInShadow) {
    float red = doPhongShadingComponent(p, light, ray, intersectionPoint, viewDir, Red, isInShadow);
    float green = doPhongShadingComponent(p, light, ray, intersectionPoint, viewDir, Green, isInShadow);
    float blue = doPhongShadingComponent(p, light, ray, intersectionPoint, viewDir, Blue, isInShadow);

    return Vec3(red, green, blue);
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
//            if (!(*iter)->isTransparent()
//                       || !(*iter)->mat.getColor().isApprox(Vec3(1.0f, 1.0f, 1.0f))){
//                //Sample color here
//                color += doPhongShading(scene, (*iter), Vec3(ray->vector * t), Vec3(ray->vector));
//            }

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
    Sphere* sphere = new Sphere(Vec3(1, 0, -10), 1.0f, TURQUOISE);
    Plane* floor = new Plane(Vec3(1, 0, 0), Vec3(2, 0.025f, -1), Vec3(0, 0, -1), BRASS);

    primitives.push_front(floor);
    primitives.push_front(sphere);

    //Get our bearings
    Vec3 viewLocation = Vec3(0, 0, 0);//getViewLocation();
    View camera = View(Vec3(0, 1, 0)/*getUp()*/,  -1 * sphere->center - viewLocation, viewLocation);
    Basis b = Basis(camera);

    //Place image plane half-way between sphere and camera
    Vec3 centreOfImPlane = -1 * ((sphere->center - camera.viewLocation).norm() / (float) 6) * b.z;
    float imPlaneDimensions = 6.0f; //Scalable

    ImagePlane img = ImagePlane(Vec3(-1, -1, -1), //Gives me an
                                Vec3(1, 1, -1), //4 * imPlaneDimensions x imPlaneDimension
                                640, 640);//Resolution

    //Make a scene
    Light *pl = new PointLight(Vec3(3, 3, -1));
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
            float s = sphere->calculateIntersectDistance(Vec3(ray->vector), Vec3(camera.viewLocation));
            float t = floor->calculateIntersectDistance(Vec3(ray->vector), Vec3(camera.viewLocation));

            if (t < 0.00001f && s < 0.00001f) {
                img.img(row, col) = ambientLightColor;
                delete ray;
                continue;
            }

            bool isInShadow = false;
            Vec3 lightDir = pl->center - t * ray->vector, intersectPoint;
            lightDir.normalize();
            float sphereDistance, planeDistance, lightDistance;

            if (t < s) {
//                intersectPoint = t * ray->vector;
//                lightDistance = pl->calculateIntersectDistance(lightDir, intersectPoint);
//                sphereDistance = sphere->calculateIntersectDistance(lightDir, intersectPoint);
//                planeDistance = floor->calculateIntersectDistance(lightDir, intersectPoint);
//                isInShadow = (sphereDistance > 0 || planeDistance > 0);
                img.img(row, col) = doPhongShading(sphere, pl, ray->vector, s * ray->vector, Vec3(0, 0, -1), isInShadow);//+ doPhongShading(scene, sphere, Vec3(t * ray->vector), Vec3(ray->vector));
            } else {
//                intersectPoint = s * ray->vector;
//                lightDistance = pl->calculateIntersectDistance(lightDir, intersectPoint);
//                sphereDistance = sphere->calculateIntersectDistance(lightDir, intersectPoint);
//                planeDistance = floor->calculateIntersectDistance(lightDir, intersectPoint);
//                isInShadow = (sphereDistance > 0 || planeDistance > 0);
                img.img(row, col) = doPhongShading(floor, pl, ray->vector, t * ray->vector, Vec3(0, 0, -1), isInShadow);
            }
            delete ray;
        }
    }

    bmpwrite("../../out.bmp", img.img);
    imshow(img.img, "junk");

    return EXIT_SUCCESS;
}



