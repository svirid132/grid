#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <array>

class Matrix;
/**
 * @brief M4x4 - матрица 4 на 4
 */
typedef std::array<std::array<float, 4>, 4> M4x4;
typedef std::array<std::array<float, 3>, 3> M3x3;
typedef std::array<std::array<float, 2>, 2> M2x2;


class Vector
{
public:
    Vector(float x, float y, float z, float w);
    /**
     * @brief add - сложение векторов
     * @param v1
     * @param v2
     * @return
     */
    static Vector add(const Vector& v1, const Vector& v2);
    /**
     * @brief substruct - векторное вычитание
     * @param v1 - первый вектор
     * @param v2 - второй вектор
     * @return
     */
    static Vector substruct(const Vector& v1, const Vector& v2);
    /**
     * @brief croosProduct - умножение векторов
     * @param v1
     * @param v2
     * @return
     */
    static Vector crossProduct(const Vector& v1, const Vector& v2);
    /**
     * @brief crossProductMatrix
     * @param v1 - столбец
     * @param v2 - строка
     * @return
     */
    static M4x4 crossProductMatrix(const Vector& v1, const Vector& v2);
    /**
     * @brief multiK - умножение вектора коэффицент K
     * @param v
     * @param k
     * @return
     */
    static Vector multiK(const Vector& v, float k);
    /**
     * @brief scalarProduct - скалярное произведение
     * @param v1
     * @param v2
     * @return
     */
    static float scalarProduct(const Vector& v1, const Vector& v2);
    float getLength();
    /**
     * @brief normalize - нормализация вектора
     * @return
     */
    Vector normalize();
    /**
     * @brief toCaresion - перевод в декартовые координаты
     */
    Vector toCaresion();

    /**
     * @brief degreesToRadians из градусов в радианы
     * @param degress - градусы
     * @return
     */
    static float degreesToRadians(float degress);

    float x() const { return coordinate.x; };
    float y() const { return coordinate.y; };
    float z() const { return coordinate.z; };
    float w() const { return coordinate.w; };

private:
    struct Coordinate {
        float x = 0;
        float y = 0;
        float z = 0;
        float w = 1;
    } coordinate;
};

#endif // VECTOR_H
