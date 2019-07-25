#ifndef BONUS_H
#define BONUS_H

#include "character.h"

class Bonus
{
public:
    enum Type
    {
        INCREASE_HP,
        INCREASE_REGENERATION,
        INCREASE_DAMAGE,
        POISON,
        HEAL,
        DAMAGE,
        SECRET
    };
    Bonus();
signals:
    void signalTakenBy(Character* character);
};

#endif // BONUS_H
