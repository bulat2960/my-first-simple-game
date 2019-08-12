#include "battleexecutor.h"

BattleExecutor::BattleExecutor()
{

}

void BattleExecutor::slotBattle(Character* unit1, Character* unit2)
{
    int counter = 0;
    while (counter++ < 3)
    {
        unit2->setHitpoints(unit2->hitpoints() - unit1->damage());
        if (unit2->hitpoints() <= 0)
        {
            unit2->kill();
            break;
        }

        unit1->setHitpoints(unit1->hitpoints() - unit2->damage());
        if (unit1->hitpoints() <= 0)
        {
            unit1->kill();
            break;
        }
    }

    if (unit1->hitpoints() < unit2->hitpoints())
    {
        unit1->kill();
    }
    else
    {
        unit2->kill();
    }
}
