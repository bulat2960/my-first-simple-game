#ifndef SECTOR_H
#define SECTOR_H

#include <QGraphicsRectItem>
#include <QObject>
#include "cell.h"

#include "globaloptions.h"


class Sector : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int m_x;
    int m_y;

    int m_height;
    int m_width;
public:
    Sector(const QVector<QVector<Cell>>& matrix, int x, int y, int size);
};

#endif // SECTOR_H
