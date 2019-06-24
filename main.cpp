#include <QApplication>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "maze/builder.h"
#include "maze/sector.h"

QVector<QVector<Sector*>> createSectors(int mH, int mW, int sH, int sW)
{
    Builder builder(sH, sW);

    QVector<QVector<Sector*>> maze;

    for (int i = 0; i < mH; i++)
    {
        QVector<Sector*> sectorRow;
        for (int j = 0; j < mW; j++)
        {
            QVector<QVector<Cell>> sectorMatrix = builder.create();
            Sector* sector = new Sector(sectorMatrix, j, i);
            sectorRow.push_back(sector);
        }
        maze.push_back(sectorRow);
    }

    return maze;
}

void addSectorsToScene(QVector<QVector<Sector*>> sectors, QGraphicsScene* scene)
{
    for (int i = 0; i < sectors.size(); i++)
    {
        for (int j = 0; j < sectors[i].size(); j++)
        {
            Sector* sector = sectors[i][j];

            QPoint pos = sector->position();
            int p1 = pos.x() * sector->width();
            int p2 = pos.y() * sector->height();
            sector->setPos(QPoint(p1, p2) * SIZE);

            scene->addItem(sector);
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const int sHeight = 10;
    const int sWidth = 10;
    const int mHeight = 10;
    const int mWidth = 10;

    QWidget* widget = new QWidget;
    QGraphicsView* view = new QGraphicsView;
    QGraphicsScene* scene = new QGraphicsScene;

    QVector<QVector<Sector*>> maze = createSectors(mHeight, mWidth, sHeight, sWidth);
    addSectorsToScene(maze, scene);


    view->setScene(scene);
    view->setParent(widget);
    widget->show();


    return a.exec();
}
