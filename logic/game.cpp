#include "game.h"

Game::Game(int botsNumber, int bonusesNumber, int portalsNumber,
           int mHeight, int mWidth, int sHeight, int sWidth)
{
    maze = new Maze(mHeight, mWidth, sHeight, sWidth);

    player = new Player(maze->sector(0, 0), Qt::red);

    for (int i = 0; i < botsNumber; i++)
    {
        Sector* sector = maze->sector(qrand() % mWidth, qrand() % mHeight);
        QColor color = Qt::blue;
        bots.push_back(new Bot(sector, color));
    }

    for (int i = 0; i < portalsNumber; i++)
    {
        // Add portals
    }

    for (int i = 0; i < bonusesNumber; i++)
    {
        Sector* sector = maze->sector(qrand() % mWidth, qrand() % mHeight);
        QColor color = Qt::green;
        bonuses.push_back(new Bonus(sector, color));
    }

    collisionDetector = new CollisionDetector(player, bots);
    battleExecutor = new BattleExecutor;
    QObject::connect(collisionDetector, &CollisionDetector::signalBattle, battleExecutor, &BattleExecutor::slotBattle);
}

void Game::start()
{
    for (int i = 0; i < bots.size(); i++)
    {
        bots[i]->move();
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
