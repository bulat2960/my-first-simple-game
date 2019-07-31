﻿#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QTimer>

#include "maze/sector.h"

class Object : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal rot READ rot WRITE setRot)
protected:
    QPoint objPosition;
    QColor objColor;

    Sector* objSector;

    QPropertyAnimation* moveAnim;
    QPropertyAnimation* rotateAnim;

    bool isAlive;
    QTimer* respawnTimer;
protected:
    QPoint mapToSector(QPoint p, Sector *sector) const;
    QPoint graphicalPosition(const QPoint& position) const;

    bool moveAnimStopped() const;
public:
    Object(Sector* sector, QColor color);

    QPoint position() const;
    void setPosition(int x, int y);
    void setPosition(const QPoint& position);

    void setStartPosition();

    Sector* sector() const;
    void setSector(Sector* sector);

    QColor color() const;
    void setColor(QColor color);

    qreal rot() const;
    void setRot(qreal angle);

    bool alive() const;
    void kill();
    void respawn();
signals:
    void signalCheckCollisions();
public slots:
    virtual QRectF boundingRect() const override;
};

#endif // OBJECT_H
