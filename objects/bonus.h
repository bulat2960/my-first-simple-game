#ifndef BONUS_H
#define BONUS_H

#include "object.h"
#include "character.h"

class Bonus : public Object
{
    Q_OBJECT
    Q_PROPERTY(qreal rot READ rot WRITE setRot)
private:
    QPropertyAnimation* rotateAnim;
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

    qreal rot() const;
    void setRot(qreal angle);
signals:
    void signalTakenBy(Character* character);
public slots:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;
};

#endif // BONUS_H
