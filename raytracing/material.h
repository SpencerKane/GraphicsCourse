#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "OpenGP/Eigen/Image.h"
using namespace OpenGP;
using namespace std;

class Material
{
public:
    Material() {
        Material("", Vec3(1.0f, 1.0f, 1.0f));
    }

    Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB, float refracIndex, uint glossiness,
             bool isTransparent) {
        *this = Material(name, KaRGB, KdRGB, KsRGB, glossiness, isTransparent);
        this->setRefractiveIndex(refracIndex);
    }
    /**
     * @brief Material This is the base constructor for a material
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param isTransparent True iff the material is transparent
     */
    Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB, uint glossiness,
             bool isTransparent);

    /* Other Constructors */
    /**
     * @brief Material Produces a material, but assumes the material is not transparent
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     */
    Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB, uint glossiness);

    /**
     * @brief Material Produces a material assuming a glossiness factor of 32
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param isTransparent True iff the material is transparent
     */
    Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB,
             bool isTransparent);

    /**
     * @brief Material Produces a material assuming the glossiness is 32
     * and the material is opaque
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     */
    Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB);

    /**
     * @brief Material Produces a material assuming standard diffuse and specular constants
     * @param name The name of the material
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param isTransparent True iff the material is transparent
     */
    Material(string name, Vec3 KaRGB, uint glossiness, bool isTransparent);

    /**
     * @brief Material Produces a material assuming standard values for all constants
     * @param name The name of the material
     * @param isTransparent True iff the material is transparent
     */
    Material(string name, Vec3 KaRGB, bool isTransparent);

    /**
     * @brief Material Produces a KaRGBed material assuming it is opaque and
     * using standard values for all constants
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param isTransparent True iff the material is transparent
     */
    Material(string name, Vec3 KaRGB);

    /* Getters */
    /**
     * @brief getName Returns a copy of the name of the material
     * @return The name of the material
     */
    string getName();

    /**
     * @return The ambient constant of the material
     */
    Vec3 getAmbientConstant();

    /**
     * @return The diffuse constant of the material
     */
    Vec3 getDiffuseConstant();

    /**
     * @return The specular constant of the material
     */
    Vec3 getSpecularConstant();

    /**
     * @brief getRefractiveIndex Returns the refractive index of
     * the material as used in Snell's Law
     * @return An index for how light bends when passing through this material
     */
    float getRefractiveIndex();

    /**
     * @return The glossiness factor of the material
     */
    uint getGlossinessFactor();

    /**
     * @return True if light should pass through this material,
     * false otherwise
     */
    bool getIsTransparent();

    /* Setters */

    Vec3 setAmbientConstant(Vec3 KaRGB);

    Vec3 setDiffuseConstant(Vec3 KdRGB);

    Vec3 setSpecularConstant(Vec3 KsRGB);

    float setRefractiveIndex(float n);

    uint setGlossinessFactor(uint newAlpha);

    void setIsTransparent(bool isTransparent);

    bool willRefract(Material other);

private:
    /**
     * @brief truncate Returns a value within the given range
     * @param min The minimum wnd of the range
     * @param max The maximum end of the range
     * @param value The value being checked
     * @return The value if it is already in the range,
     * or the nearest end of the range if not
     */
    uint truncateInt(uint min, uint max, uint value) const {
        return static_cast<uint>(truncate(static_cast<float>(min),
                               static_cast<float>(max),
                               static_cast<float>(value)));
    }

    /**
     * @brief truncate Returns a value within the given range
     * @param min The minimum wnd of the range
     * @param max The maximum end of the range
     * @param value The value being checked
     * @return The value if it is already in the range,
     * or the nearest end of the range if not
     */
    float truncate(float min, float max, float value) const {
        if (value - min < 0.000001f) {
            return min;
        } else if (max - value < 0.00001f){
            return max;
        } else {
            return value;
        }
    }

    /**
     * @brief truncateVector Enforces all components are within a boundary
     * @param min The minimum value of all the components
     * @param max The maximum value of all the components
     * @param vector The vector being truncated
     * @return A vector whose components have been truncated
     */
    Vec3 truncateVector(float min, float max, Vec3 vector) {
        return Vec3(
                    truncate(min, max, vector.x()),
                    truncate(min, max, vector.y()),
                    truncate(min, max, vector.z())
                    );
    }


public:
    string name;
    Vec3 KaRGB;
    Vec3 KdRGB;//Diffuse Constant
    Vec3 KsRGB;//Specular Constant
    float refractiveIndex; //How light will bend passing through this material
    uint alpha;//Glossiness factor
    bool isTransparent;


};

#endif // MATERIAL_H
