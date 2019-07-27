#include "bonus.h"

Bonus::Bonus(Sector* sector, QColor color) : Object(sector, color)
{

}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath path;
    path.addRect(boundingRect().adjusted(SIZE / 5, SIZE / 5, -SIZE / 5, -SIZE / 5));

    QPoint center = boundingRect().bottomRight().toPoint() / 2;

    QPainterPath topLeftPath;
    topLeftPath.addRect(QRect(boundingRect().topLeft().toPoint(), center + QPoint(-3, -3)));
    path -= topLeftPath;

    QPainterPath topRightPath;
    topRightPath.addRect(QRect(boundingRect().topRight().toPoint(), center + QPoint(3, -3)));
    path -= topRightPath;

    QPainterPath bottomLeftPath;
    bottomLeftPath.addRect(QRect(boundingRect().bottomLeft().toPoint(), center + QPoint(-3, 3)));
    path -= bottomLeftPath;

    QPainterPath bottomRightPath;
    bottomRightPath.addRect(QRect(boundingRect().bottomRight().toPoint(), center + QPoint(3, 3)));
    path -= bottomRightPath;

    painter->fillPath(path, color());
}
