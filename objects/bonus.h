#ifndef BONUS_H
#define BONUS_H

#include "object.h"
#include "character.h"

class Bonus : public Object
{
public:
    enum Type
    {
        INCREASE_HP,
        DECREASE_HP,
        INCREASE_REGENERATION,
        DECREASE_REGENERATION,
        INCREASE_DAMAGE,
        DECREASE_DAMAGE,
        POISON,
        HEAL,
        DAMAGE,
        SECRET
    };
    Bonus(Sector* sector, QColor color);
signals:
    void signalTakenBy(Character* character);
public slots:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BONUS_H
