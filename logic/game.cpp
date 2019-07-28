#include "game.h"

Game::Game(Maze* maze, Player* player)
{
    this->maze = maze;
    this->player = player;

    collisionDetector = new CollisionDetector(player, bots);

    connect(player, &Character::signalCheckCollisions, collisionDetector, &CollisionDetector::slotFindCollision);

    battleExecutor = new BattleExecutor;
    QObject::connect(collisionDetector, &CollisionDetector::signalBattle, battleExecutor, &BattleExecutor::slotBattle);
}

void Game::slotCreateBot()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Bot* bot = new Bot(sector, Qt::blue);
    bots.push_back(bot);
    connect(bot, &Bot::signalCheckCollisions, collisionDetector, &CollisionDetector::slotFindCollision);

    emit signalCreated(bot);
}

void Game::slotCreateBonus()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Bonus* bonus = new Bonus(sector, Qt::green);
    bonuses.push_back(bonus);

    emit signalCreated(bonus);
}

void Game::slotCreatePortal()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Portal* portal = new Portal(sector, Qt::black);
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

Player* Game::getPlayer() const
{
    return player;
}

QVector<Bot*> Game::getBots() const
{
    return bots;
}

Maze* Game::getMaze() const
{
    return maze;
}

QVector<Bonus*> Game::getBonuses() const
{
    return bonuses;
}
