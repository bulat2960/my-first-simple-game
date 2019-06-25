#ifndef CHARACTER_H
#define CHARACTER_H

#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QMap>
#include <QGraphicsScene>

#include "object.h"
#include "maze/sector.h"

class Character : public Object
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
protected:
    QMap<int, QPoint> directions;

    QPropertyAnimation* anim;
public:
    Character(Sector* sector, QColor color);

    Sector* findNextSector(int key);
    Sector* findNextSector(QPoint dir);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;

    void startAnimation(QPoint point, QPoint offset);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CHARACTER_H
