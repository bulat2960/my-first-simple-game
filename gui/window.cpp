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
    if (event->type() != QEvent::LayoutRequest && event->type() != QEvent::UpdateRequest && event->type() != QEvent::ToolTip
            && event->type() != QEvent::Leave && event->type() != QEvent::Enter)
    {
        qDebug() << "WINDOW" << this << object;
        qDebug() << "WINDOW EVENT" << event->type() << hasFocus();
        qDebug() << "";
    }

    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    int key = keyEvent->key();

    if (event->type() == QEvent::KeyPress && key == Qt::Key_Escape)
    {
        buttonsPanel->isHidden() ? buttonsPanel->show() : buttonsPanel->hide();
        return true;
    }
    if (event->type() == QEvent::KeyPress && key == Qt::Key_Tab)
    {
        if (keyEvent->isAutoRepeat())
        {
            return QObject::eventFilter(object, event);
        }
        bool isGameDataPanelVisible = gameDataPanel->isVisible();
        isGameDataPanelVisible ? gameDataPanel->animHide() : gameDataPanel->animShow();
        return true;
    }
    return QObject::eventFilter(object, event);
}
