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
#include "gui/gamedatapanel.h"
#include "gui/buttonspanel.h"
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
    const int mHeight = 3;
    const int mWidth = 6;
    const int botsNumber = 10;
    const int bonusesNumber = 10;
    const int portalsNumber = 10;

    Maze* maze = new Maze(mHeight, mWidth, sHeight, sWidth);

    Player* player = new Player(maze->sector(0, 0));
    player->setColor(Qt::red);
    player->setZValue(0);

    Game* game = new Game(maze, player);

    QScreen* screen = a.screens()[0];
    int screenHeight = screen->geometry().height();
    int screenWidth = screen->geometry().width();

    Scene* scene = new Scene(maze, player);
    QObject::connect(game, &Game::signalCreated, scene, &Scene::addItem);

    GameDataPanel* gameDataPanel = new GameDataPanel;

    View* view = new View(scene, gameDataPanel);
    view->setGeometry(0, BUTTONS_PANEL_HEIGHT, screenWidth, screenHeight - BUTTONS_PANEL_HEIGHT);

    gameDataPanel->setParent(view);
    gameDataPanel->setGeometry(0, view->height(), view->width(), 0);

    ButtonsPanel* buttonsPanel = new ButtonsPanel;
    buttonsPanel->setGeometry(0, 0, screenWidth, 50);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalExit, &a, QApplication::quit);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalStart, game, &Game::slotStart);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalResume, game, &Game::slotResume);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalPause, game, &Game::slotPause);

    Window* window = new Window(view, buttonsPanel);

    for (int i = 0; i < botsNumber; i++)
    {
        game->slotCreateBot();
    }
    for (int i = 0; i < bonusesNumber; i++)
    {
        game->slotCreateBonus();
    }
    for (int i = 0; i < portalsNumber; i++)
    {
        game->slotCreatePortal();
    }

    window->show();

    return a.exec();
}
