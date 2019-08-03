#include "object.h"

Object::Object(Sector* sector)
{
    mapPosition.sector = sector;

    animations.moveAnim = nullptr;
    animations.rotateAnim = nullptr;

    drawingSettings.color = Qt::black;

    setStartPosition();
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

void Object::setStartPosition()
{
    while (true)
    {
        int x = qrand() % sector()->width();
        int y = qrand() % sector()->height();

        bool atVerticalBorders = (x == 0) || (x == mapPosition.sector->width() - 1);
        bool atHorizontalBorders = (y == 0) || (y == mapPosition.sector->height() - 1);
        bool notAtBorders = !(atVerticalBorders || atHorizontalBorders);
        if (mapPosition.sector->cell(x, y).isRoad() && notAtBorders)
        {
            x += mapPosition.sector->position().x() * mapPosition.sector->width();
            y += mapPosition.sector->position().y() * mapPosition.sector->height();
            setPosition(x, y);
            setGraphicalPosition(x, y);
            break;
        }
    }
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

qreal Object::rot() const
{
    return this->rotation();
}

void Object::setRot(qreal angle)
{
    QTransform t = QTransform();
    t.translate(SIZE / 2, SIZE / 2);
    t.rotate(angle);
    t.translate(-SIZE / 2, -SIZE / 2);
    setTransform(t);
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
    return animations.moveAnim->state() == QPropertyAnimation::Stopped;
}
