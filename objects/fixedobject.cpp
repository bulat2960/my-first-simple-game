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
