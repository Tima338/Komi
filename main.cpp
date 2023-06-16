#include <QApplication>
#include <iostream>
#include "graphwidget.h"
#include <QMainWindow>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    // Задаем координаты точек
    std::vector<Point> points = {
        {50, 50},
        {200, 50},
        {150, 200},
        {100, 150},
        {250, 150}
    };

    // Задаем ребра с весом
    std::vector<Edge> edges = {
        {0, 1, points[0].distanceTo(points[1])},
        {1, 2, points[1].distanceTo(points[2])},
        {2, 3, points[2].distanceTo(points[3])},
        {3, 4, points[3].distanceTo(points[4])},
        {4, 0, points[4].distanceTo(points[0])}
    };

    // Создаем окно и отображаем граф
    QMainWindow window;
    GraphWidget* graphWidget = new GraphWidget(points, edges);
    window.setCentralWidget(graphWidget);
    window.show();

    return app.exec();
}
