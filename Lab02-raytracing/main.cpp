#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"
#include <stdio.h>
#include <math.h>

using namespace OpenGP;

using Colour = Vec3; // RGB Value
Colour red() { return Colour(1.0f, 0.0f, 0.0f); }
Colour white() { return Colour(1.0f, 1.0f, 1.0f); }
Colour black() { return Colour(0.0f, 0.0f, 0.0f); }
Colour ambient() {return Colour(0.02f, 0.03f, 0.55f);}
Colour sphereColor() {return Colour(0.0f, 0.0f, 0.0f);}
static float intensity = 0.8f;
static float specularConstant = 0.9;

uchar BoundPixelValue(int shading)
{
    if (shading < 0) return 0;
    if (shading >= 255) return 255;
    return shading;
}

int main(int, char**){

    int wResolution = 640;
    int hResolution = 640;
    // #rows = hResolution, #cols = wResolution
    Image<Colour> image(hResolution, wResolution);

    /// TODO: define camera position, sphere center, sphere radius
    // example: Vec3 spherePos = Vec3(0, 5, 0);
    Vec3 cameraPos = Vec3(0, 0, 0);
    Vec3 cameraForward = Vec3(0, 0, -1);
    Vec3 cameraUp = Vec3(0, 1, 0);

    Vec3 sphereCentre = Vec3(0, 0, -10);
    float sphereRadius = 2.0f;
	
	///TODO: define lighting source. ambient and diffuse colors
    Vec3 lightingSource = Vec3(-5, -5, -5);
    float sphereDiffuse = 0.5f;//Between 0.3 and 1


    //Define the image plane's position
    Vec3 llc = Vec3(-1, -1, -1);
    Vec3 urc = Vec3(1, 1, -1);

    for (int row = 0; row < image.rows(); ++row) {
        for (int col = 0; col < image.cols(); ++col) {
            /// TODO: build primary rays
            // example: Vec3 o = Vec3(0,0,0);
            float pixelX = llc.x() + ((float) col / image.cols())
                    * (urc.x() - llc.x());
            float pixelY = llc.y() + ((float) row / image.rows())
                    * (urc.y() - llc.y());
            Vec3 ray = Vec3(pixelX, pixelY, -1);
            ray.normalize();

            /// TODO: ray sphere intersection (refer to the lectureslides for the equations)
            float A = ray.dot(ray); //Sum of the squares of the components of the ray
            /* Cross term between components of the ray and camera , and the ray and sphere */
            float B = 2 * ((cameraPos.dot(ray)) - sphereCentre.dot(ray));
            /* Square of camera and sphere components, cross of sphere
                and camera components, and sphere radius */
            float C = cameraPos.dot(cameraPos)
                    + sphereCentre.dot(sphereCentre)
                    - (2 * cameraPos.dot(sphereCentre))
                    - sphereRadius * sphereRadius;

            //Prepare to find the length of the ray
            float discriminant = (B * B) - (4 * A * C);
            float lengthOfRay = 0;

            //Find the distance from the intersectio to the origin
            if (discriminant < 0) {
                image(row, col) = white(); // No intersection
                continue;
            } else if (discriminant < 0.000001f && discriminant > -0.000001f) {
                lengthOfRay = (-B) / (2 * A); //Only a tangential intersection
            } else {
                float solution1 = (sqrt(discriminant) - B) / (2 * A);
                float solution2 = (-sqrt(discriminant) - B) / (2 * A);

                //Only intersect the at the smallest length
                if (solution1 < solution2) {
                    lengthOfRay = solution1;
                } else {
                    lengthOfRay = solution2;
                }
            }

            Vec3 intersectionPoint = lengthOfRay * ray;

            ///TODO: basic shading (ambient and diffuse)
            Vec3 N = intersectionPoint - sphereCentre;
            N.normalize();

            Vec3 R = ray + 2 * ray.dot(N) * N;
            R.normalize();
            image(row, col) = ambient()
                    + sphereColor() * sphereDiffuse * N.dot(lightingSource)
                    + Vec3(1,1,1) * specularConstant * pow(R.dot(cameraForward), 64);
       }
    }

    bmpwrite("../../out.bmp", image);
    imshow(image);

    return EXIT_SUCCESS;
}

