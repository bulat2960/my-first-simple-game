#include "object.h"

Object::Object(Sector* sector, QColor color)
{
    objPosition = QPoint(0, 0);
    objSector = sector;
    objColor = color;
}

QPoint Object::position() const
{
    return objPosition;
}

QPoint Object::graphicalPosition(const QPoint &position) const
{
    return position * SIZE;
}

void Object::setPosition(int x, int y)
{
    objPosition = QPoint(x, y);
}

void Object::setPosition(const QPoint& position)
{
    this->objPosition = position;
}

Sector* Object::sector() const
{
    return objSector;
}

void Object::setSector(Sector* sector)
{
    objSector = sector;
}

QColor Object::color() const
{
    return objColor;
}

void Object::setColor(QColor color)
{
    objColor = color;
}

QPoint Object::mapToSector(QPoint p, Sector* sector) const
{
    return QPoint(p.x() % sector->width(), p.y() % sector->height());
}

bool Object::animStopped() const
{
    return anim->state() == QPropertyAnimation::Stopped;
}
