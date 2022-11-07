#ifndef DISTANCELINES_H
#define DISTANCELINES_H

#include <QList>
#include <QPainter>
#include <QPointF>
#include "vector.h"

class DistanceLines
{
public:
    DistanceLines();
    void addPoint(QPointF point_mm);
    void setDistanceLine(float cell_mm);
    void clear();
    void paint(QPainter& p, const QPointF& moveP, const M4x4 &m);

private:
    float cell_mm = 0;
    struct Point {
        float x;
        float y;
        bool isExists = true;
    };
    struct DistPoints_mm {
        Point p1 = {0, 0, false};
        Point p2 = {0, 0, false};
        float distance;
    };
    QList<DistPoints_mm> distPoints_mm;

    void createFirstDist(const QPointF& point_mm);
    QVector3D toPointScreen(QPainter& painter, const Vector& v, const M4x4 &m);
    float radiansToDegrees(float radians);
    void paintArrow(QPainter &p, const QVector3D& pF1, const QVector3D& pF2);
    QPointF paintPointDist(QPainter &p, const M4x4 &m, float x, float y) const;
};

#endif // DISTANCELINES_H
