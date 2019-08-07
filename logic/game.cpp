#include "game.h"

Game::Game(Maze* maze, Player* player)
{
    this->maze = maze;
    this->player = player;

    collisionDetector = new CollisionDetector(player, bots, bonuses, portals);
    connect(player, &Character::signalFindCharacter, collisionDetector, &CollisionDetector::slotFindCharacter);
    connect(player, &Player::signalFindPortal, collisionDetector, &CollisionDetector::slotFindPortal);

    battleExecutor = new BattleExecutor;
    QObject::connect(collisionDetector, &CollisionDetector::signalBattle, battleExecutor, &BattleExecutor::slotBattle);
}

void Game::slotCreateBot()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Bot* bot = new Bot(sector);
    bot->setColor(Qt::blue);
    bot->setZValue(-20);
    bots.push_back(bot);
    connect(bot, &Bot::signalFindCharacter, collisionDetector, &CollisionDetector::slotFindCharacter);
    connect(bot, &Bot::signalFindPortal, collisionDetector, &CollisionDetector::slotFindPortal);

    emit signalCreated(bot);
}

void Game::slotCreateBonus()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Bonus* bonus = new Bonus(sector);
    bonus->setColor(Qt::green);
    bonus->setZValue(-100);
    bonuses.push_back(bonus);

    emit signalCreated(bonus);
}

void Game::slotCreatePortal()
{
    Sector* sector = maze->sector(qrand() % maze->width(), qrand() % maze->height());
    Portal* portal = new Portal(sector);
    portal->setColor(Qt::black);
    portal->setZValue(-50);
    portals.push_back(portal);

    emit signalCreated(portal);
}

void Game::slotStart()
{
    player->setMovementPermission(true);
    for (int i = 0; i < bots.size(); i++)
    {
        bots[i]->start();
    }
}

void Game::slotResume()
{
    player->setMovementPermission(true);
    for (int i = 0; i < bots.size(); i++)
    {
        bots[i]->resume();
    }
}

void Game::slotPause()
{
    player->setMovementPermission(false);
    for (int i = 0; i < bots.size(); i++)
    {
        bots[i]->pause();
    }
}

void Game::slotStop()
{

}
