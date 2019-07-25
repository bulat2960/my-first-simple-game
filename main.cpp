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
    const int botsNumber = 2;
    const int bonusesNumber = 5;
    const int portalsNumber = 0;

    Game* game = new Game(botsNumber, bonusesNumber, portalsNumber, mHeight, mWidth, sHeight, sWidth);

    Scene* scene = new Scene(game->getMaze(), game->getPlayer(), game->getBots(), game->getBonuses());
    View* view = new View(scene);
    Window* window = new Window(view);

    view->setScene(scene);
    view->setParent(window);
    QRect geometry = a.screens()[0]->geometry();
    view->setGeometry(geometry);

    window->show();

    game->start();

    return a.exec();
}
