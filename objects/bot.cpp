#include "bot.h"

Bot::Bot(Sector* sector) : Character(sector)
{
    connect(animations.moveAnim, &QPropertyAnimation::finished, this, &Bot::slotFindCorrectMoveDir);

    state = DO_NOTHING;
}

Bot::State Bot::getState() const
{
    return state;
}

void Bot::setState(State state)
{
    this->state = state;
}

void Bot::slotFindCorrectMoveDir()
{
    if (!haveMovementPermission())
    {
        return;
    }

    if (state == DO_NOTHING)
    {
        QPoint left  = position() + directions[Qt::Key_A];
        QPoint right = position() + directions[Qt::Key_D];
        QPoint up    = position() + directions[Qt::Key_W];
        QPoint down  = position() + directions[Qt::Key_S];

        QVector<QPoint> dirs = {left, right, up, down};
        QVector<QPoint> validDirs;

        for (int i = 0; i < dirs.size(); i++)
        {
            QPoint nextPos = dirs[i];

            if (!insideScene(nextPos))
            {
                continue;
            }

            Sector* next = findNextSector(nextPos);
            QPoint sectorPos = QPoint(nextPos.x() % next->width(), nextPos.y() % next->height());
            bool roadInCurrentSector = sector()->cell(sectorPos.x(), sectorPos.y()).isRoad();
            bool roadInNextSector = next->cell(sectorPos.x(), sectorPos.y()).isRoad();

            bool validDirInCurrentSector = (sector() == next && roadInCurrentSector);
            bool validDirInNextSector = (sector() != next && roadInNextSector);

            if (validDirInCurrentSector || validDirInNextSector)
            {
                validDirs.push_back(nextPos);
            }
        }

        QPoint nextPos = validDirs[qrand() % validDirs.size()];
        move(nextPos);
    }
    if (state == ATTACK)
    {

    }
}
