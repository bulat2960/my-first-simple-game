#ifndef PORTAL_H
#define PORTAL_H

#include "object.h"
#include "maze/sector.h"

class Portal : public Object
{
    Q_OBJECT
public:
    Portal(int x, int y, Sector* sector, QColor color);
public slots:

};

#endif // PORTAL_H
