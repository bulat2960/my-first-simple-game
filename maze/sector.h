#ifndef SECTOR_H
#define SECTOR_H

#include <QVector>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsRectItem>
#include <QObject>

#include "cell.h"

#include "globaloptions.h"


class Sector : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int x;
    int y;

    QVector<QVector<Cell>> matrix;

    QVector<Cell>& operator[](int index);
public:
    Sector(const QVector<QVector<Cell>>& matrix, int x, int y);

    QPoint position();

    int height() const;
    int width() const;

    Cell cell(int x, int y) const;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SECTOR_H
