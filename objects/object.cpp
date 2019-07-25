﻿#include "object.h"

Object::Object(Sector* sector, QColor color)
{
    objPosition = QPoint(0, 0);
    this->objSector = sector;
    this->objColor = color;
}

QPoint Object::position() const
{
    return objPosition;
}

void Object::setPosition(int x, int y)
{
    this->objPosition = QPoint(x, y);
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
    this->objSector = sector;
}

QColor Object::color() const
{
    return objColor;
}

void Object::setColor(QColor color)
{
    this->objColor = color;
}

QPoint Object::mapToSector(QPoint p, Sector* sector) const
{
    return QPoint(p.x() % sector->width(), p.y() % sector->height());
}
