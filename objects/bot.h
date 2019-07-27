﻿#ifndef BOT_H
#define BOT_H

#include "character.h"

class Bot : public Character
{
public:
    Bot(Sector* sector, QColor color);
public slots:
    void slotFindCorrectMoveDir();
};

#endif // BOT_H
