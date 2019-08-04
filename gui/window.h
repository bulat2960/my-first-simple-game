#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include "view.h"
#include "gamedata.h"

class Window : public QWidget
{
private:
    View* view;
    GameData* gameData;
public:
    Window(View* view);
public slots:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};

#endif // WINDOW_H
