#include "portal.h"

Portal::Portal(Sector* sector, QColor color) : Object(sector, color)
{
    setSector(sector);
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

    QPainterPath subtractVertLine;
    QPoint vertTopCenter = (boundingRect().topLeft() + boundingRect().topRight()).toPoint() / 2;
    QPoint vertBottomCenter = (boundingRect().bottomLeft() + boundingRect().bottomRight()).toPoint() / 2 - QPoint(1, 1);
    QRect vertRect = QRect(vertTopCenter - QPoint(1, 0), vertBottomCenter + QPoint(1, 0));
    subtractVertLine.addRect(vertRect);

    QPainterPath subtractHorizLine;
    QPoint horizTopCenter = (boundingRect().topLeft() + boundingRect().bottomLeft()).toPoint() / 2;
    QPoint horizBottomCenter = (boundingRect().topRight() + boundingRect().bottomRight()).toPoint() / 2 - QPoint(1, 1);
    QRect horizRect = QRect(horizTopCenter - QPoint(0, 1), horizBottomCenter + QPoint(0, 1));
    subtractHorizLine.addRect(horizRect);

    QPainterPath centerEllipse;
    QRect centerRect = QRect(QPoint(SIZE / 2 - 1, SIZE / 2 - 1), QPoint(SIZE / 2 + 1, SIZE / 2 + 1) - QPoint(1, 1));
    centerEllipse.addEllipse(centerRect);


    path -= subtractPath1;
    path += addPath1;
    path -= subtractPath2;
    path -= subtractVertLine;
    path -= subtractHorizLine;
    path += centerEllipse;

    return path;
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillPath(shape(), color());
}
