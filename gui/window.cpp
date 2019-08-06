#include "window.h"

Window::Window(View* view)
{
    this->view = view;

    installEventFilter(this);
}

bool Window::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
    {
        return true;
    }
    if (event->type() != QEvent::Type::UpdateRequest)
    {
        return true;
    }
    return QObject::eventFilter(object, event);
}
