﻿#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "maze/maze.h"
#include "objects/player.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
private:
    Maze* maze;
    Player* player;
public:
    Scene(Maze* maze, Player* player);

public slots:
    bool eventFilter(QObject* object, QEvent* event) override;
};

#endif // SCENE_H
