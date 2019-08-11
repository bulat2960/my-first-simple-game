#include "window.h"

Window::Window(View* view, GameDataPanel* gameDataPanel, ButtonsPanel* buttonsPanel, QWidget *parent) : QWidget(parent)
{
    this->view = view;
    this->gameDataPanel = gameDataPanel;
    this->buttonsPanel = buttonsPanel;

    installEventFilter(this);
}

bool Window::eventFilter(QObject* object, QEvent* event)
{
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    int key = keyEvent->key();

    if (event->type() == QEvent::KeyPress && key == Qt::Key_Escape)
    {
        if (buttonsPanel->isHidden())
        {
            buttonsPanel->show();
            buttonsPanel->slotPause();
        }
        else
        {
            buttonsPanel->hide();
            buttonsPanel->slotResume();
        }
        return true;
    }
    if (event->type() == QEvent::KeyPress && key == Qt::Key_Tab)
    {
        if (keyEvent->isAutoRepeat())
        {
            return QObject::eventFilter(object, event);
        }
        bool isGameDataPanelVisible = gameDataPanel->isVisible();
        if (isGameDataPanelVisible)
        {
            view->animDown();
            gameDataPanel->animDown();
        }
        else
        {
            view->animUp();
            gameDataPanel->animUp();
        }
        return true;
    }
    return QObject::eventFilter(object, event);
}
