#ifndef FIXEDOBJECT_H
#define FIXEDOBJECT_H

#include "object.h"

class FixedObject : public Object
{
public:
    FixedObject(Sector* sector);
};

#endif // FIXEDOBJECT_H
