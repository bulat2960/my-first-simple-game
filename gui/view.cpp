#include "view.h"

View::View(Scene* scene) : QGraphicsView(scene)
{
    this->scene = scene;

    anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(200);

    setScene(scene);

    installEventFilter(this);

    centerOn(0, 0);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFrameStyle(0);
}

void View::animUp()
{
    if (anim->state() != QPropertyAnimation::Stopped)
    {
        anim->stop();
    }
    anim->setStartValue(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    anim->setEndValue(QRect(0, 0, parentWidget()->width(), parentWidget()->height() - GAME_DATA_PANEL_HEIGHT));
    anim->start();
}

void View::animDown()
{
    if (anim->state() != QPropertyAnimation::Stopped)
    {
        anim->stop();
    }
    anim->setStartValue(QRect(0, 0, parentWidget()->width(), parentWidget()->height() - GAME_DATA_PANEL_HEIGHT));
    anim->setEndValue(QRect(0, 0, parentWidget()->width(), parentWidget()->height()));
    anim->start();
}

Scene* View::getScene() const
{
    return scene;
}

bool View::eventFilter(QObject* object, QEvent* event)
{
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    int key = keyEvent->key();

    if (event->type() == QEvent::KeyPress && (key == Qt::Key_Escape || key == Qt::Key_Tab))
    {
        return parentWidget()->eventFilter(object, event);
    }

    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
         return scene->eventFilter(object, event);
    }
    return QObject::eventFilter(object, event);
}
