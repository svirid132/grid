#ifndef MATRIX_H
#define MATRIX_H

#include <vector.h>
#include <array>
#include <QVector3D>

/**
 * @brief The MatrixData struct - структура данных матрицы. Можно сказать общий интерфейс
 */
struct MatrixData {
    float x = 0; // в какую точку смортрит наблюдатель по оси x. Значения в градусах
    float y = 0;// в какую точку смортрит наблюдатель по оси y. Значения в градусах.
    float rotationZ = 0; // поворот фигигуры вдоль оси z. Передавать градусы.
    float scale = 3; // масштаб. Увеличение, уменьшение размера. Делаем из этого эффект безразмерности фигуры
    float zoom = 1; // Приближение, отдаление зума камеры.
    float frustum = 1;//Усечение пирамиды
    float k3 = 1.5;//Коэфицент увеличение поворота
protected:
    void setData(const MatrixData& m) {
        (*this) = m;
    }
};

/**
 * @brief M4x4 - матрица 4 на 4
 */
typedef std::array<std::array<float, 4>, 4> M4x4;
typedef std::array<std::array<float, 3>, 3> M3x3;
typedef std::array<std::array<float, 2>, 2> M2x2;

class Matrix
{
public:
    Matrix();
    /**
    * @brief multiply умножение матриц
    * @param a
    * @param b
    * @return новая матрица
    */
    static M4x4 multiply(const M4x4& a, const M4x4& b);
    /**
    * @brief getTranslation матрица перемещения
    * @param dx
    * @param dy
    * @param dz
    * @return новая матрица
    */
    static M4x4 getTranslation(float dx, float dy, float dz);
    /**
    * @brief getLookAt матрица вида. Указывает куда смотреть.
    * @param eye Наблюдаеть. Откуда смотрит.
    * @param target В какую точку смотрить наблюдатель
    * @param up указывает вверх сцены. То есть если вектор dy = 1, то сцена повернута вверх по направлению dy.
    * @return новая матрица
    */
    static M4x4 getLookAt(const Vector& eye, const Vector& target, const Vector& up);
    /**
    * @brief getScale матрица увеличения
    * @param sx
    * @param sy
    * @param sz
    * @return новая матрица
    */
    static M4x4 getScale(float sx, float sy, float sz);
    /**
    * @brief getRotationZ - поворот фигуры вдоль оси z
    * @param angle - измеряется в радианах
    * @return новая матрица
    */
    static M4x4 getRotationZ(float angle);
    static M4x4 getRotationX(float angle);
    static M4x4 getRotationY(float angle);
    /**
     * @brief difference - разность двух матриц
     * @param m1
     * @param m2
     * @return
     */
    static M4x4 difference(const M4x4 m1, const M4x4 m2);
    /**
     * @brief I - единичная матрица
     * @param k - по какому коэффиценту
     * @return
     */
    static M4x4 I(float k);
    /**
    * @brief multiplyVector - Умножение матрицы на квектор получается вектор
    * @param m
    * @param v
    * @return
    */
    static Vector multiplyVector(const M4x4& m, const Vector& v);
    /**
    * @brief getFrustum - усечение пирамиды. Необходим для перспективы.
    * @param left - левый край экрана.
    * @param right - правый край экрана.
    * @param bottom - нижний край экрана.
    * @param top - верхний край экрана.
    * @param near - ближняя проекция.
    * @param far дальняя проекция
    * @return матрица
    */
    static M4x4 getFrustum(float left, float right, float bottom, float top, float near, float far);

    static void debugM4x4(const M4x4 &m);
private:
    float m[4][4];
};

#endif // MATRIX_H
