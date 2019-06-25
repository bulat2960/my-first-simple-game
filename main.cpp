#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScreen>
#include <QTime>

#include "maze/sector.h"
#include "maze/maze.h"
#include "gui/window.h"
#include "gui/view.h"
#include "gui/scene.h"
#include "objects/player.h"
#include "objects/bot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTime midnight(0, 0, 0);
    qsrand(static_cast<uint>(midnight.secsTo(QTime::currentTime())));

    const int sHeight = 6;
    const int sWidth = 6;
    const int mHeight = 3;
    const int mWidth = 3;

    Maze* maze = new Maze(mHeight, mWidth, sHeight, sWidth);
    Player* player = new Player(maze->sector(0, 0), Qt::red);
    Bot* bot = new Bot(maze->sector(0, 0), Qt::blue);


    Scene* scene = new Scene(maze, player, bot);
    View* view = new View(scene);
    Window* window = new Window(view);


    view->setScene(scene);
    view->setParent(window);
    QRect geometry = a.screens()[0]->geometry();
    view->setGeometry(geometry);

    window->showFullScreen();


    return a.exec();
}
