#include "distancelines.h"
#include "matrix.h"
#include <QDebug>
#include <cmath>
#include "math.h"

DistanceLines::DistanceLines()
{

}

void DistanceLines::addPoint(QPointF point_mm)
{
    if (distPoints_mm.isEmpty()) {
        createFirstDist(point_mm);
        return;
    }
    DistPoints_mm lastDist_mm = distPoints_mm.last();
    if (lastDist_mm.p2.isExists) {//вторая точка сущестует
        createFirstDist(point_mm);
    } else {
        lastDist_mm.p2 = {(float)point_mm.x(), (float)point_mm.y(), true};//Вторая точка существует
        QPointF pF1 = QPointF(lastDist_mm.p1.x, lastDist_mm.p1.y);
        QPointF pF2 = QPointF(lastDist_mm.p2.x, lastDist_mm.p2.y);
        lastDist_mm.distance = Math::getDistance(pF1, pF2);
        distPoints_mm.removeLast();
        distPoints_mm.append(lastDist_mm);
    }
}



void DistanceLines::setDistanceLine(float cell_mm)
{
    this->cell_mm = cell_mm;
}

void DistanceLines::clear()
{
    distPoints_mm.clear();
}

void DistanceLines::paint(QPainter &p, const QPointF &moveP, const M4x4 &m)
{
    p.save();
    //Прорисовка точек дистанции
    for (int i = 0; i < distPoints_mm.size(); ++i) {
        float x = distPoints_mm[i].p1.x * 2 / cell_mm;//в координатах от -1 до 1
        float y = distPoints_mm[i].p1.y * 2 / cell_mm;//в координатах от -1 до 1
        QVector3D pF1 = toPointScreen(p, Vector(x, y, 0, 1), m);
        QVector3D pF2;

        if (distPoints_mm[i].p2.isExists) {
            x = distPoints_mm[i].p2.x * 2 / cell_mm;//в координатах от -1 до 1
            y = distPoints_mm[i].p2.y * 2 / cell_mm;//в координатах от -1 до 1
            pF2 = toPointScreen(p, Vector(x, y, 0, 1), m);

            //Текст
            p.save();
            QString text = QString::number(distPoints_mm[i].distance);
            float lenX = pF2.x() - pF1.x();//длина линии по X
            float lenY = pF2.y() - pF1.y();//длина линии по Y
            float distance = Math::getDistance(lenX, lenY);//дистанция между двумя точками
            QFont font;
            font.setPointSize(22);
            QFontMetrics metric(font);
            int pixelWidth = metric.horizontalAdvance(text);
            p.setFont(font);
            p.translate(QPointF(lenX / 2 + pF1.x(), lenY / 2 + pF1.y()));
            float multi = pF2.x() > pF1.x() ? -1 : 1;
            p.rotate(multi * radiansToDegrees(-std::asin(lenY / distance)));
            QPointF pText = QPointF(lenX / 2, 0);
            p.drawText(QPointF(- pixelWidth / 2, -5), text);
            p.restore();
        } else {
            x = moveP.x() * 2 /  cell_mm;//в координатах от -1 до 1
            y = moveP.y() * 2 / cell_mm;//в координатах от -1 до 1
            pF2 = toPointScreen(p, Vector(x, y, 0, 1), m);;

            QPen pen;
            pen.setDashPattern({ 7, 10 });
            p.setPen(pen);
        }

        p.drawLine(pF1.toPointF(), pF2.toPointF());
        paintArrow(p, pF1, pF2);
        paintArrow(p, pF2, pF1);
    }
    p.restore();
}

void DistanceLines::createFirstDist(const QPointF& point_mm)
{
    DistPoints_mm dist_mm;
    dist_mm.p1 = {(float)point_mm.x(), (float)point_mm.y(), true};
    dist_mm.p2 = {0, 0, false};//Вторая точка не существует
    distPoints_mm.append(dist_mm);
}

QVector3D DistanceLines::toPointScreen(QPainter& painter, const Vector &v, const M4x4 &m)
{
    Vector newV = Matrix::multiplyVector(
                m,
                v);
    newV = newV.toCaresion();
    float x = newV.x() * (painter.device()->width() / 2);
    float y = newV.y() * (painter.device()->width() / 2);

    return QVector3D(x + painter.device()->width() / 2, painter.device()->height() / 2 - y, newV.z());
}

float DistanceLines::radiansToDegrees(float radians)
{
    const float PI  = 3.141592653589793238463;
    float degress = radians * 180 / PI;
    return degress;
}

void DistanceLines::paintArrow(QPainter &p, const QVector3D &pF1, const QVector3D &pF2)
{
    p.save();
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);

    float lenX = pF2.x() - pF1.x();//длина линии по X
    float lenY = pF2.y() - pF1.y();//длина линии по Y
    float distance = Math::getDistance(lenX, lenY);//дистанция между двумя точками
    p.translate(pF1.toPointF());
    float multi = pF2.x() > pF1.x() ? -1 : 1;
    float zero = pF2.x() > pF1.x() ? 1 : 0;
    p.rotate(zero * 180 + (-45) + multi * radiansToDegrees(-std::asin(lenY / distance)));
    QPointF pText = QPointF(lenX / 2, 0);
    float r = 10;
    float rz = r - r * pF1.z();
    p.drawLine(QPoint(rz, 0), QPoint(0, 0));
    p.drawLine(QPoint(0, rz), QPoint(0, 0));
    p.restore();
}

QPointF DistanceLines::paintPointDist(QPainter &p, const M4x4 &m, float x, float y) const
{
    Vector v = Matrix::multiplyVector(
                m,
                Vector({x, y, 0, 1}));
    v.toCaresion();
    x = v.x() * (p.device()->width() / 2);
    y = v.y() * (p.device()->width() / 2);
    p.save();
    p.setBrush(QBrush(QColor(Qt::blue)));
    qreal r = 2;
    qreal rz = r - r * v.z();//Радиус окружности от расстояния
    QPointF pF = QPointF(x + p.device()->width() / 2 + rz, p.device()->height() / 2 - rz - y);
    p.drawEllipse(pF, rz * 2, rz * 2);
    p.restore();
    return pF;
}
