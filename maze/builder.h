#ifndef BUILDER_H
#define BUILDER_H

#include <QVector>
#include <QStack>

#include <cmath>

#include "cell.h"

class Builder
{
private:
    enum State
    {
        VISITED,
        NOT_VISITED
    };
private:
    int height;
    int width;

    QVector<QVector<Cell>> matrix;
    QVector<QVector<State>> visitMatrix;
    QStack<Cell> stack;
private:
    void initMatrix();
    void initVisitMatrix();

    QVector<Cell> getNeighbours(const Cell& cell);
    void removeWall(const Cell& current, const Cell& neighbour);

    void destroyVertical();
    void destroyHorizontal();
public:
    Builder(int height, int width);
    QVector<QVector<Cell>> create();
};

#endif // BUILDER_H
