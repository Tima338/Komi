#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <vector>
#include <algorithm>
#include <limits>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtCore/Qt>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include "point.h"
#include "edge.h"

// Класс для отображения графа и решения коммивояжера
class GraphWidget : public QGraphicsView
{
public:
    GraphWidget(std::vector<Point>& points, std::vector<Edge>& edges);

private:
    std::vector<Point>& points;
    std::vector<Edge>& edges;
    QGraphicsScene* scene;
    std::vector<int> tour;

    void solveTSP();
    void addPoint();
    void removePoint();
};

#endif // GRAPHWIDGET_H
