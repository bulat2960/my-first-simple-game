#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <QObject>

#include "objects/object.h"
#include "objects/player.h"
#include "objects/bot.h"

class CollisionDetector : public QObject
{
    Q_OBJECT
private:
    Player* player;
    QVector<Bot*> bots;
public:
    CollisionDetector(Player* player, QVector<Bot*> bots);
public slots:
    void findCollision();
};

#endif // COLLISIONDETECTOR_H
