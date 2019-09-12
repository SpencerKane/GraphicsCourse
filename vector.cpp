#include "vector.h"

using namespace std;

/*
 * Changes the components of the left hand vector
 * to be that of the right in the equation
 */
Vector& Vector::operator=(const Vector& second) {
    x = second.x;
    y = second.y;
    z = second.z;

    return *this;
}

/*
 * Verifies whether two vectors are equal.
 * This equality is determined of two vectors
 * have the same respective components.
 */
bool Vector::operator==(const Vector& second) const {
    float precision = 0.00001f;
    return x - second.x < precision && y - second.y < precision
            && z - second.z < precision;
}

/*
 * Changes the component of the vector to be 0
 */
void Vector::Zero() {
   x = 0.0f;
   y = 0.0f;
   z = 0.0f;
}

/*
 * Returns a vector whose components are the same as the
 * given vector, but changes the sign
 */
Vector Vector::operator -() const {
    Vector result = Vector();

    //Modify components
    result.x = x * -1;
    result.y = y * -1;
    result.z = z * -1;

    return result;
}

/*
 * Returns a vector whose components are the differences of the
 * respective components of the given vectors
 */
Vector Vector::operator-(const Vector& second) const {
    Vector result = Vector();

    //Modify components
    result.x = x - second.x;
    result.y = y - second.y;
    result.z = z - second.z;

    return result;
}

/*
 * Returns a vector whose components are the sums of the respective
 * components of the given vectors
 */
Vector Vector::operator +(const Vector& second) const {
    Vector result = Vector();

    //Modify components
    result.x = x + second.x;
    result.y = y + second.y;
    result.z = z + second.z;

    return result;
}

/*
 * Returns the dot product between two vectors.
 *
 * Can be found by multiplying each vector's components respectively
 * and then summing those results.
 */
float Vector::operator *(const Vector& second) const {
    Vector product = Vector();

    //Multiply components respectively
    product.x = x * second.x;
    product.y = y * second.y;
    product.z = z * second.z;

    //Return the sum
    return product.x + product.y + product.z;
}

/*
 * Returns a vector whose components are the result of multiplying
 * each component of the given vector with the scalar
 */
Vector Vector::operator *(const float scalar) const {
    Vector result = Vector();

    //Multiply each componenty of the vector by the scalar
    result.x = x * scalar;
    result.y = y * scalar;
    result.z = z * scalar;

    return result;
}

/*
 * Returns a vector whose components are the result of dividing
 * each component of the given vector with the scalar
 */
Vector Vector::operator /(const float scalar) const {
    return *this * (1/scalar);
}

/*
 * Returns the magnitude of the vector
 */
float Vector::VectorMag() {
    return sqrt(*this * *this);
}

/*
 * Maintains the direction of the vector but reduces
 * the magnitude to 1. Alters the vector
 */
void Vector::Normalize() {
    float norm = this->VectorMag();
    x /= norm;
    y /= norm;
    z /= norm;
}

/*
 * Finds the cross poduct of two vectors.
 *
 * https://www.youtube.com/watch?v=v1RerGVd6C4
 */
Vector Vector::CrossProduct(const Vector &other) {
    Vector result;

    //Modify result - formula found by youtube clip
    //See function comment
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;

    return result;
}

/*
 * Outputs the vector in a user-friendly way to a given stream
 */
ostream& operator <<(ostream& stream, const Vector& vec) {
    stream << "x = " << vec.x << endl;
    stream << "y = " << vec.y << endl;
    stream << "z = " << vec.z << endl;

    return stream;
}

