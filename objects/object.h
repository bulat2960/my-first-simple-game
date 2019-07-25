#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsObject>
#include <QPropertyAnimation>

#include "maze/sector.h"

class Object : public QGraphicsObject
{
    Q_OBJECT
protected:
    QPoint objPosition;
    QColor objColor;

    Sector* objSector;

    QPropertyAnimation* anim;
protected:
    QPoint mapToSector(QPoint p, Sector *sector) const;
public:
    Object(Sector* sector, QColor color);

    QPoint position() const;
    QPoint graphicalPosition(const QPoint& position) const;
    void setPosition(int x, int y);
    void setPosition(const QPoint& position);

    void setStartPosition();

    Sector* sector() const;
    void setSector(Sector* sector);

    QColor color() const;
    void setColor(QColor color);

    bool animStopped() const;
signals:
    void signalCheckCollisions();
public slots:
    QRectF boundingRect() const override;
};

#endif // OBJECT_H
