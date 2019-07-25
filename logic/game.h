#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "battleexecutor.h"
#include "bonusgenerator.h"
#include "collisiondetector.h"

#include "maze/maze.h"

#include "objects/bonus.h"
#include "objects/player.h"
#include "objects/bot.h"
#include "objects/portal.h"


class Game : public QObject
{
    Q_OBJECT
private:
    Maze* maze;

    Player* player;
    QVector<Bot*> bots;
    QVector<Bonus*> bonuses;
    QVector<Portal*> portals;

    BattleExecutor* battleExecutor;
    CollisionDetector* collisionDetector;
    BonusGenerator* bonusGenerator;

public:
    Game(int botsNumber, int bonusesNumber, int portalsNumber,
         int mHeight, int mWidth, int sHeight, int sWidth);

    Maze* getMaze() const;
    Player* getPlayer() const;
    QVector<Bot*> getBots() const;
    QVector<Bonus*> getBonuses() const;

public slots:
    void start();
};

#endif // GAME_H
