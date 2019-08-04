#include "window.h"

Window::Window(View* view)
{
    this->view = view;

    this->gameData = new GameData(this);
    gameData->setGeometry(0, 0, 300, 300);
    gameData->show();
    gameData->activateWindow();
}

void Window::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Tab)
    {
        qDebug() << "Show";
        gameData->show();
    }
}

void Window::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Tab)
    {
        qDebug() << "Hide";
        gameData->hide();
    }
}
