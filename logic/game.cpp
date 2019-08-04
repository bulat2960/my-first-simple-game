#include "game.h"

Game::Game(Maze* maze, Player* player)
{
    this->maze = maze;
    this->player = player;

    collisionDetector = new CollisionDetector(player, bots, bonuses, portals);

    connect(player, &Character::signalCheckCollisions, collisionDetector, &CollisionDetector::slotFindCollision);
    connect(player, &Player::signalCheckPortal, collisionDetector, &CollisionDetector::slotFindPortal);

    battleExecutor = new BattleExecutor;
    QObject::connect(collisionDetector, &CollisionDetector::signalBattle, battleExecutor, &BattleExecutor::slotBattle);
}

void Game::slotCreateBot()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Bot* bot = new Bot(sector);
    bot->setColor(Qt::blue);
    bots.push_back(bot);
    connect(bot, &Bot::signalCheckCollisions, collisionDetector, &CollisionDetector::slotFindCollision);
    connect(bot, &Bot::signalCheckPortal, collisionDetector, &CollisionDetector::slotFindPortal);

    emit signalCreated(bot);
}

void Game::slotCreateBonus()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Bonus* bonus = new Bonus(sector);
    bonus->setColor(Qt::green);
    bonuses.push_back(bonus);

    emit signalCreated(bonus);
}

void Game::slotCreatePortal()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Portal* portal = new Portal(sector);
    portal->setColor(Qt::black);
    portals.push_back(portal);

    emit signalCreated(portal);
}

void Game::slotStart()
{
    for (int i = 0; i < bots.size(); i++)
    {
        bots[i]->slotFindCorrectMoveDir();
    }
}
