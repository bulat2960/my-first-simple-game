#include "collisiondetector.h"

CollisionDetector::CollisionDetector(Player* player, QVector<Bot*> bots)
{
    this->player = player;
    this->bots = bots;

    connect(player, &Player::signalMove, this, &CollisionDetector::findCollision);
}

void CollisionDetector::findCollision()
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
            if (p->getPosition() == bot->getPosition())
            {
                emit signalBattle(p, bot);
            }
        }
    }
}
