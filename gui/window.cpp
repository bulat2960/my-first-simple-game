#include "window.h"

Window::Window(View* view)
{
    this->view = view;
    installEventFilter(view);
}
