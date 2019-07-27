#include "object.h"

Object::Object(Sector* sector, QColor color)
{
    objSector = sector;
    objColor = color;

    isAlive = true;
    respawnTimer = nullptr;

    moveAnim = nullptr;

    setStartPosition();
    setPos(graphicalPosition(position()));
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

        bool notAtBorders = !(x == 0 || y == 0 || x == sector()->width() - 1 || y == sector()->height() - 1);
        if (sector()->cell(x, y).isRoad() && notAtBorders)
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

bool Object::moveAnimStopped() const
{
    return moveAnim->state() == QPropertyAnimation::Stopped;
}

bool Object::alive() const
{
    return isAlive;
}

void Object::kill()
{
    isAlive = false;
    respawnTimer->start();
    if (moveAnim->state() == QPropertyAnimation::Running)
    {
        moveAnim->pause();
    }
    hide();
}

void Object::respawn()
{
    isAlive = true;
    respawnTimer->stop();
    if (moveAnim->state() == QPropertyAnimation::Paused)
    {
        moveAnim->resume();
    }
    show();
}
