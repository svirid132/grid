#include "squarepoints.h"

#include <QDebug>
#include <QSize>
#include "math.h"

SquarePoints::SquarePoints()
{
    float interval = 2 / ((float)pointSide - 1);
    float y = -1;
    for (int i = 0; i < pointSide; ++i) {
        float x = -1;
        for (int a = 0; a < pointSide; ++a) {
            points.append(Vector({x, y, 0, 1}));
            x += interval;
        }
        y += interval;
    }
}

QPointF SquarePoints::getOriginClicked(const SquarePointsData &data, const QPointF& clickedPoint, const QSize& screen) {
    M4x4 mp = calcMatrix(data);
    QList<Vector> scenceVerticesPoints;
    Matrix::debugM4x4(mp);
    for (int i = 0; i < points.size(); i++) {
        Vector vertex = Matrix::multiplyVector(
                    mp,
                    points[i]);
        vertex = vertex.toCaresion();
        float x = vertex.x() * (screen.width() / 2);
        float y = vertex.y() * (screen.width() / 2);
        scenceVerticesPoints.append(Vector({x, y, vertex.z(), vertex.w()}));
    }

    std::pair<double, QPoint> minDistance = {100000, QPoint(0,0)};
    float selectedDx = 0;
    float selectedDy = 0;
    float originX = data.translationX;
    float originY =  data.translationY;
    float interval = (float)data.side * 2 / (float)pointSide;//интервал между ячейками у исходного квадратя для растояния
    for (int i = 0; i < points.size(); i++) {
        Vector v = scenceVerticesPoints[i];
        QPoint point = QPoint(v.x() + screen.width() / 2, screen.height() / 2 - v.y());
//        p.drawEllipse(point, 1, 1);
        float distance = Math::getDistance(clickedPoint, point);
        if(minDistance.first > distance) {
            minDistance.first = distance;
            minDistance.second = point;
            selectedDx = originX + (interval * (i % pointSide));
            selectedDy = originY + (interval * (i / pointSide));
        };
    }

    return QPointF(selectedDx, selectedDy);
}

M4x4 SquarePoints::calcMatrix(const SquarePointsData &data)
{
    float scale = (float)data.scale * data.side;
    qDebug() << data.scale << data.side;
    M4x4 mp = Matrix::getScale(scale, scale, scale);
    //Раньше
//    double dx = vertices[verEdges[0]].x();//x на исходной сетке
//    double dy = vertices[horEdges[0]].y();//y на исходной сетке
    mp = Matrix::multiply(
                Matrix::getTranslation(data.scale * (data.translationX + data.side), data.scale * (data.translationY + data.side), 1),
                mp);
    mp = Matrix::multiply(Matrix::getRotationZ(-Vector::degreesToRadians(data.rotationZ)),
                         mp);
    mp = Matrix::multiply(
                Matrix::getLookAt(
                    Vector({0, 0, 0, 1}), // where is the observer
                    Vector({-Vector::degreesToRadians(data.x) * data.k3, -Vector::degreesToRadians(data.y) * data.k3, -1, 1}), // where to look
                    Vector({0, 1, 0, 1})
                    ),
                mp);
    mp = Matrix::multiply(
                Matrix::getFrustum(-data.frustum, data.frustum, -data.frustum, data.frustum, -1, -1000),
                mp
                );

    return mp;
}
