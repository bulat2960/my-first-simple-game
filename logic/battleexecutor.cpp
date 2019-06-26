#include "battleexecutor.h"

BattleExecutor::BattleExecutor()
{

}

void BattleExecutor::slotBattle(Character* unit1, Character* unit2)
{
    unit2->kill();
}
