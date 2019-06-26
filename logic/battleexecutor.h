#ifndef BATTLEEXECUTOR_H
#define BATTLEEXECUTOR_H

#include <QObject>

#include "collisiondetector.h"
#include "objects/character.h"

class BattleExecutor : public QObject
{
    Q_OBJECT
public:
    BattleExecutor();
public slots:
    void slotBattle(Character* unit1, Character* unit2);
};

#endif // BATTLEEXECUTOR_H
