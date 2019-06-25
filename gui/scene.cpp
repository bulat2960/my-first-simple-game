﻿#include "scene.h"

Scene::Scene(Maze* maze, Player* player, Bot* bot)
{
    this->maze = maze;
    this->player = player;

    addItem(player);
    addItem(bot);

    for (int i = 0; i < maze->width(); i++)
    {
        for (int j = 0; j < maze->height(); j++)
        {
            Sector* sector = maze->sector(i, j);

            QPoint pos = sector->position();
            int p1 = pos.x() * sector->width();
            int p2 = pos.y() * sector->height();
            sector->setPos(QPoint(p1, p2) * SIZE);

            addItem(sector);
        }
    }

    bot->move();
}

void Scene::keyPressEvent(QKeyEvent* event)
{
    sendEvent(player, event);
}

void Scene::keyReleaseEvent(QKeyEvent* event)
{
    sendEvent(player, event);
}
