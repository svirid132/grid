#include "math.h"
#include <cmath>

//Math::Math()
//{
//}

float Math::degreesToRadians(float degress)
{
    const float PI  = 3.141592653589793238463;
    float radians = PI / 180 * degress;
    return radians;
}

float Math::getDistance(float lenX, float lenY)
{
    return std::sqrt(std::pow(lenX, 2) + std::pow(lenY, 2));
}

float Math::getDistance(const QPointF &p1, const QPointF &p2)
{
    return std::sqrt((double)(std::pow(p2.x() - p1.x(), 2) + std::pow(p2.y() - p1.y(), 2)));
}

DistanceLine Math::getDistanceLine(const QLineF& line, QPointF pt)
{
    QPointF p1 = line.p1();
    QPointF p2 = line.p2();
    float d = ((p1.ry() - p2.ry())*pt.rx() + (p2.rx() - p1.rx())*pt.ry() + (p1.rx()*p2.ry() - p2.rx()*p1.ry()))
            / std::sqrt(std::pow((p2.rx() - p1.rx()), 2) + std::pow((p2.ry() - p1.ry()) ,2));
    DirPoint dirPoint = d > 0 ? DirPoint::Plus : DirPoint::Minus;

    return DistanceLine({std::abs(d), dirPoint});
}


