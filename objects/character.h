#ifndef CHARACTER_H
#define CHARACTER_H

#include <QKeyEvent>
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

    int speed;
    int damage;
    int hitpoints;
protected:
    void move(QPoint nextPos);
public:
    Character(Sector* sector, QColor color);

    virtual QPainterPath shape() const override;

    void startMoveAnimation(QPoint startPos, QPoint endPos);

    Sector* findNextSector(QPoint nextPos);
    bool insideScene(QPoint nextPos);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void signalCheckPortal();
    void signalCheckCollisions();
};

#endif // CHARACTER_H
