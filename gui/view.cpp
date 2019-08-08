#include "view.h"

View::View(Scene* scene) : QGraphicsView(scene)
{
    this->scene = scene;

    setScene(scene);

    installEventFilter(this);

    centerOn(0, 0);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFrameStyle(0);
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
         scene->eventFilter(object, event);
         return true;
    }
    return QObject::eventFilter(object, event);
}
