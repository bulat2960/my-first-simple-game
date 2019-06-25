#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "maze/sector.h"
#include "maze/maze.h"
#include "gui/window.h"
#include "gui/view.h"
#include "gui/scene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const int sHeight = 10;
    const int sWidth = 10;
    const int mHeight = 10;
    const int mWidth = 10;

    Maze* maze = new Maze(mHeight, mWidth, sHeight, sWidth);
    Scene* scene = new Scene(maze);
    View* view = new View(scene);
    Window* window = new Window(view);

    view->setScene(scene);
    view->setParent(window);
    window->show();


    return a.exec();
}
