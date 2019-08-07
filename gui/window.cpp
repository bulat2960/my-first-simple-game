#include "window.h"

Window::Window(View* view, ButtonsPanel* buttonsPanel)
{
    this->view = view;
    view->setParent(this);

    this->buttonsPanel = buttonsPanel;
    buttonsPanel->setParent(this);

    installEventFilter(view);
}
