#include "bot.h"

Bot::Bot(Sector* sector) : Character(sector)
{
    connect(animations.moveAnim, &QPropertyAnimation::finished, this, &Bot::slotFindCorrectMoveDir);

    animations.moveAnim->setDuration(gameSettings.speed);

    target = nullptr;
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

void Bot::setTarget(Character* character)
{
    this->target = character;
}

Character* Bot::getTarget() const
{
    return target;
}

void Bot::slotFindCorrectMoveDir()
{
    if (!haveMovementPermission())
    {
        return;
    }

    QPoint left  = position() + directions[Qt::Key_A];
    QPoint right = position() + directions[Qt::Key_D];
    QPoint up    = position() + directions[Qt::Key_W];
    QPoint down  = position() + directions[Qt::Key_S];

    QVector<QPoint> dirs = {left, right, up, down};

    if (state == DO_NOTHING)
    {
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
        if (target == nullptr || target->sector() != this->sector())
        {
            setState(DO_NOTHING);
            slotFindCorrectMoveDir();
            return;
        }

        QVector<QVector<int>> digitMatrix = mapPosition.sector->digitMatrix();

        QPoint startPos = mapToSector(position(), mapPosition.sector);
        QPoint finishPos = mapToSector(target->position(), mapPosition.sector);

        // To fix bug with characters who stay very close
        if ((startPos - finishPos).manhattanLength() == 1 || (startPos - finishPos).manhattanLength() == -1)
        {
            move(finishPos);
            return;
        }

        int currentValue = 1;
        QVector<QPoint> points = {startPos};

        while (true)
        {
            QVector<QPoint> temp;
            for (int i = 0; i < dirs.size(); i++)
            {
                for (int j = 0; j < points.size(); j++)
                {
                    QPoint currentCell = points[j] + (dirs[i] - position());

                    if (currentCell.x() < 0 || currentCell.y() < 0 || currentCell.x() >= mapPosition.sector->width()
                        || currentCell.y() >= mapPosition.sector->height())
                    {
                        continue;
                    }

                    if (mapPosition.sector->cell(currentCell).isRoad() && digitMatrix[currentCell.y()][currentCell.x()] == 0
                            && currentCell != startPos)
                    {
                        digitMatrix[currentCell.y()][currentCell.x()] = currentValue;
                        temp.push_back(currentCell);
                    }
                }
            }

            if (temp.empty() || temp.contains(finishPos))
            {
                break;
            }

            points = temp;
            currentValue++;
        }

        QVector<QPoint> way;

        if (digitMatrix[finishPos.y()][finishPos.x()] != 0)
        {
            way.push_back(finishPos);

            while (true)
            {
                for (int i = 0; i < dirs.size(); i++)
                {
                    QPoint currentPoint = way.back();
                    QPoint nextPoint = currentPoint + (position() - dirs[i]);

                    if (nextPoint.x() < 0 || nextPoint.y() < 0 || nextPoint.x() >= mapPosition.sector->width()
                        || nextPoint.y() >= mapPosition.sector->height())
                    {
                        continue;
                    }
                    if (digitMatrix[currentPoint.y()][currentPoint.x()] == digitMatrix[nextPoint.y()][nextPoint.x()] + 1
                            && digitMatrix[nextPoint.y()][nextPoint.x()] != -1
                            && mapPosition.sector->cell(nextPoint).isRoad())
                    {
                        way.push_back(nextPoint);
                        break;
                    }
                }

                if (way.back() == startPos)
                {
                    break;
                }
            }

            if (way.size() != 0)
            {
                way.pop_back();
                move(way.back());
            }
        }
    }
}
