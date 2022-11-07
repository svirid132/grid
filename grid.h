#ifndef GRID_H
#define GRID_H

#include <QList>
#include <QPainter>
#include <QWidget>
#include "distancelines.h"
#include "matrix.h"
#include "squarepoints.h"
#include "math.h"

/**
 * @brief The gridData struct - струкрута данных для постороения сетки
 */
struct GridData : MatrixData {
    float height = 4001; // отстояние в сантиметрах. Отдаление, приближение сетки.
    float pitchingX = 0; // качка киливая. Подъем и спуск коробля.
    float pitchingY = 0; // качка курсовая. Пример, ударил волной борта корабля. Крениться в право, либо в лево.
};

class Grid : public QWidget
{
    Q_OBJECT
public:
    explicit Grid(QWidget *parent = nullptr);
    void setGridData(const GridData& data);
    GridData getGridData();
    void setFixedSize(int w, int h);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    SquarePoints squarePoints;
    DistanceLines distanceLines;
    GridData gridData;
    M4x4 matrix;//матрица сетки
    float cellLength_mm;//Длина всей сетки
    int allIntCell;//Всего ячеек сетки
    float bmm = 1000;//размер ячейки в мм
    float alpha = 45;//Угол обзора камеры. Наподобие закрытия и открытия глаза. В градусах.
    QPointF moveP;//Двигаем мышкой
    //Количество edge пар по вертикали
    int sizeVertical = 0;
    int sizePoint = 0;//Сколько точек у квадрата по горизонтали или вертикали (квадрат для расстояния)
    //Точки по которым кликнули мышкой. Они расчитываются в мм.
    float externSelectedDx;
    float externSelectedDy;
    //Вершины образующие при пересечении квадрат.
    std::array<int, 2> verEdges = {0, 0};
    std::array<int, 2> endVerEdges = {0, 0};
    std::array<int, 2> horEdges = {0, 0};
    std::array<int, 2> endHorEdges = {0, 0};
    //растояние между линией сетки и курсором мыши
    DistanceLine verDistLine = {1000000, DirPoint::Plus};
    DistanceLine horDistLine = {1000000, DirPoint::Plus};
    QList<Vector> vertices; // Вершины - точки
    QList<std::array<int, 2>> edges; // пары индексов вершин, то есть [1, 2]. Нужны, чтобы из индексов вершин нарисовать линию.

    struct LineV {
        Vector v1;
        Vector v2;
    };

    /**
     * @brief clipLine - Отрезать линию. Чтобы прорисовка линии была нормальной.Проблемы с прорисвкой возникаю при w < 0
     * @param p1
     * @param p2
     * @return
     */
    LineV clipLine(const Vector& p1, const Vector& p2);
    /**
     * @brief clipLeftLine - отсичение линни по левой стороне
     * @param clipP - отсичение точки
     * @param p2
     * @return
     */
    Vector clipLeftLine(const Vector& clipP, const Vector& p2);
    /**
     * @brief drawLineScreen - рисует на экране линию
     * @param p = рисовальщик
     * @param v1 - вершина 1 в однородных координатах
     * @param v2 - вершина 2 в однородных координатах
     * @return - возварщает точки которые создаются при начертываниии линии
     */
    QLineF drawLineScreen(QPainter &p, const Vector& v1, const Vector& v2);
    /**
     * @brief findSelectedCell - находит ячейку сетки, на которой лежит курсор мыши. Заполняет:
     * verEdges, endVerEdges, horEdges, endHorEdges
     * @param indexEdge - индекс текущего edge - пары точек
     * @param line - линия, которая выводится на экран монитора
     */
    void findSelectedCell(int indexEdge, const QLineF& line);
    /**
     * @brief calcDistPoint - расчитываем точки ячейки, чтобы узнать точное растояние, где находится точка в пространстве
     */
    void calcDistPoint(QPainter& p);
    void calcGrid();
    /**
     * @brief testPaintCell - тест на выделение правильной ячейки
     * @param p
     */
    void testPaintCell(QPainter& p, const QList<Vector>& sceneVertices);
    void paintGrid(QPainter& p);
    void init(int count = 100);
    void clearInit();
};

#endif // GRID_H
