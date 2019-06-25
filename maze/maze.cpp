#include "maze.h"

Maze::Maze(int mHeight, int mWidth, int sHeight, int sWidth)
{
    Builder builder(sHeight, sWidth);

    for (int i = 0; i < mHeight; i++)
    {
        QVector<Sector*> sectorRow;
        for (int j = 0; j < mWidth; j++)
        {
            QVector<QVector<Cell>> sectorMatrix = builder.create();
            Sector* sector = new Sector(sectorMatrix, j, i);
            sectorRow.push_back(sector);
        }
        matrix.push_back(sectorRow);
    }
}

int Maze::height() const
{
    return matrix.size();
}

int Maze::width() const
{
    return matrix[0].size();
}

Sector* Maze::sector(int x, int y) const
{
    return matrix[y][x];
}
