#include "bonus.h"

Bonus::Bonus(Sector* sector, QColor color) : Object(sector, color)
{
    rotateAnim = new QPropertyAnimation(this, "rot");
    rotateAnim->setDuration(10000);
    rotateAnim->setStartValue(0);
    rotateAnim->setEndValue(360);
    rotateAnim->setLoopCount(-1);
    rotateAnim->start();
}

QPainterPath Bonus::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect().adjusted(SIZE / 5, SIZE / 5, -SIZE / 5, -SIZE / 5));

    QPoint center = boundingRect().bottomRight().toPoint() / 2;

    QPainterPath topLeftPath;
    QRect topLeftRect = QRect(boundingRect().topLeft().toPoint(), center + QPoint(-3, -3));
    topLeftPath.addRect(topLeftRect);
    path -= topLeftPath;

    QPainterPath topRightPath;
    QRect topRightRect = QRect(boundingRect().topRight().toPoint(), center + QPoint(1, -3));
    topRightPath.addRect(topRightRect);
    path -= topRightPath;

    QPainterPath bottomLeftPath;
    QRect bottomLeftRect = QRect(boundingRect().bottomLeft().toPoint(), center + QPoint(-3, 1));
    bottomLeftPath.addRect(bottomLeftRect);
    path -= bottomLeftPath;

    QPainterPath bottomRightPath;
    QRect bottomRightRect = QRect(boundingRect().bottomRight().toPoint(), center + QPoint(1, 1));
    bottomRightPath.addRect(bottomRightRect);
    path -= bottomRightPath;

    return path;
}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillPath(shape(), color());
}
