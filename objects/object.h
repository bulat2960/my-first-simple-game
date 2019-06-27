#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsObject>

#include "maze/sector.h"

class Object : public QGraphicsObject
{
    Q_OBJECT
protected:
    QPoint position;
    QColor color;

    Sector* sector;
public:
    Object(Sector* sector, QColor color);

    QPoint getPosition() const;
signals:
    void signalCheckCollisions();
};

#endif // OBJECT_H
