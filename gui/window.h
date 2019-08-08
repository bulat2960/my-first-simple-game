#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "gamedatapanel.h"
#include "buttonspanel.h"
#include "view.h"

class Window : public QWidget
{
    Q_OBJECT
private:
    View* view;
    GameDataPanel* gameDataPanel;
    ButtonsPanel* buttonsPanel;
public:
    Window(View* view, GameDataPanel* gameDataPanel, ButtonsPanel* buttonsPanel, QWidget* parent = nullptr);
public slots:
    bool eventFilter(QObject* object, QEvent* event) override;
};

#endif // WINDOW_H
