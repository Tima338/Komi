#ifndef POINT_H
#define POINT_H

#include <cmath>

// Класс, представляющий точку на плоскости
class Point
{
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    double distanceTo(const Point& other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    double x;
    double y;
};

#endif // POINT_H
