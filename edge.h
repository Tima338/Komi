#ifndef EDGE_H
#define EDGE_H

// Класс, представляющий ребро графа с весом
class Edge
{
public:
    Edge(int src, int dest, double weight) : src(src), dest(dest), weight(weight) {}

    int src;
    int dest;
    double weight;
};

#endif // EDGE_H
