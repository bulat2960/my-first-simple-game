#include "scene.h"

Scene::Scene(Maze* maze, Player* player)
{
    this->maze = maze;
    this->player = player;

    for (int i = 0; i < maze->width(); i++)
    {
        for (int j = 0; j < maze->height(); j++)
        {
            Sector* sector = maze->sector(i, j);

            QPoint pos = sector->position();
            int p1 = pos.x() * sector->width();
            int p2 = pos.y() * sector->height();
            sector->setPos(QPoint(p1, p2) * SIZE);
            sector->setZValue(-10000);

            addItem(sector);
        }
    }

    addItem(player);
}

bool Scene::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        sendEvent(player, event);
        return true;
    }
    return QObject::eventFilter(object, event);
}

