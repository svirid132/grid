#include "grid.h"

#include <QDebug>
#include <QDebug>
#include <QLabel>
#include <QLineF>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <QPushButton>
#include <QSpinBox>
#include <QVector2D>
#include <QVector3D>
#include <QtMath>
#include "math.h"

Grid::Grid(QWidget *parent)
    : QWidget{parent}
{
    this->setMouseTracking(true);

    QSpinBox* boxX = new QSpinBox(this);
    boxX->setPrefix("X: ");
    boxX->setStyleSheet("background-color: white;");
    boxX->setGeometry(600, 150, 100, 30);
    boxX->setRange(-100, 100);
    boxX->setValue(gridData.x);
    connect(boxX, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int x) {
        GridData data = this->getGridData();
        data.x = x;
        this->setGridData(data);
    });

    QSpinBox* boxY = new QSpinBox(this);
    boxY->setPrefix("Y: ");
    boxY->setStyleSheet("background-color: white;");
    boxY->setGeometry(600, 200, 100, 30);
    boxY->setRange(-100, 100);
    boxY->setValue(gridData.y);
    connect(boxY, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int y) {
        GridData data = this->getGridData();
        data.y = y;
        this->setGridData(data);
    });

    QSpinBox* boxZ = new QSpinBox(this);
    boxZ->setValue(gridData.rotationZ);
    boxZ->setPrefix("rotationZ: ");
    boxZ->setStyleSheet("background-color: white;");
    boxZ->setGeometry(600, 250, 100, 30);
    boxZ->setRange(-180, 180);
    connect(boxZ, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int z) {
        GridData data = this->getGridData();
        data.rotationZ = z;
        this->setGridData(data);
    });

    QSpinBox* boxHeight = new QSpinBox(this);
    boxHeight->setPrefix("height: ");
    boxHeight->setStyleSheet("background-color: white;");
    boxHeight->setGeometry(600, 300, 100, 30);
    boxHeight->setRange(1, 100000);
    boxHeight->setValue(gridData.height);
    connect(boxHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int h) {
        GridData data = this->getGridData();
        data.height = h;
        this->setGridData(data);
    });

    QSpinBox* boxScale = new QSpinBox(this);
    boxScale->setValue(gridData.scale);
    boxScale->setPrefix("scale: ");
    boxScale->setStyleSheet("background-color: white;");
    boxScale->setGeometry(600, 350, 100, 30);
    boxScale->setRange(1, 100);
    connect(boxScale, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int h) {
        GridData data = this->getGridData();
        data.scale = h;
        this->setGridData(data);
    });

    QSpinBox* boxPitchingX = new QSpinBox(this);
    boxPitchingX->setValue(0);
    boxPitchingX->setPrefix("pitchingX: ");
    boxPitchingX->setStyleSheet("background-color: white;");
    boxPitchingX->setGeometry(600, 400, 100, 30);
    boxPitchingX->setRange(-180, 180);
    connect(boxPitchingX, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int pitchingX) {
        GridData data = this->getGridData();
        data.pitchingX = pitchingX;
        this->setGridData(data);
    });

    QSpinBox* boxPitchingY = new QSpinBox(this);
    boxPitchingY->setValue(0);
    boxPitchingY->setPrefix("pitchingY: ");
    boxPitchingY->setStyleSheet("background-color: white;");
    boxPitchingY->setGeometry(600, 450, 100, 30);
    boxPitchingY->setRange(-180, 180);
    connect(boxPitchingY, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int pitchingY) {
        GridData data = this->getGridData();
        data.pitchingY = pitchingY;
        this->setGridData(data);
    });

    QSpinBox* boxb = new QSpinBox(this);
    boxb->setPrefix("bmm: ");
    boxb->setStyleSheet("background-color: white;");
    boxb->setGeometry(600, 650, 100, 30);
    boxb->setRange(1, 10000);
    boxb->setValue(bmm);
    connect(boxb, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int bmm) {
        this->bmm = bmm;
        this->repaint();
    });

    QDoubleSpinBox* boxAlpha = new QDoubleSpinBox(this);
    boxAlpha->setPrefix("alpha: ");
    boxAlpha->setStyleSheet("background-color: white;");
    boxAlpha->setGeometry(600, 700, 100, 30);
    boxAlpha->setRange(1, 10000);
    boxAlpha->setValue(alpha);
    connect(boxAlpha, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this](double alpha) {
        this->alpha = alpha;
        this->repaint();
    });

    init();
}

void Grid::setGridData(const GridData &data)
{
    gridData = data;
    this->repaint();
}

GridData Grid::getGridData()
{
    return gridData;
}

void Grid::setFixedSize(int w, int h)
{
    QWidget::setFixedSize(w, h);
    clearInit();
    init();
}

void Grid::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    calcGrid();
    paintGrid(p);
    //Точки, чтобы расчитать точное растояние
    calcDistPoint(p);
    distanceLines.setDistanceLine(cellLength_mm);
    distanceLines.paint(p, {externSelectedDx, externSelectedDy}, matrix);
}

void Grid::init(int count)
{
    //создаем вершины - точки
    int countVertiacal = count;//количество ячеек по вертикали(считаем слева на право)
    int countHorizontal = count;//количество ячеек по горизонтали(считаем сверху вниз)
    // всего ячеек countHorizontal x countVertiacal
    const int pointHorizontal = countHorizontal * 2 + 2;//6
    const int pointVertiacal = countVertiacal * 2 - 2;//2
    const int pointCount = pointHorizontal + pointVertiacal;
    const float intervalHorizontal = 2 / (float)countHorizontal; // 1
    const float intervalVertical = 2 / (float)countVertiacal;// 1
    float currentIntHor = 1;// Спуск сверху вниз
    float currentIntVer = -1 + intervalVertical;//спуск слева направо
    for (int i = 0; i < pointCount; ++i) {
        if (i < pointHorizontal) {
            if (i % 2) {
                vertices.append(Vector({1, currentIntHor, 0, 1}));//выполняется вторым
                currentIntHor -= intervalHorizontal;
            } else {
                vertices.append(Vector({-1, currentIntHor, 0, 1}));//Выполняется первым
            }
        } else {
            if (i % 2) {
                vertices.append(Vector({currentIntVer, -1, 0, 1}));//выполняется вторым
                currentIntVer += intervalVertical;
            } else {
                vertices.append(Vector({currentIntVer, 1, 0, 1})); //Выполняется первым
            }
        }
    }

    //Создаем пары индексов вершин для лниний
    const int vertical = countHorizontal + 1;//пары по вертикали
    const int horizontal = countVertiacal + 1;
    for (int i = 0; i < vertical; ++i) {
        edges.append({i*2, i*2 + 1});
    }
    sizeVertical = vertical;
    const int lastHorIndex = edges.size() - 1;
    std::array<int, 2> lastHorVal = edges[lastHorIndex];
    for (int i = 0; i < horizontal; ++i){
        if (i == 0) {//первая строка
            edges.append({0, lastHorVal[0]});
        } else if (i == horizontal - 1) {//последнияя строка
            edges.append({1, lastHorVal[1]});
        } else {
            const int magic = 2 * i;
            edges.append({lastHorVal[1] + magic - 1, lastHorVal[1] + magic});
        }
    }
}

Grid::LineV Grid::clipLine(const Vector &p1, const Vector &p2)
{
    Vector newP1 = p1;
    Vector newP2 = p2;
    if (newP1.w() > 0) {
        newP1 = clipLeftLine(newP1, newP2);
    }
    if(newP2.w() > 0) {
        newP2 = clipLeftLine(newP2, newP1);
    }

    return { newP1, newP2 };
}

Vector Grid::clipLeftLine(const Vector &clipP, const Vector &p2)
{
    //Отсечение по x
    float n = (clipP.x() > 0) ? -1 : 1;//максимальное отсечение. Второе условие из-за поворота камеры по оси z
    float k = (clipP.x() - n * clipP.w()) / (n * p2.w() - p2.x());

    Vector multiP2 = Vector::multiK(p2, k);
    Vector clipedP = Vector::add(clipP, multiP2);

    //Отсечение по y
    if(clipedP.w() > 0) {
        float n = (clipP.y() < 0) ? 1 : -1;//максимальное отсечение. Второе условие из-за поворота камеры по оси z
        float k = (clipedP.y() - n * clipedP.w()) / (n * p2.w() - p2.y());
        Vector multiP2 = Vector::multiK(p2, k);
        clipedP = Vector::add(clipedP, multiP2);
    }

    return clipedP;
}

QLineF Grid::drawLineScreen(QPainter &p, const Vector &v1, const Vector &v2)
{
    Vector newV1 = v1;
    Vector newV2 = v2;

    //Clip - отсечение
    if ((v1.w() > 0) || (v2.w() > 0)) {
        LineV line = clipLine(v1, v2);
        newV1 = line.v1;
        newV2 = line.v2;
    }

    float x1 = newV1.x() / newV1.w() * (this->width() / 2);
    float y1 = newV1.y() / newV1.w() * (this->width() / 2);
    float x2 = newV2.x() / newV2.w() * (this->width() / 2);
    float y2 = newV2.y() / newV2.w() * (this->width() / 2);
    QPointF p1(x1 + this->width() / 2, this->height() / 2 - y1);
    QPointF p2(x2 + this->width() / 2, this->height() / 2 - y2);

    p.drawLine(p1, p2);

    return {p1, p2};
}

void Grid::findSelectedCell(int indexEdge, const QLineF& line)
{
    DistanceLine distEdge = Math::getDistanceLine(
                {(float)line.p1().rx(), (float)line.p1().ry(), (float)line.p2().rx(), (float)line.p2().ry()},
                moveP);
    //Находим линии ближайшие к точке
    if (sizeVertical >= indexEdge) {
        if (distEdge.d < horDistLine.d) {
            horDistLine = distEdge;
            horEdges = edges[indexEdge];
            if (distEdge.dirPoint == DirPoint::Plus) {
                endHorEdges = indexEdge + 1 < edges.size() ?  edges[indexEdge + 1] : edges[indexEdge];
            } else {
                endHorEdges = indexEdge - 1 > 0 ? edges[indexEdge - 1] : edges[indexEdge];
            }
        }
    } else {
        if (distEdge.d < verDistLine.d) {
            verDistLine = distEdge;
            verEdges = edges[indexEdge];
            if (distEdge.dirPoint == DirPoint::Plus) {
                endVerEdges = indexEdge - 1 > 0 ?  edges[indexEdge - 1] : edges[indexEdge];
            } else {
                endVerEdges = indexEdge + 1 < edges.size() ? edges[indexEdge + 1] : edges[indexEdge];
            }
        }
    }

    //Перестановка, чтобы отрисовка работала нормально (для выделения ячейки)
    std::array<int, 2> middleEdges = {0, 0};
    if (endVerEdges[0] < verEdges[0]) {
        middleEdges = verEdges;
        verEdges = endVerEdges;
        endVerEdges = middleEdges;
    }
    middleEdges = {0, 0};
    if (endHorEdges[0] > horEdges[0]) {
        middleEdges = horEdges;
        horEdges = endHorEdges;
        endHorEdges = middleEdges;
    }
}

void Grid::calcDistPoint(QPainter& p)
{
    SquarePointsData squarePointsData = static_cast<MatrixData>(gridData);
    squarePointsData.translationX = vertices[verEdges[0]].x();//x на исходной сетке
    squarePointsData.translationY = vertices[horEdges[0]].y();
    squarePointsData.side = (float)1 / allIntCell;
    QPointF originPoint = squarePoints.getOriginClicked(squarePointsData, {moveP.rx(), moveP.ry()}, {this->width(), this->height()});
    externSelectedDx = originPoint.rx() * cellLength_mm / (float)2; //Точка в системе координат mm
    externSelectedDy = originPoint.ry() * cellLength_mm / (float)2;
}

void Grid::calcGrid()
{
    //Расчитываем матрицы и коэффиценты
    float height = gridData.height;//переводим мм в метры
    float cellCount = height * std::tan(Math::degreesToRadians(alpha)) / bmm;
    float k1 = 8;//коэффицент обрезание просмотра сетки. = 6
    float allCell = cellCount * k1 * gridData.scale;
    //TODO Виден скачок в сетке при изменеии отсояния и ширины. Нужно узнать зарание какие габариты сетки.
    allIntCell = ((int)ceil(allCell) % 2 == 0) ? ceil(allCell) : ceil(allCell) + 1;//размер всей сетки, чтобы соотношение было 2x2, 4x4, 6x6
    cellLength_mm = (float)allIntCell * bmm;//Узнаем ширину всей сетки
    gridData.frustum = cellCount / allIntCell * gridData.scale;
    matrix = Matrix::getScale(gridData.scale, gridData.scale, gridData.scale);
    matrix = Matrix::multiply(
                Matrix::getTranslation(0, 0, 1),
                matrix);
    matrix = Matrix::multiply(Matrix::getRotationZ(-Vector::degreesToRadians(gridData.rotationZ)),
                         matrix);
    matrix = Matrix::multiply(
                Matrix::getLookAt(
                    Vector({0, 0, 0, 1}), // where is the observer
                    Vector({-Vector::degreesToRadians(gridData.x) * gridData.k3, -Vector::degreesToRadians(gridData.y) * gridData.k3, -1, 1}), // where to look
                    Vector({0, 1, 0, 1})
                    ),
                matrix);
    matrix = Matrix::multiply(
                Matrix::getFrustum(-gridData.frustum, gridData.frustum, -gridData.frustum, gridData.frustum, -1, -1000),
                matrix
                );

    clearInit();
    init(allIntCell);//текстура
}

void Grid::testPaintCell(QPainter &p, const QList<Vector>& sceneVertices)
{
    p.save();
    p.setBrush(QBrush(QColor(Qt::green)));
    p.setPen(QPen(QColor(Qt::green)));
    drawLineScreen(p, sceneVertices[horEdges[0]], sceneVertices[horEdges[1]]);
    drawLineScreen(p, sceneVertices[endHorEdges[0]], sceneVertices[endHorEdges[1]]);
    drawLineScreen(p, sceneVertices[verEdges[0]], sceneVertices[verEdges[1]]);
    drawLineScreen(p, sceneVertices[endVerEdges[0]], sceneVertices[endVerEdges[1]]);
    p.restore();
}

void Grid::paintGrid(QPainter &p)
{
    p.save();
    QPen pen = QPen(Qt::green);
    p.setPen(pen);
    p.setRenderHint(QPainter::Antialiasing);
    QList<Vector> sceneVertices;
    for (int i = 0; i < vertices.size(); i++) {
        Vector vertex = Matrix::multiplyVector(
                    matrix,
                    vertices[i]);
        sceneVertices.append(vertex);
    }

    verDistLine = {1000000, DirPoint::Plus};
    horDistLine = {1000000, DirPoint::Plus};
    for (int i = 0; i < edges.size(); i++) {
        std::array<int, 2> e = edges[i];
        QLineF lineF = drawLineScreen(p, sceneVertices[e[0]], sceneVertices[e[1]]);
        findSelectedCell(i, lineF);
    }

    //Прорисовка ячейки сетки при наводке (тест)
//    testPaintCell(p, sceneVertices);
    p.restore();
}

void Grid::clearInit()
{
    vertices.clear();
    edges.clear();
}

void Grid::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    moveP = {(float)event->pos().x(), (float)event->pos().y()};
    this->repaint();
}

void Grid::mouseReleaseEvent(QMouseEvent *event)
{
    distanceLines.addPoint({externSelectedDx, externSelectedDy});
    this->repaint();
}
