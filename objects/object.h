#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsObject>

#include "maze/sector.h"

class Object : public QGraphicsObject
{
    Q_OBJECT
protected:
    QPoint objPosition;
    QColor objColor;

    Sector* objSector;
protected:
    QPoint mapToSector(QPoint p, Sector *sector) const;
public:
    Object(Sector* sector, QColor color);

    QPoint position() const;
    void setPosition(int x, int y);
    void setPosition(const QPoint& position);

    Sector* sector() const;
    void setSector(Sector* sector);

    QColor color() const;
    void setColor(QColor color);
signals:
    void signalCheckCollisions();
};

#endif // OBJECT_H
