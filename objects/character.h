#ifndef CHARACTER_H
#define CHARACTER_H

#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QMap>
#include <QGraphicsScene>
#include <QTimer>

#include "object.h"
#include "maze/sector.h"

class Character : public Object
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
protected:
    QMap<int, QPoint> directions;

    QPropertyAnimation* anim;

    int speed;
    int damage;
    int hitpoints;

    bool isAlive;
    QTimer* respawnTimer;
public:
    Character(Sector* sector, QColor color);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;

    void startAnimation(QPoint startPos, QPoint endPos);

    bool alive() const;
    void kill();
    void respawn();

    Sector* findNextSector(QPoint direction);
    bool isInsideScene(QPoint nextPos);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
    void signalCheckCollisions();
};

#endif // CHARACTER_H
