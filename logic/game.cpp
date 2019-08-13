#include "game.h"

Game::Game(Maze* maze, Player* player)
{
    this->maze = maze;
    this->player = player;

    collisionDetector = new CollisionDetector(player, bots, bonuses, portals);
    connect(player, &Character::signalFindCharacter, collisionDetector, &CollisionDetector::slotFindCharacter);
    connect(player, &Player::signalFindPortal, collisionDetector, &CollisionDetector::slotFindPortal);
    connect(player, &Player::signalSendData, this, &Game::slotFindNearestEnemy);
    connect(player, &Player::signalSectorChanged, this, &Game::slotChangeBotState);

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
    player->start();
    foreach (Bot* bot, bots)
    {
        bot->start();
    }
    foreach (Bonus* bonus, bonuses)
    {
        bonus->start();
    }
    foreach (Portal* portal, portals)
    {
        portal->start();
    }
}

void Game::slotResume()
{
    player->resume();
    foreach (Bot* bot, bots)
    {
        bot->resume();
    }
    foreach (Bonus* bonus, bonuses)
    {
        bonus->resume();
    }
    foreach (Portal* portal, portals)
    {
        portal->resume();
    }
}

void Game::slotPause()
{
    player->pause();
    foreach (Bot* bot, bots)
    {
        bot->pause();
    }
    foreach (Bonus* bonus, bonuses)
    {
        bonus->pause();
    }
    foreach (Portal* portal, portals)
    {
        portal->pause();
    }
}

void Game::slotChangeBotState()
{
    foreach (Bot* bot, bots)
    {
        if (bot->sector() == player->sector())
        {
            bot->setState(Bot::ATTACK);
        }
    }
}

void Game::slotFindNearestEnemy()
{
    QObject* sender = QObject::sender();
    Player* player = dynamic_cast<Player*>(sender);

    if (bots.size() > 0)
    {
        double minDistance = 10000000000;
        Bot* nearestBot = nullptr;

        foreach (Bot* bot, bots)
        {
            if (bot->hitpoints() <= 0)
            {
                continue;
            }

            QPoint pPos = player->position();
            QPoint bPos = bot->position();
            double xSquare = pow(pPos.x() - bPos.x(), 2);
            double ySquare = pow(pPos.y() - bPos.y(), 2);
            double distance = sqrt(xSquare + ySquare);

            if (distance < minDistance)
            {
                minDistance = distance;
                nearestBot = bot;
            }
        }

        if (nearestBot != nullptr)
        {
            nearestBot->setTarget(player); // Fix me!
            emit signalSendToGamePanel(player->gameData(), nearestBot->gameData());
        }
    }
}
