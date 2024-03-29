#include "material.h"
#include "OpenGP/Eigen/Image.h"
#include <math.h>
using namespace OpenGP;
using namespace std;

static const Vec3 DIFFUSE = Vec3(0.5f, 0.5f, 0.5f), SPECULAR = Vec3(0.5f, 0.5f, 0.5f);
static const float PRECISION = 0.000001f;
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
    Material::Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB, uint glossiness,
                       bool isTransparent) {
        //Users can't break these
        this->name = name;
        this->isTransparent = isTransparent;

        //Need to enforce restrictions on these
        this->setAmbientConstant(KaRGB);
        this->setDiffuseConstant(KdRGB);
        this->setSpecularConstant(KsRGB);
        this->setGlossinessFactor(glossiness);
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
    Material::Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB, uint glossiness) {
        Material(name, KaRGB, KdRGB, KsRGB, glossiness, IS_OPAQUE);
    }

    /**
     * @brief Material Produces a material assuming a glossiness factor of 32
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, Vec3 KaRGB, Vec3 KdRGB, Vec3 KsRGB,
                       bool isTransparent) {
        Material(name, KaRGB, KdRGB, KsRGB, GLOSSINESS, isTransparent);
    }

    /**
     * @brief Material Produces a material assuming the glossiness is 32
     * and the material is opaque
     * @param name The name of the material
     * @param diffuse The diffuse constant of the material from 0 to 1
     * @param specular The specular constant of the material from 0 to 1
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     */
    Material::Material(string name, Vec3 KaRGB, Vec3 KdRGB,Vec3 KsRGB) {
        Material(name, KaRGB, KdRGB, KsRGB, GLOSSINESS, IS_OPAQUE);
    }

    /**
     * @brief Material Produces a material assuming standard diffuse and specular constants
     * @param name The name of the material
     * @param glossiness The glossiness factor, should be a small power of 2 (i.e 32)
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, Vec3 KaRGB, uint glossiness, bool isTransparent) {
        Material(name, KaRGB, DIFFUSE, SPECULAR, glossiness, isTransparent);
    }

    /**
     * @brief Material Produces a material assuming standard values for all constants
     * @param name The name of the material
     * @param color A Vec3 containing 3 floats between 0 and 1 representing the color of the material
     * @param isTransparent True iff the material is transparent
     */
    Material::Material(string name, Vec3 KaRGB, bool isTransparent) {
        Material(name, KaRGB, DIFFUSE, SPECULAR, GLOSSINESS, isTransparent);
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
    Material::Material(string name, Vec3 KaRGB) {
        Material(name, KaRGB, DIFFUSE, SPECULAR, GLOSSINESS, IS_OPAQUE);
    }

    /* Getters */
    /**
     * @brief getName Returns a copy of the name of the material
     * @return The name of the material
     */
    string Material::getName() {
        return string(this->name);
    }

    Vec3 Material::getAmbientConstant() {
        return this->KaRGB;
    }

    /**
     * @return The diffuse constant of the material
     */
    Vec3 Material::getDiffuseConstant() {
        return this->KdRGB;
    }

    /**
     * @return The specular constant of the material
     */
    Vec3 Material::getSpecularConstant() {
        return this->KsRGB;
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
     * @return True if light should pass through this material,
     * false otherwise
     */
    bool Material::getIsTransparent() {
        return this->isTransparent;
    }

    /* Setters */

    Vec3 Material::setAmbientConstant(Vec3 Ka) {
        this->KaRGB = truncateVector(0.0f, 1.0f, Ka);
        return this->KdRGB;
    }

    Vec3 Material::setDiffuseConstant(Vec3 Kd) {
        this->KdRGB = truncateVector(0.0f, 1.0f, Kd);
        return this->KdRGB;
    }

    Vec3 Material::setSpecularConstant(Vec3 Ks) {
        this->KsRGB = truncateVector(0.0f, 1.0f, Ks);
        return this->KsRGB;
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
