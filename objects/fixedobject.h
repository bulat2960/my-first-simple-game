#ifndef FIXEDOBJECT_H
#define FIXEDOBJECT_H

#include "object.h"

class FixedObject : public Object
{
public:
    FixedObject(Sector* sector, QColor color);
};

#endif // FIXEDOBJECT_H
