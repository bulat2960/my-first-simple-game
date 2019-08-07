#include "view.h"

View::View(Scene* scene, GameDataPanel *panel) : QGraphicsView(scene)
{
    this->panel = panel;
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

    if (event->type() == QEvent::FocusOut)
    {
        setFocus();
    }
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        if (key != Qt::Key_Tab)
        {
            scene->eventFilter(object, event);
        }
        else
        {
            if (keyEvent->isAutoRepeat() == false)
            {
                panel->startAnimation();
            }

        }
        return true;
    }
    return QObject::eventFilter(object, event);
}
