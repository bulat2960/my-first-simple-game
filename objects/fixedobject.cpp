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
