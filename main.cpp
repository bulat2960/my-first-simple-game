#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScreen>

#include "maze/sector.h"
#include "maze/maze.h"
#include "gui/window.h"
#include "gui/view.h"
#include "gui/scene.h"
#include "objects/player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const int sHeight = 10;
    const int sWidth = 10;
    const int mHeight = 10;
    const int mWidth = 10;

    Maze* maze = new Maze(mHeight, mWidth, sHeight, sWidth);
    Player* player = new Player(maze->sector(0, 0), Qt::red);

    Scene* scene = new Scene(maze, player);
    View* view = new View(scene);
    Window* window = new Window(view);


    view->setScene(scene);
    view->setParent(window);
    QRect geometry = a.screens()[0]->geometry();
    view->setGeometry(geometry);

    window->showFullScreen();


    return a.exec();
}
