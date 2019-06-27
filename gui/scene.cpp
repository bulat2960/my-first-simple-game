#include "scene.h"

Scene::Scene(Maze* maze, Player* player, QVector<Bot*> bots)
{
    this->maze = maze;
    this->player = player;
    this->bots = bots;

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

    addItem(player);

    for (int i = 0; i < bots.size(); i++)
    {
        addItem(bots[i]);
        bots[i]->move();
    }
}

void Scene::keyPressEvent(QKeyEvent* event)
{
    sendEvent(player, event);
}

void Scene::keyReleaseEvent(QKeyEvent* event)
{
    sendEvent(player, event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    int n1 = qrand() % maze->height();
    int n2 = qrand() % maze->width();
    maze->swapSectors(n1, n2);

    Sector* sector1 = maze->sector(n1, n2);
    Sector* sector2 = maze->sector(n2, n1);

    QPoint pos1 = sector1->position();
    QPoint pos2 = sector2->position();

    int pos1x = pos1.x() * sector1->width();
    int pos1y = pos1.y() * sector1->height();
    qDebug() << sector1->pos();
    sector1->setPos(QPoint(pos1x, pos1y) * SIZE);
    qDebug() << sector2->pos();
    sector1->update();
    sector1->hide();

    int pos2x = pos2.x() * sector2->width();
    int pos2y = pos2.y() * sector2->height();
    sector2->setPos(QPoint(pos2x, pos2y) * SIZE);
    sector2->update();
}

