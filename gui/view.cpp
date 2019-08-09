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
        invalidateScene(scene->sceneRect());
        return parentWidget()->eventFilter(object, event);
    }

    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
         return scene->eventFilter(object, event);
    }
    return QObject::eventFilter(object, event);
}
