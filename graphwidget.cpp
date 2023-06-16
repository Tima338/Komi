#include "graphwidget.h"
#include <iostream>

// Конструктор класса GraphWidget
GraphWidget::GraphWidget(std::vector<Point>& points, std::vector<Edge>& edges)
    : points(points), edges(edges)
{
    // Создание сцены и установка фона
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::white);
    setScene(scene);

    // Установка размеров области просмотра
    setRenderHint(QPainter::Antialiasing);
    setMinimumSize(800, 600);

    // Создание точек на сцене
    for (int i = 0; i < points.size(); ++i)
    {
        QGraphicsEllipseItem* item = scene->addEllipse(points[i].x - 5, points[i].y - 5, 10, 10, QPen(Qt::black), QBrush(Qt::black));
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QGraphicsSimpleTextItem* textItem = scene->addSimpleText(QString::number(i));
        textItem->setPos(points[i].x - 10, points[i].y - 20);
    }

    // Создание ребер на сцене
    for (const Edge& edge : edges)
    {
        QGraphicsLineItem* item = scene->addLine(points[edge.src].x, points[edge.src].y, points[edge.dest].x, points[edge.dest].y, QPen(Qt::blue));
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QGraphicsSimpleTextItem* textItem = scene->addSimpleText(QString::number(edge.weight));
        textItem->setPos((points[edge.src].x + points[edge.dest].x) / 2, (points[edge.src].y + points[edge.dest].y) / 2);
    }

    solveTSP();

    // Кнопка "Добавить пункт"
    QPushButton* addButton = new QPushButton("Добавить пункт", this);
    addButton->move(10, 10);
    connect(addButton, &QPushButton::clicked, this, &GraphWidget::addPoint);

    // Кнопка "Удалить пункт"
    QPushButton* removeButton = new QPushButton("Удалить пункт", this);
    removeButton->move(10, 40);
    connect(removeButton, &QPushButton::clicked, this, &GraphWidget::removePoint);
}

void GraphWidget::solveTSP()
{
    double minDistance = std::numeric_limits<double>::max();  // Минимальное расстояние

    std::vector<int> vertexList(points.size());
    for (int i = 0; i < points.size(); ++i)
        vertexList[i] = i;

    do
    {
        double distance = 0;
        for (int i = 0; i < points.size() - 1; ++i)
            distance += points[vertexList[i]].distanceTo(points[vertexList[i + 1]]);
        distance += points[vertexList.back()].distanceTo(points[vertexList[0]]);

        if (distance < minDistance)
        {
            minDistance = distance;
            tour = vertexList;
        }
    } while (std::next_permutation(vertexList.begin() + 1, vertexList.end()));

    // Отображение решения
    for (int i = 0; i < tour.size() - 1; ++i)
    {
        int src = tour[i];
        int dest = tour[i + 1];

        QGraphicsLineItem* item = scene->addLine(points[src].x, points[src].y, points[dest].x, points[dest].y, QPen(Qt::red, 2));
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }

    int src = tour.back();
    int dest = tour[0];
    QGraphicsLineItem* item = scene->addLine(points[src].x, points[src].y, points[dest].x, points[dest].y, QPen(Qt::red, 2));
    item->setFlag(QGraphicsItem::ItemIsMovable, false);
    item->setFlag(QGraphicsItem::ItemIsSelectable, false);

    std::cout << "Min Distance: " << minDistance << std::endl;
    std::cout << "Tour: ";
    for (int i : tour)
        std::cout << i << " ";
    std::cout << std::endl;
}

void GraphWidget::addPoint()
{
    int newX = std::rand() % 600 + 100;
    int newY = std::rand() % 400 + 100;

    Point newPoint(newX, newY);
    points.push_back(newPoint);

    scene->clear();

    for (int i = 0; i < points.size(); ++i)
    {
        QGraphicsEllipseItem* item = scene->addEllipse(points[i].x - 5, points[i].y - 5, 10, 10, QPen(Qt::black), QBrush(Qt::black));
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QGraphicsSimpleTextItem* textItem = scene->addSimpleText(QString::number(i));
        textItem->setPos(points[i].x - 10, points[i].y - 20);
    }

    for (const Edge& edge : edges)
    {
        QGraphicsLineItem* item = scene->addLine(points[edge.src].x, points[edge.src].y, points[edge.dest].x, points[edge.dest].y, QPen(Qt::blue));
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QGraphicsSimpleTextItem* textItem = scene->addSimpleText(QString::number(edge.weight));
        textItem->setPos((points[edge.src].x + points[edge.dest].x) / 2, (points[edge.src].y + points[edge.dest].y) / 2);
    }

    solveTSP();
}

void GraphWidget::removePoint()
{
    if (!points.empty())
        points.pop_back();

    scene->clear();

    for (int i = 0; i < points.size(); ++i)
    {
        QGraphicsEllipseItem* item = scene->addEllipse(points[i].x - 5, points[i].y - 5, 10, 10, QPen(Qt::black), QBrush(Qt::black));
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QGraphicsSimpleTextItem* textItem = scene->addSimpleText(QString::number(i));
        textItem->setPos(points[i].x - 10, points[i].y - 20);
    }

    for (const Edge& edge : edges)
    {
        QGraphicsLineItem* item = scene->addLine(points[edge.src].x, points[edge.src].y, points[edge.dest].x, points[edge.dest].y, QPen(Qt::blue));
        item->setFlag(QGraphicsItem::ItemIsMovable, false);
        item->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QGraphicsSimpleTextItem* textItem = scene->addSimpleText(QString::number(edge.weight));
        textItem->setPos((points[edge.src].x + points[edge.dest].x) / 2, (points[edge.src].y + points[edge.dest].y) / 2);
    }

    solveTSP();
}
