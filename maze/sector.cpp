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
    path.addRect(boundingRect());
    return path;
}

void Sector::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    QPointF center = QPointF(height() * SIZE / 2, height() * SIZE / 2);
    QRadialGradient grad(center, width() * SIZE / 2, center);

    bool mouseOver = (option->state & QStyle::State_MouseOver);
    grad.setColorAt(0, !mouseOver ? Qt::white : Qt::black);
    grad.setColorAt(0.5, !mouseOver ? Qt::red : Qt::green);
    grad.setColorAt(1, !mouseOver ? Qt::black : Qt::white);

    painter->setPen(Qt::NoPen);

    for (int i = 0; i < height(); i++)
    {
        for (int j = 0; j < width(); j++)
        {
            QPoint topLeft = {j * SIZE, i * SIZE};
            QPoint bottomRight = topLeft + QPoint(SIZE - 1, SIZE - 1);
            QRect rect = QRect(topLeft, bottomRight);

            if (cell(j, i).isWall())
            {
                painter->setBrush(grad);
                painter->drawRect(rect);
                painter->setBrush(Qt::BrushStyle::NoBrush);
            }
        }
    }
}
