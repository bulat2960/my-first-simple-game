#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "maze/maze.h"
#include "objects/player.h"
#include "objects/bot.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
private:
    Maze* maze;
    Player* player;
    QVector<Bot*> bots;
public:
    Scene(Maze* maze, Player* player, QVector<Bot*> bots);

public slots:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};

#endif // SCENE_H
