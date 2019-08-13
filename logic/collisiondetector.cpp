#include "collisiondetector.h"

CollisionDetector::CollisionDetector(Player* player, QVector<Bot*>& bots, QVector<Bonus*>& bonuses, QVector<Portal*>& portals)
    : bots(bots), bonuses(bonuses), portals(portals)
{
    this->player = player;
}

void CollisionDetector::slotFindCharacter()
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
            if (bot->alive() && p->collidesWithItem(bot))
            {
                emit signalBattle(p, bot);
            }
        }
    }

    if (b)
    {
        for (int i = 0; i < bots.size(); i++)
        {
            Bot* bot = bots[i];
            if (b == bot)
            {
                continue;
            }
            if (bot->alive() && b->collidesWithItem(bot))
            {
                emit signalBattle(b, bot);
            }
        }
        if (player->alive() && b->collidesWithItem(player))
        {
            emit signalBattle(b, player);
        }
    }
}

void CollisionDetector::slotFindPortal()
{
    QObject* sender = QObject::sender();

    Character* character = dynamic_cast<Character*>(sender);

    Portal* start = nullptr;
    Portal* finish = nullptr;

    if (portals.size() == 0)
    {
        return;
    }

    for (int i = 0; i < portals.size(); i++)
    {
        if (character->position() == portals[i]->position())
        {
            start = portals[i];
        }
    }
    while (true)
    {
        int randNum = qrand() % portals.size();
        finish = portals[randNum];
        if (start != finish)
        {
            break;
        }
    }
    if (start != nullptr)
    {
        character->setSector(finish->sector());
        character->setPosition(finish->position());
        character->setPos(finish->pos());
    }
}
