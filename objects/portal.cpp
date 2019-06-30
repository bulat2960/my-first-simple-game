#include "portal.h"

Portal::Portal(int x, int y, Sector* sector, QColor color) : Object(sector, color)
{
    position = QPoint(x, y);
}
