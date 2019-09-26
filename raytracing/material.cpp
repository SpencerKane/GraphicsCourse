#include "material.h"
#include "OpenGP/Eigen/Image.h"
#include <math.h>
using namespace OpenGP;
using namespace std;

static const float DIFFUSE = 0.5, SPECULAR = 0.5, PRECISION = 0.000001f;
static const uint GLOSSINESS = 32;
static bool IS_OPAQUE = false;


using Colour = Vec3;
    /**
     * @brief Material This is the base constructor for a material
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, float diffuse, float specular, uint glossiness,
                       Colour color, bool isTransparent) {
        //Users can't break these
        this->name = name;
        this->isTransparent = isTransparent;

        //Need to enforce restrictions on these
        this->setDiffuseConstant(diffuse);
        this->setSpecularConstant(specular);
        this->setGlossinessFactor(glossiness);
        this->color = truncateVector(0.0f, 1.0f, color);
    }

    /* Other Constructors */
    /**
     * @brief Material Produces a material, but assumes the material is not transparent
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     */
    Material::Material(string name, float diffuse, float specular, uint glossiness,
                       Colour color) {
        Material(name, diffuse, specular, glossiness, color, IS_OPAQUE);
    }

    /**
     * @brief Material Produces a material assuming a glossiness factor of 32
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, float diffuse, float specular, Colour color,
                       bool isTransparent) {
        Material(name, diffuse, specular, GLOSSINESS, color, isTransparent);
    }

    /**
     * @brief Material Produces a material assuming the glossiness is 32
     * and the material is opaque
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     */
    Material::Material(string name, float diffuse, float specular, Colour color) {
        Material(name, diffuse, specular, GLOSSINESS, color, IS_OPAQUE);
    }

    /**
     * @brief Material Produces a material assuming standard diffuse and specular constants
     * @param name The name of the material
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, uint glossiness, Colour color, bool isTransparent) {
        Material(name, DIFFUSE, SPECULAR, glossiness, color, isTransparent);
    }

    /**
     * @brief Material Produces a material assuming standard values for all constants
     * @param name The name of the material
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, Colour color, bool isTransparent) {
        Material(name, DIFFUSE, SPECULAR, GLOSSINESS, color, isTransparent);
    }

    /**
     * @brief Material Produces a colored material assuming it is opaque and
     * using standard values for all constants
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, Colour color) {
        Material(name, DIFFUSE, SPECULAR, GLOSSINESS, color, IS_OPAQUE);
    }

    /* Getters */
    /**
     * @brief getName Returns a copy of the name of the material
     * @return The name of the material
     */
    string Material::getName() {
        return string(this->name);
    }

    /**
     * @return The diffuse constant of the material
     */
    float Material::getDiffuseConstant() {
        return this->Kd;
    }

    /**
     * @return The specular constant of the material
     */
    float Material::getSpecularConstant() {
        return this->Ks;
    }

    /**
     * @brief getRefractiveIndex Returns the refractive index of
     * the material as used in Snell's Law
     * @return An index for how light bends when passing through this material
     */
    float Material::getRefractiveIndex() {
        return this->refractiveIndex;
    }

    /**
     * @return The glossiness factor of the material
     */
    uint Material::getGlossinessFactor() {
        return this->alpha;
    }

    /**
     * @brief getColor Returns the color of the material in the form of vector with
     * components in the interval [0, 1]
     * @return The color of the material
     */
    Colour Material::getColor() {
        return this->color;
    }

    /**
     * @return True if light should pass through this material,
     * false otherwise
     */
    bool Material::getIsTransparent() {
        return this->isTransparent;
    }

    /* Setters */

    float Material::setDiffuseConstant(float Kd) {
        this->Kd = truncate(0.0f, 1.0f, Kd);
        return this->Kd;
    }

    float Material::setSpecularConstant(float Ks) {
        this->Ks = truncate(0.0f, 1.0f, Ks);
        return this->Ks;
    }

    float Material::setRefractiveIndex(float n) {
        this->refractiveIndex = min(1.0f, n);
        return this->refractiveIndex;
    }

    uint Material::setGlossinessFactor(uint newAlpha) {
        this->alpha = max(static_cast<uint>(1), newAlpha);
        return this->alpha;
    }

    void Material::setIsTransparent(bool isTransparent) {
        this->isTransparent = isTransparent;
    };

    bool Material::willRefract(Material other) {
        return abs(other.getRefractiveIndex() - this->getRefractiveIndex()) < PRECISION;
    }
