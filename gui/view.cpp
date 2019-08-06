#include "view.h"

View::View(Scene* scene, GameDataPanel *panel) : QGraphicsView(scene)
{
    this->panel = panel;

    installEventFilter(this);

    centerOn(0, 0);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFrameStyle(0);
}

bool View::eventFilter(QObject* obj, QEvent* event)
{
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    int key = keyEvent->key();

    if (key == Qt::Key_Tab)
    {
        if (panel->isHidden())
        {
            panel->show();
        }
        else
        {
            panel->hide();
        }
        return true;
    }
    return QObject::eventFilter(obj, event);
}
