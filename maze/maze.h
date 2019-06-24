#ifndef MAZE_H
#define MAZE_H

#include "sector.h"

class Maze
{
private:
    QVector<QVector<Sector*>> maze;
public:
    Maze(QVector<QVector<Sector*>>& maze);

    Sector* sector(int x, int y);

    int height() const;
    int width() const;
};

#endif // MAZE_H
