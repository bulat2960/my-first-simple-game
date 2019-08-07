#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "view.h"
#include "gamedatapanel.h"
#include "buttonspanel.h"

class Window : public QWidget
{
private:
    View* view;
    ButtonsPanel* buttonsPanel;
public:
    Window(View* view, ButtonsPanel* buttonsPanel);
};

#endif // WINDOW_H
