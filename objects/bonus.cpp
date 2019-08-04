#include "bonus.h"

Bonus::Bonus(Sector* sector) : FixedObject(sector)
{
    drawingSettings.image.load(":/images/images/heal_bonus.png");
}

QPainterPath Bonus::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());

    return path;
}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawImage(boundingRect().adjusted(SIZE / 5, SIZE / 5, -SIZE / 5, -SIZE / 5), drawingSettings.image);
}
