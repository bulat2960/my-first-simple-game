#ifndef BONUS_H
#define BONUS_H

#include "fixedobject.h"
#include "character.h"

class Bonus : public FixedObject
{
    Q_OBJECT
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
    Bonus(Sector* sector);
signals:
    void signalTakenBy(Character* character);
public slots:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;
};

#endif // BONUS_H
