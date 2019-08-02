#ifndef PORTAL_H
#define PORTAL_H

#include "fixedobject.h"
#include "maze/sector.h"

class Portal : public FixedObject
{
    Q_OBJECT
private:
    Sector* other;
public:
    Portal(Sector* sector, QColor color);
public slots:
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // PORTAL_H
