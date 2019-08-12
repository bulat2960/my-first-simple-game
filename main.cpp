#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScreen>
#include <QTime>

#include "maze/sector.h"
#include "maze/maze.h"
#include "gui/view.h"
#include "gui/scene.h"
#include "gui/gamedatapanel.h"
#include "gui/buttonspanel.h"
#include "gui/window.h"
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
    const int bonusesNumber = 0;
    const int portalsNumber = 10;

    QScreen* screen = a.screens()[0];
    int screenHeight = screen->geometry().height();
    int screenWidth = screen->geometry().width();

    Maze* maze = new Maze(mHeight, mWidth, sHeight, sWidth);

    Player* player = new Player(maze->sector(0, 0));
    player->setColor(Qt::red);
    player->setZValue(0);

    Game* game = new Game(maze, player);

    Scene* scene = new Scene(maze, player);
    QObject::connect(game, &Game::signalCreated, scene, &Scene::addItem);

    GameDataPanel* gameDataPanel = new GameDataPanel;
    ButtonsPanel* buttonsPanel = new ButtonsPanel;

    View* view = new View(scene);

    Window* window = new Window(view, gameDataPanel, buttonsPanel);
    window->setGeometry(0, 0, screenWidth, screenHeight);
    window->setFocus();

    view->setParent(window);
    view->setGeometry(window->geometry());

    QPoint menuTopLeft = QPoint((screenWidth - MENU_PANEL_WIDTH) / 2, (screenHeight - MENU_PANEL_HEIGHT) / 2);
    QPoint menuBottomRight = menuTopLeft + QPoint(MENU_PANEL_WIDTH, MENU_PANEL_HEIGHT);
    buttonsPanel->setGeometry(QRect(menuTopLeft, menuBottomRight));
    buttonsPanel->setParent(window);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalExit, &a, QApplication::quit);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalStart, game, &Game::slotStart);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalResume, game, &Game::slotResume);
    QObject::connect(buttonsPanel, &ButtonsPanel::signalPause, game, &Game::slotPause);

    gameDataPanel->setGeometry(0, window->height(), window->width(), 0);
    gameDataPanel->setParent(window);
    QObject::connect(game, &Game::signalSendToGamePanel, gameDataPanel, &GameDataPanel::slotReceiveDataFromGame);

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

    window->showFullScreen();

    return a.exec();
}
