#include "matrix.h"
#include "vector.h"
#include <QDebug>
#include <cmath>

Vector::Vector(float x, float y, float z, float w)
{
    coordinate.x = x;
    coordinate.y = y;
    coordinate.z = z;
    coordinate.w = w;
}

Vector Vector::add(const Vector &v1, const Vector &v2)
{
    float w = v1.w() + v2.w();//w не должна равнятся нулю.
    return Vector(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z(), w == 0 ? 0.00000001 : w);
}

Vector Vector::substruct(const Vector &v1, const Vector &v2)
{
    return Vector(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z(), 1);
}

Vector Vector::crossProduct(const Vector &v1, const Vector &v2)
{
    return Vector(v1.y() * v2.z() - v1.z() * v2.y(),
                  v1.z() * v2.x() - v1.x() * v2.z(),
                  v1.x() * v2.y() - v1.y() * v2.x(),
                  1);
}

M4x4 Vector::crossProductMatrix(const Vector &v1, const Vector &v2)
{
    return {
                std::array<float, 4>{v1.x() * v2.x(), v1.x() * v2.y(), v1.x() * v2.z(), v1.x() * v2.w()},
                std::array<float, 4>{v1.y() * v2.x(), v1.y() * v2.y(), v1.y() * v2.z(), v1.y() * v2.w()},
                std::array<float, 4>{v1.z() * v2.x(), v1.z() * v2.y(), v1.z() * v2.z(), v1.z() * v2.w()},
                std::array<float, 4>{v1.w() * v2.x(), v1.w() * v2.y(), v1.w() * v2.z(), v1.w() * v2.w()},
    };
}

Vector Vector::multiK(const Vector &v, float k)
{
    return Vector({v.x() * k, v.y() * k, v.z() * k, v.w() * k});
}

float Vector::scalarProduct(const Vector &v1, const Vector &v2)
{
    float product = v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z() + v1.w() * v2.w();
    return product;
}

float Vector::getLength()
{
    return std::sqrt(
                this->coordinate.x * this->coordinate.x + this->coordinate.y * this->coordinate.y + this->coordinate.z * this->coordinate.z
                );
}

Vector Vector::normalize()
{
    const float length = getLength();

    this->coordinate.x /= length;
    this->coordinate.y /= length;
    this->coordinate.z /= length;

    return *this;
}

Vector Vector::toCaresion()
{
    float w = this->coordinate.w;
    float x = coordinate.x / w;
    float y = coordinate.y / w;
    float z = coordinate.z / w;
    w = coordinate.w / w;

    return {x, y, z, w};
}

float Vector::degreesToRadians(float degress)
{
    const float PI  = 3.141592653589793238463;
    float radians = PI / 180 * degress;
    return radians;
}
