#include "view.h"

View::View(Scene* scene, GameDataPanel* gameDataPanel, ButtonsPanel* buttonsPanel) : QGraphicsView(scene)
{
    this->gameDataPanel = gameDataPanel;
    this->buttonsPanel = buttonsPanel;
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

    if (event->type() == QEvent::KeyPress && key == Qt::Key_Escape)
    {
        buttonsPanel->isHidden() ? buttonsPanel->show() : buttonsPanel->hide();
        return true;
    }
    if (event->type() == QEvent::KeyPress && key == Qt::Key_Tab)
    {
        gameDataPanel->animShow();
        return true;
    }
    if (event->type() == QEvent::KeyRelease && key == Qt::Key_Tab)
    {
        gameDataPanel->animHide();
        return true;
    }
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
         scene->eventFilter(object, event);
         return true;
    }
    return QObject::eventFilter(object, event);
}
