#include "sector.h"

Sector::Sector(const QVector<QVector<Cell>>& matrix, int x, int y)
{
    this->matrix = matrix;
    this->x = x;
    this->y = y;
}

QPoint Sector::position()
{
    return QPoint(x, y);
}

void Sector::setPosition(QPoint pos)
{
    this->x = pos.x();
    this->y = pos.y();
}

int Sector::height() const
{
    return matrix.size();
}

int Sector::width() const
{
    return matrix[0].size();
}

Cell Sector::cell(int x, int y) const
{
    return matrix[y][x];
}

QRectF Sector::boundingRect() const
{
    return QRectF(0, 0, width() * SIZE, height() * SIZE);
}

QPainterPath Sector::shape() const
{
    QPainterPath path;
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            if (cell(i, j).isWall())
            {
                QRect rect = QRect(cell(i, j).x * SIZE, cell(i, j).y * SIZE, SIZE, SIZE);
                rect.adjust(1, 1, -1, -1);
                path.addRect(rect);
            }
        }
    }
    return path;
}

void Sector::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPointF center = QPointF(height() * SIZE / 2, height() * SIZE / 2);
    QRadialGradient grad(center, width() * SIZE / 2, center);

    grad.setColorAt(0, Qt::black);
    grad.setColorAt(0.5, Qt::gray);
    grad.setColorAt(1, Qt::lightGray);

    painter->setPen(Qt::NoPen);

    painter->fillPath(shape(), grad);

    painter->setPen(Qt::black);
    painter->drawRect(0, 0, width() * SIZE, height() * SIZE);
}
