#include "object.h"

Object::Object(Sector* sector, QColor color)
{
    objSector = sector;
    objColor = color;

    isAlive = true;
    respawnTimer = nullptr;

    anim = nullptr;

    setStartPosition();
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

void Object::setStartPosition()
{
    while (true)
    {
        int x = qrand() % sector()->width();
        int y = qrand() % sector()->height();
        if (sector()->cell(x, y).isRoad())
        {
            x += sector()->position().x() * sector()->width();
            y += sector()->position().y() * sector()->height();
            setPosition(x, y);
            setPos(graphicalPosition(position()));
            break;
        }
    }
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

QRectF Object::boundingRect() const
{
    return QRectF(0, 0, SIZE, SIZE);
}

bool Object::animStopped() const
{
    return anim->state() == QPropertyAnimation::Stopped;
}

bool Object::alive() const
{
    return isAlive;
}

void Object::kill()
{
    isAlive = false;
    respawnTimer->start();
    anim->pause();
    hide();
}

void Object::respawn()
{
    isAlive = true;
    respawnTimer->stop();
    anim->resume();
    show();
}
