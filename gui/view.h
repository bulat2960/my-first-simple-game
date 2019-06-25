#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QScrollBar>

#include "scene.h"

class View : public QGraphicsView
{
public:
    View(Scene* scene);
};

#endif // VIEW_H
