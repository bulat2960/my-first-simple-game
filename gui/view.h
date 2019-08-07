#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QScrollBar>
#include <QKeyEvent>

#include "scene.h"
#include "gamedatapanel.h"
#include "buttonspanel.h"

class View : public QGraphicsView
{
    Q_OBJECT
private:
    Scene* scene;
    GameDataPanel* gameDataPanel;
    ButtonsPanel* buttonsPanel;
public:
    View(Scene* scene, GameDataPanel* gameDataPanel, ButtonsPanel* buttonsPanel);
public slots:
    bool eventFilter(QObject* object, QEvent* event) override;

};

#endif // VIEW_H
