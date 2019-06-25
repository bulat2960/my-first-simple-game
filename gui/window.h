#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "view.h"

class Window : public QWidget
{
    View* view;
public:
    Window(View* view);
};

#endif // WINDOW_H
