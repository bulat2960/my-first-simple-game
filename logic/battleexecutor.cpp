#include "battleexecutor.h"

BattleExecutor::BattleExecutor(CollisionDetector* detector)
{
    this->detector = detector;
    connect(detector, &CollisionDetector::signalBattle, this, &BattleExecutor::slotBattle);
}

void BattleExecutor::slotBattle(Character* unit1, Character* unit2)
{
    unit2->kill();
}
