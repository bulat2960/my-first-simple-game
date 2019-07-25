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
#include "logic/game.h"
#include "logic/collisiondetector.h"
#include "logic/battleexecutor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTime midnight(0, 0, 0);
    qsrand(static_cast<uint>(midnight.secsTo(QTime::currentTime())));

    const int sHeight = 10;
    const int sWidth = 10;
    const int mHeight = 2;
    const int mWidth = 2;

    Maze* maze = new Maze(mHeight, mWidth, sHeight, sWidth);
    Player* player = new Player(maze->sector(0, 0), Qt::red);

    QVector<Bot*> bots;
    for (int i = 0; i < 2; i++)
    {
        Sector* randomSector = maze->sector(qrand() % mWidth, qrand() % mHeight);
        QColor randomColor = Qt::blue; //QColor(qrand() % 255, qrand() % 255, qrand() % 255);
        bots.push_back(new Bot(randomSector, randomColor));
    }

    CollisionDetector* detector = new CollisionDetector(player, bots);
    BattleExecutor* executor = new BattleExecutor();
    QObject::connect(detector, &CollisionDetector::signalBattle, executor, &BattleExecutor::slotBattle);

    Scene* scene = new Scene(maze, player, bots);
    View* view = new View(scene);
    Window* window = new Window(view);

    view->setScene(scene);
    view->setParent(window);
    QRect geometry = a.screens()[0]->geometry();
    view->setGeometry(geometry);

    window->show();

    return a.exec();
}
