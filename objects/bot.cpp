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

Sector* Bot::findNextSector(QPoint direction)
{
    QPoint next = direction * SIZE;
    QRect nextRect = QRect(next.x(), next.y(), SIZE, SIZE);
    Sector* nextSector = dynamic_cast<Sector*>(scene()->items(nextRect, Qt::IntersectsItemBoundingRect)[0]);
    return nextSector;
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
        QPoint p = dirs[i];
        QRect sceneRect = scene()->sceneRect().toRect();
        QPoint scenePos = p * SIZE;
        bool insideHorizontal = (scenePos.x() >= 0) && (scenePos.x() < sceneRect.width());
        bool insideVertical = (scenePos.y() >= 0) && (scenePos.y() < sceneRect.height());
        bool inside = (insideVertical && insideHorizontal);

        if (inside)
        {
            Sector* next = findNextSector(p);
            QPoint sectorPos = QPoint(p.x() % next->width(), p.y() % next->height());
            bool check1 = sector->cell(sectorPos.x(), sectorPos.y()).isRoad();
            bool check2 = next->cell(sectorPos.x(), sectorPos.y()).isRoad();

            bool checkInCurrentSector = (sector == next && check1);
            bool checkInSectorCrossing = (sector != next && check2);

            if (checkInCurrentSector || checkInSectorCrossing)
            {
                realDirs.push_back(p);
            }
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
