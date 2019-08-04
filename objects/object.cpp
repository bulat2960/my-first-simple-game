#include "object.h"

Object::Object(Sector* sector)
{
    mapPosition.sector = sector;

    drawingSettings.color = Qt::black;

    setGraphicalPosition(mapPosition.coords);
}

QPoint Object::graphicalPosition(int x, int y) const
{
    return QPoint(x, y) * SIZE;
}

QPoint Object::graphicalPosition(const QPoint &position) const
{
    return position * SIZE;
}

void Object::setGraphicalPosition(int x, int y)
{
    setPos(QPoint(x, y) * SIZE);
}

void Object::setGraphicalPosition(const QPoint& position)
{
    setPos(position * SIZE);
}

QPoint Object::position() const
{
    return mapPosition.coords;
}

void Object::setPosition(int x, int y)
{
    mapPosition.coords = QPoint(x, y);
}

void Object::setPosition(const QPoint& position)
{
    mapPosition.coords = position;
}

Sector* Object::sector() const
{
    return mapPosition.sector;
}

void Object::setSector(Sector* sector)
{
    mapPosition.sector = sector;
}

QColor Object::color() const
{
    return drawingSettings.color;
}

void Object::setColor(QColor color)
{
    for (int i = 0; i < drawingSettings.image.width(); i++)
    {
        for (int j = 0; j < drawingSettings.image.height(); j++)
        {
            if (drawingSettings.image.pixelColor(i, j) == drawingSettings.color)
            {
                drawingSettings.image.setPixelColor(i, j, color);
            }
        }
    }

    drawingSettings.color = color;
}

QPoint Object::mapToSector(QPoint p, Sector* sector) const
{
    return QPoint(p.x() % sector->width(), p.y() % sector->height());
}

QRectF Object::boundingRect() const
{
    return QRectF(0, 0, SIZE, SIZE);
}
