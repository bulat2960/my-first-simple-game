#ifndef BOT_H
#define BOT_H

#include "character.h"

class Bot : public Character
{
private:
    void setStartPosition();
public:
    Bot(Sector* sector, QColor color);

    Sector* findNextSector(QPoint direction);
    QVector<QPoint> findMoveDirs();
public slots:
    void move();
};

#endif // BOT_H
