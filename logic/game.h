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
    Game(Maze* maze, Player* player);
public slots:
    void slotCreateBot();
    void slotCreateBonus();
    void slotCreatePortal();

    void slotStart();
    void slotResume();
    void slotPause();

    void slotFindNearestEnemy();
signals:
    void signalCreated(Object* object);
    void signalSendToGamePanel(QByteArray playerData, QByteArray botData);
};

#endif // GAME_H
