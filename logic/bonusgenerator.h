#ifndef BONUSGENERATOR_H
#define BONUSGENERATOR_H

#include "objects/bonus.h"

class BonusGenerator
{
private:
    QVector<Bonus*> bonuses;
public:
    BonusGenerator();
};

#endif // BONUSGENERATOR_H
