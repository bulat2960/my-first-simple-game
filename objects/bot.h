#ifndef BOT_H
#define BOT_H

#include "character.h"

class Bot : public Character
{
public:
    Bot(Sector* sector);
private slots:
    void slotFindCorrectMoveDir() override;
};

#endif // BOT_H
