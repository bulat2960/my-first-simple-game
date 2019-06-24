#include "maze.h"

Maze::Maze(QVector<QVector<Sector*>>& maze)
{
    this->maze = maze;
}

int Maze::height() const
{
    return maze.size();
}

int Maze::width() const
{
    return maze[0].size();
}
