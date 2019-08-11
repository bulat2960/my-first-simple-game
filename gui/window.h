#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QAnimationGroup>

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

    QAnimationGroup* animGroupUp;
    QAnimationGroup* animGroupDown;
    bool isGameDataPanelVisible;
private:
    void animUp();
    void animDown();
public:
    Window(View* view, GameDataPanel* gameDataPanel, ButtonsPanel* buttonsPanel, QWidget* parent = nullptr);
public slots:
    bool eventFilter(QObject* object, QEvent* event) override;
};

#endif // WINDOW_H
