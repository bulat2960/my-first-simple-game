#ifndef BUILDER_H
#define BUILDER_H

#include <QVector>
#include <QStack>

#include "cell.h"

class Builder
{
private:
    int height;
    int width;

    QVector<QVector<Cell>> matrix;
    QVector<QVector<int>> visitMatrix;
    QStack<Cell> stack;
private:
    QVector<Cell> getNeighbours(const Cell& cell);
    void removeWall(const Cell& current, const Cell& neighbour);

    void destroyVertical();
    void destroyHorizontal();
public:
    Builder(int height, int width);
    QVector<QVector<Cell>> create(int x, int y);
};

#endif // BUILDER_H
