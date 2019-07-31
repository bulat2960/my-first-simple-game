#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include <QObject>

#include "objects/object.h"
#include "objects/player.h"
#include "objects/bot.h"
#include "objects/bonus.h"
#include "objects/portal.h"

class CollisionDetector : public QObject
{
    Q_OBJECT
private:
    Player* player;
    QVector<Bot*>& bots;
    QVector<Bonus*>& bonuses;
    QVector<Portal*>& portals;
public:
    CollisionDetector(Player* player, QVector<Bot*>& bots, QVector<Bonus*>& bonuses, QVector<Portal*>& portals);
public slots:
    void slotFindCollision();
    void slotFindPortal();
signals:
    void signalBattle(Character* obj1, Character* obj2);
};

#endif // COLLISIONDETECTOR_H
