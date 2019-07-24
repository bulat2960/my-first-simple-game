#include "bot.h"

#include <QDebug>

Bot::Bot(Sector* sector, QColor color) : Character(sector, color)
{
    setStartPosition();

    connect(anim, &QPropertyAnimation::finished, this, &Bot::move);
}

void Bot::setStartPosition()
{
    while (true)
    {
        int x = qrand() % sector->width();
        int y = qrand() % sector->height();
        if (sector->cell(x, y).isRoad())
        {
            x += sector->position().x() * sector->width();
            y += sector->position().y() * sector->height();
            position = QPoint(x, y);
            setPos(position * SIZE);
            break;
        }
    }
}

QVector<QPoint> Bot::findMoveDirs()
{
    QPoint left  = position + directions[Qt::Key_A];
    QPoint right = position + directions[Qt::Key_D];
    QPoint up    = position + directions[Qt::Key_W];
    QPoint down  = position + directions[Qt::Key_S];

    QVector<QPoint> dirs = {left, right, up, down};
    QVector<QPoint> realDirs;

    for (int i = 0; i < dirs.size(); i++)
    {
        QPoint nextPos = dirs[i];

        if (!isInsideScene(nextPos))
        {
            continue;
        }

        Sector* next = findNextSector(nextPos);
        QPoint sectorPos = QPoint(nextPos.x() % next->width(), nextPos.y() % next->height());
        bool check1 = sector->cell(sectorPos.x(), sectorPos.y()).isRoad();
        bool check2 = next->cell(sectorPos.x(), sectorPos.y()).isRoad();

        bool checkInCurrentSector = (sector == next && check1);
        bool checkInSectorCrossing = (sector != next && check2);

        if (checkInCurrentSector || checkInSectorCrossing)
        {
            realDirs.push_back(nextPos);
        }
    }

    return realDirs;
}

void Bot::move()
{
    QVector<QPoint> realDirs = findMoveDirs();
    QPoint nextPos = realDirs[qrand() % realDirs.size()];

    startAnimation(position, nextPos);

    position = nextPos;
    sector = findNextSector(position);
}
