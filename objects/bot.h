#ifndef BOT_H
#define BOT_H

#include "character.h"

class Bot : public Character
{
public:
    enum State
    {
        ATTACK = 1,
        RUN_AWAY,
        FIND_BONUS,
        DO_NOTHING
    };
private:
    State state;
public:
    Bot(Sector* sector);

    State getState() const;
    void setState(State state);
private slots:
    void slotFindCorrectMoveDir() override;
};

#endif // BOT_H
