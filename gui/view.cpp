#include "view.h"

View::View(Scene* scene) : QGraphicsView(scene)
{
    verticalScrollBar()->setStyleSheet("QScrollBar {height:0px;}");
    horizontalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
}
