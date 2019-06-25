#include "view.h"

View::View(Scene* scene) : QGraphicsView(scene)
{
    centerOn(0, 0);
    verticalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    horizontalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
}
