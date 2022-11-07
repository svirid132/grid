#include "matrix.h"
#include <QDebug>
#include <QLineF>
#include <QVector4D>
#include <cmath>

Matrix::Matrix()
{

}

M4x4 Matrix::multiply(const M4x4 &a, const M4x4 &b)
{
    M4x4 m;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = a[i][0] * b[0][j] +
                    a[i][1] * b[1][j] +
                    a[i][2] * b[2][j] +
                    a[i][3] * b[3][j];
        }
    }

    return m;
}

M4x4 Matrix::getTranslation(float dx, float dy, float dz)
{
    return {
        std::array<float, 4>{1, 0, 0, dx},
        std::array<float, 4>{0, 1, 0, dy},
        std::array<float, 4>{0, 0, 1, dz},
        std::array<float, 4>{0, 0, 0, 1}
    };
}

void Matrix::debugM4x4(const M4x4 &m)
{
    qDebug() << "matrix:";
    for (int i = 0; i < 4; ++i) {
        QString str = QString::number(i) + ": ";
        for (int a = 0; a < 4; ++a) {
            str += QString::number(m[i][a]) + " ";
        }
        qDebug() << str;
    }
}

M4x4 Matrix::getLookAt(const Vector &eye, const Vector &target, const Vector &up)
{
    Vector vz = Vector::substruct(eye, target).normalize();
    Vector vx = Vector::crossProduct(up, vz).normalize();
    Vector vy = Vector::crossProduct(vz, vx).normalize();

    M4x4 m = {
        std::array<float, 4>{vx.x(), vx.y(), vx.z(), 0},
        std::array<float, 4>{vy.x(), vy.y(), vy.z(), 0},
        std::array<float, 4>{vz.x(), vz.y(), vz.z(), 0},
        std::array<float, 4>{0, 0, 0, 1}
    };

    return Matrix::multiply(
                Matrix::getTranslation(-eye.x(), -eye.y(), -eye.z()),
                m
                );
}

M4x4 Matrix::getScale(float sx, float sy, float sz)
{
    return {
        std::array<float, 4>{sx, 0, 0, 0},
        std::array<float, 4>{0, sy, 0, 0},
        std::array<float, 4>{0, 0, sz, 0},
        std::array<float, 4>{0, 0, 0, 1}
    };
}

M4x4 Matrix::getRotationZ(float angle)
{
    return {
        std::array<float, 4>{std::cos(angle), -std::sin(angle), 0, 0},
        std::array<float, 4>{std::sin(angle), std::cos(angle), 0, 0},
        std::array<float, 4>{0, 0, 1, 0},
        std::array<float, 4>{0, 0, 0, 1}
    };
}

M4x4 Matrix::getRotationX(float angle)
{
    return {
        std::array<float, 4>{1, 0, 0, 0},
        std::array<float, 4>{0, std::cos(angle), -std::sin(angle), 0},
        std::array<float, 4>{0, std::sin(angle), std::cos(angle), 0},
        std::array<float, 4>{0, 0, 0, 1}
    };
}

M4x4 Matrix::getRotationY(float angle)
{
    return {
        std::array<float, 4>{std::cos(angle), 0, std::sin(angle), 0},
        std::array<float, 4>{0, 1, 0, 0},
        std::array<float, 4>{-std::sin(angle), 0, std::cos(angle), 0},
        std::array<float, 4>{0, 0, 0, 1}
    };
}

M4x4 Matrix::difference(const M4x4 m1, const M4x4 m2)
{
    return {
        std::array<float, 4>{m1[0][0] - m2[0][0], m1[0][1] - m2[0][1], m1[0][2] - m2[0][2], m1[0][3] - m2[0][3]},
        std::array<float, 4>{m1[1][0] - m2[1][0], m1[1][1] - m2[1][1], m1[1][2] - m2[1][2], m1[1][3] - m2[1][3]},
        std::array<float, 4>{m1[2][0] - m2[2][0], m1[2][1] - m2[2][1], m1[2][2] - m2[2][2], m1[2][3] - m2[2][3]},
        std::array<float, 4>{m1[3][0] - m2[3][0], m1[3][1] - m2[3][1], m1[3][2] - m2[3][2], m1[3][3] - m2[3][3]}
    };
}

M4x4 Matrix::I(float k)
{
    return {
        std::array<float, 4>{k, 0, 0, 0},
        std::array<float, 4>{0, k, 0, 0},
        std::array<float, 4>{0, 0, k, 0},
        std::array<float, 4>{0, 0, 0, k}
    };
}

Vector Matrix::multiplyVector(const M4x4 &m, const Vector &v)
{
    return Vector({
                      m[0][0] * v.x() + m[0][1] * v.y() + m[0][2] * v.z() + m[0][3] * v.w(),
                      m[1][0] * v.x() + m[1][1] * v.y() + m[1][2] * v.z() + m[1][3] * v.w(),
                      m[2][0] * v.x() + m[2][1] * v.y() + m[2][2] * v.z() + m[2][3] * v.w(),
                      m[3][0] * v.x() + m[3][1] * v.y() + m[3][2] * v.z() + m[3][3] * v.w()
                  });
}

M4x4 Matrix::getFrustum(float left, float right, float bottom, float top, float near, float far)
{
    return {
        std::array<float, 4>{2 * near / (right - left), 0, (right + left) / (right - left), 0},
        std::array<float, 4>{0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0},
        std::array<float, 4>{0, 0, -(far + near) / (far - near), -2*far*near/(far- near)},
        std::array<float, 4>{0, 0, -1, 0}
    };
}
