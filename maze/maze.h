#ifndef MAZE_H
#define MAZE_H

#include <QVector>

#include "sector.h"
#include "builder.h"

class Maze
{
private:
    QVector<QVector<Sector*>> matrix;
public:
    Maze(int mHeight, int mWidth, int sHeight, int sWidth);

    int height() const;
    int width() const;

    Sector* sector(int x, int y) const;
};

#endif // MAZE_H
