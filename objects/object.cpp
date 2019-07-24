#include "object.h"

Object::Object(Sector* sector, QColor color)
{
    position = QPoint(0, 0);
    this->sector = sector;
    this->color = color;
}

QPoint Object::getPosition() const
{
    return position;
}

QPoint Object::mapToSector(QPoint p, Sector* sector) const
{
    return QPoint(p.x() % sector->width(), p.y() % sector->height());
}
