#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "maze/maze.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
private:
    Maze* maze;
public:
    Scene(Maze* maze);
};

#endif // SCENE_H
