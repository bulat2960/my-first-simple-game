#include "portal.h"

Portal::Portal(Sector* sector) : FixedObject(sector)
{
    drawingSettings.image.load(":/images/images/portal.png");
}

QPainterPath Portal::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());

    return path;
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawImage(boundingRect(), drawingSettings.image);
}
