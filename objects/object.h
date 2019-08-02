#ifndef OBJECT_H
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
    struct MapPosition
    {
        QPoint coords;
        Sector* sector;
    };
    MapPosition mapPosition;

    struct Animations
    {
        QPropertyAnimation* moveAnim;
        QPropertyAnimation* rotateAnim;
    };
    Animations animations;

    struct DrawingSettings
    {
        QPixmap pixmap;
        QColor color;
    };
    DrawingSettings drawingSettings;
protected:
    QPoint mapToSector(QPoint p, Sector *sector) const;

    QPoint graphicalPosition(int x, int y) const;
    QPoint graphicalPosition(const QPoint& position) const;
    void setGraphicalPosition(int x, int y);
    void setGraphicalPosition(const QPoint& position);

    bool moveAnimStopped() const;

    void setStartPosition();
public:
    Object(Sector* sector, QColor color);

    QPoint position() const;
    void setPosition(int x, int y);
    void setPosition(const QPoint& position);

    Sector* sector() const;
    void setSector(Sector* sector);

    QColor color() const;
    void setColor(QColor color);

    qreal rot() const;
    void setRot(qreal angle);
signals:
    void signalCheckCollisions();
public slots:
    virtual QRectF boundingRect() const override;
};

#endif // OBJECT_H
