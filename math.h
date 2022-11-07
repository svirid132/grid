#ifndef MATH_H
#define MATH_H

#include <QLineF>
#include <QPoint>

/**
 * @brief The DirPoint enum - где находится точка от линии
 */
enum DirPoint {
    Minus,// слева или снизу
    Plus // справа или сверху
};

struct DistanceLine {
    float d;//растояние
    DirPoint dirPoint;
};

class Math
{
public:
//    Math();
    static float degreesToRadians(float degress);
    static float getDistance(const QPointF& p1, const QPointF& p2);
    static float getDistance(float lenX, float lenY);
    /**
     * @brief getDistanceLine - находим растояние между линией и точкой
     * @param p1 - первая точка на линии
     * @param p2 - вторая точка на линии
     * @param t - любая точка до которой нужно найти расстояние
     * @return
     */
    static DistanceLine getDistanceLine(const QLineF& line, QPointF pt);
};

#endif // MATH_H
