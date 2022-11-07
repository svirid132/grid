#ifndef SQUAREPOINTS_H
#define SQUAREPOINTS_H

#include <QList>
#include "vector.h"
#include "matrix.h"

struct SquarePointsData : MatrixData {
    SquarePointsData(const MatrixData& m) {
        SquarePointsData::MatrixData::setData(m);
    }
    float side = 0; // исходная длина квдрата
    float translationX = 0;
    float translationY = 0;
    //Не работает!
//    SquarePointsData& operator=(MatrixData&& m) {
//        SquarePointsData::MatrixData::setData(m);
//        return (*this);
//    }
};

class SquarePoints
{
public:
    SquarePoints();

    QPointF getOriginClicked(const SquarePointsData &data, const QPointF& clickedScreen, const QSize& screen);
private:
    QList<Vector> points;//Точки, которые показывают куда нажата мышка. Расположены слева направо.
    int pointSide = 100;//длина стороны кварата в точках sizeSquare x sizeSquare
    M4x4 calcMatrix(const SquarePointsData& data);
};

#endif // SQUAREPOINTS_H
