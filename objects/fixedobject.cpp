#include "fixedobject.h"

FixedObject::FixedObject(Sector* sector) : Object(sector)
{
    animations.rotateAnim = new QPropertyAnimation(this, "rot");
    animations.rotateAnim->setDuration(5000);
    animations.rotateAnim->setStartValue(0);
    animations.rotateAnim->setEndValue(3600);
    animations.rotateAnim->setLoopCount(-1);
    animations.rotateAnim->setEasingCurve(QEasingCurve::InOutSine);
    animations.rotateAnim->start();

    setStartPosition();
}

qreal FixedObject::rot() const
{
    return this->rotation();
}

void FixedObject::setRot(qreal angle)
{
    QTransform t = QTransform();
    t.translate(SIZE / 2, SIZE / 2);
    t.rotate(angle);
    t.translate(-SIZE / 2, -SIZE / 2);
    setTransform(t);
}

void FixedObject::setStartPosition()
{
    while (true)
    {
        int x = qrand() % sector()->width();
        int y = qrand() % sector()->height();

        bool atVerticalBorders = (x == 0) || (x == mapPosition.sector->width() - 1);
        bool atHorizontalBorders = (y == 0) || (y == mapPosition.sector->height() - 1);
        bool notAtBorders = !(atVerticalBorders || atHorizontalBorders);
        if (mapPosition.sector->cell(x, y).isRoad() && notAtBorders)
        {
            x += mapPosition.sector->position().x() * mapPosition.sector->width();
            y += mapPosition.sector->position().y() * mapPosition.sector->height();
            setPosition(x, y);
            setGraphicalPosition(x, y);
            break;
        }
    }
}
