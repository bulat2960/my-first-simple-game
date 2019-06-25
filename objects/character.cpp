#include "character.h"

Character::Character(Sector* sector, QColor color) : Object(sector, color)
{
    anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(250);

    directions.insert(Qt::Key_A, QPoint(-1, 0));
    directions.insert(Qt::Key_W, QPoint(0, -1));
    directions.insert(Qt::Key_D, QPoint(1, 0));
    directions.insert(Qt::Key_S, QPoint(0, 1));
}

void Character::startAnimation(QPoint point, QPoint offset)
{
    anim->setStartValue(point);
    anim->setEndValue(point + offset);
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

Sector* Character::findNextSector(int key)
{
    QPoint next = (position + directions[key]) * SIZE;
    Sector* nextSector = dynamic_cast<Sector*>(scene()->items(next)[0]);
    return nextSector;
}

Sector* Character::findNextSector(QPoint dir)
{
    QPoint next = (position + dir) * SIZE;
    Sector* nextSector = dynamic_cast<Sector*>(scene()->items(next)[0]);
    return nextSector;
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillPath(shape(), color);
}
