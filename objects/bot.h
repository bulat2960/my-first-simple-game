#ifndef BOT_H
#define BOT_H

#include "character.h"

class Bot : public Character
{
private:
    void setStartPosition();
    QVector<QPoint> findMoveDirs();
public:
    Bot(Sector* sector, QColor color);
public slots:
    void move();
};

#endif // BOT_H
