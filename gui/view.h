#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QScrollBar>
#include <QKeyEvent>

#include "scene.h"
#include "gamedatapanel.h"

class View : public QGraphicsView
{
    Q_OBJECT
private:
    GameDataPanel* panel;
public:
    View(Scene* scene, GameDataPanel* panel);
public slots:
    bool eventFilter(QObject* object, QEvent* event) override;

};

#endif // VIEW_H
