#include "builder.h"

Builder::Builder(int height, int width)
{
    this->height = height;
    this->width = width;

    this->matrix = QVector<QVector<Cell>>(height, QVector<Cell>(width));
    this->visitMatrix = QVector<QVector<int>>(height, QVector<int>(width));
}

QVector<Cell> Builder::getNeighbours(const Cell &c)
{
    Cell up    = {c.x, c.y - 2};
    Cell down  = {c.x, c.y + 2};
    Cell left  = {c.x - 2, c.y};
    Cell right = {c.x + 2, c.y};

    QVector<Cell> cells = {up, down, left, right};
    QVector<Cell> neighbours;

    for (const auto& cell : cells)
    {
        if (cell.x >= 0 && cell.x < width && cell.y >= 0 && cell.y < height)
        {
            Cell& neighbour = matrix[cell.y][cell.x];
            if (visitMatrix[cell.y][cell.x] == 1)
            {
                neighbours.push_back(neighbour);
            }
        }
    }
}
