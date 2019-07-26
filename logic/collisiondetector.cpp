#include "collisiondetector.h"

CollisionDetector::CollisionDetector(Player* player, QVector<Bot*> bots)
{
    this->player = player;
    this->bots = bots;

    connect(player, &Character::signalCheckCollisions, this, &CollisionDetector::slotFindCollision);
    for (int i = 0; i < bots.size(); i++)
    {
        connect(bots[i], &Character::signalCheckCollisions, this, &CollisionDetector::slotFindCollision);
    }
}

void CollisionDetector::slotFindCollision()
{
    QObject* sender = QObject::sender();

    Object* senderObject = dynamic_cast<Object*>(sender);
    Player* p = dynamic_cast<Player*>(senderObject);
    Bot* b = dynamic_cast<Bot*>(senderObject);

    if (p)
    {
        for (int i = 0; i < bots.size(); i++)
        {
            Bot* bot = bots[i];
            if (bot->alive() && p->collidesWithItem(bot, Qt::ItemSelectionMode::IntersectsItemBoundingRect))
            {
                emit signalBattle(p, bot);
            }
        }
    }

    if (b)
    {
        if (player->alive() && b->collidesWithItem(player, Qt::ItemSelectionMode::IntersectsItemBoundingRect))
        {
            emit signalBattle(b, player);
        }
    }
}
