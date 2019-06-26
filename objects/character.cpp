#include "character.h"

Character::Character(Sector* sector, QColor color) : Object(sector, color)
{
    anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(50);

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

    painter->fillPath(shape(), color);
}
