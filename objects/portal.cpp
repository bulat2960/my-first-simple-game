#include "portal.h"

Portal::Portal(Sector* sector) : FixedObject(sector)
{
    animations.rotateAnim = new QPropertyAnimation(this, "rot");
    animations.rotateAnim->setDuration(5000);
    animations.rotateAnim->setStartValue(0);
    animations.rotateAnim->setEndValue(3600);
    animations.rotateAnim->setLoopCount(-1);
    animations.rotateAnim->setEasingCurve(QEasingCurve::InOutSine);
    animations.rotateAnim->start();

    drawingSettings.pixmap.load(":/images/images/portal.png");
}

QPainterPath Portal::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());

    return path;
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(boundingRect().toRect(), drawingSettings.pixmap);
}
