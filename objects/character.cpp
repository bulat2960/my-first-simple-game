﻿#include "character.h"

Character::Character(Sector* sector, QColor color) : Object(sector, color)
{
    speed = 500;
    damage = 1;
    hitpoints = 10;

    respawnTimer = new QTimer(this);
    respawnTimer->setSingleShot(true);
    respawnTimer->setInterval(2000);
    connect(respawnTimer, &QTimer::timeout, this, &Character::respawn);

    isAlive = true;

    anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(speed);

    directions.insert(Qt::Key_A, QPoint(-1, 0));
    directions.insert(Qt::Key_W, QPoint(0, -1));
    directions.insert(Qt::Key_D, QPoint(1, 0));
    directions.insert(Qt::Key_S, QPoint(0, 1));
}

void Character::startAnimation(QPoint startPos, QPoint endPos)
{
    anim->setStartValue(startPos * SIZE);
    anim->setEndValue(endPos * SIZE);
    anim->start();
}

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, SIZE, SIZE);
}

QPainterPath Character::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (isAlive)
    {
        painter->fillPath(shape(), color);
    }
    else
    {
        sector->update();
    }
}

bool Character::alive() const
{
    return isAlive;
}

void Character::kill()
{
    isAlive = false;
    respawnTimer->start();
    anim->pause();
}

void Character::respawn()
{
    isAlive = true;
    anim->resume();
}
