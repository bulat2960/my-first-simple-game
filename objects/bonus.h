#ifndef BONUS_H
#define BONUS_H

#include "character.h"

class Bonus
{
public:
    Bonus();
signals:
    void signalTakenBy(Character* character);
};

#endif // BONUS_H
