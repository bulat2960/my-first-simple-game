#include "bonus.h"

Bonus::Bonus(Sector* sector, QColor color) : Object(sector, color)
{

}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath path;
    path.addRect(boundingRect());

    QPoint topLeftPoint = boundingRect().topLeft().toPoint() + QPoint(SIZE, SIZE) / 4;

    // Дописать

    painter->fillPath(path, color());
}
