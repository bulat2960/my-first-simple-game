#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsObject>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPixmap>
#include <QBitmap>

#include "maze/sector.h"

class Object : public QGraphicsObject
{
    Q_OBJECT
protected:
    struct MapPosition
    {
        QPoint coords;
        Sector* sector;
    };
    MapPosition mapPosition;

    struct DrawingSettings
    {
        QImage image;
        QColor color;
    };
    DrawingSettings drawingSettings;
protected:
    QPoint mapToSector(QPoint p, Sector *sector) const;

    QPoint graphicalPosition(int x, int y) const;
    QPoint graphicalPosition(const QPoint& position) const;
    void setGraphicalPosition(int x, int y);
    void setGraphicalPosition(const QPoint& position);

    virtual void setStartPosition() = 0;
public:
    Object(Sector* sector);

    QPoint position() const;
    void setPosition(int x, int y);
    void setPosition(const QPoint& position);

    Sector* sector() const;
    void setSector(Sector* sector);

    QColor color() const;
    void setColor(QColor color);
public slots:
    virtual QRectF boundingRect() const override;
};

#endif // OBJECT_H
