#include "portal.h"

Portal::Portal(Sector* sector, QColor color, Sector* other) : Object(sector, color)
{
    setSector(sector);
    this->other = other;
}

QPainterPath Portal::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());

    QPainterPath subtractPath1;
    QPoint topLeftSub1 = boundingRect().topLeft().toPoint() + QPoint(SIZE / 8, SIZE / 8);
    QPoint bottomRightSub1 = boundingRect().bottomRight().toPoint() + QPoint(-SIZE / 8, -SIZE / 8) - QPoint(1, 1);
    subtractPath1.addEllipse(QRect(topLeftSub1, bottomRightSub1));

    QPainterPath addPath1;
    QPoint topLeftAdd1 = boundingRect().topLeft().toPoint() + QPoint(SIZE / 4, SIZE / 4);
    QPoint bottomRightAdd1 = boundingRect().bottomRight().toPoint() + QPoint(-SIZE / 4, -SIZE / 4) - QPoint(1, 1);
    subtractPath1.addEllipse(QRect(topLeftAdd1, bottomRightAdd1));

    QPainterPath subtractPath2;
    QPoint topLeftSub2 = boundingRect().topLeft().toPoint() + QPoint(SIZE / 3, SIZE / 3);
    QPoint bottomRightSub2 = boundingRect().bottomRight().toPoint() + QPoint(-SIZE / 3, -SIZE / 3) - QPoint(1, 1);
    subtractPath2.addEllipse(QRect(topLeftSub2, bottomRightSub2));


    path -= subtractPath1;
    path += addPath1;
    path -= subtractPath2;

    return path;
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillPath(shape(), color());
}
