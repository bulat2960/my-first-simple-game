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
    Character* target;
private:
    QVector<QVector<int>> generateFilledDigitMatrix(QPoint start, QPoint finish);
    QVector<QPoint> getPath(QPoint start, QPoint finish, QVector<QVector<int>> matrix);
public:
    Bot(Sector* sector);

    State getState() const;
    void setState(State state);

    void setTarget(Character* character);
    Character* getTarget() const;
private slots:
    void slotFindCorrectMoveDir() override;
};

#endif // BOT_H
