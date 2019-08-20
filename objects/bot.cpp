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

QVector<QVector<int>> Bot::generateFilledDigitMatrix(QPoint start, QPoint finish)
{
    QPoint left  = directions[Qt::Key_A];
    QPoint right = directions[Qt::Key_D];
    QPoint up    = directions[Qt::Key_W];
    QPoint down  = directions[Qt::Key_S];

    QVector<QPoint> dirs = {left, right, up, down};

    QVector<QVector<int>> digitMatrix = mapPosition.sector->digitMatrix();

    int value = 2;
    QVector<QPoint> points = {start};

    while (true)
    {
        QVector<QPoint> temp;

        foreach (QPoint currentPoint, points)
        {
            foreach (QPoint dir, dirs)
            {
                QPoint nextPoint = currentPoint + dir;
                QPoint mappedNextPoint = mapToSector(nextPoint);

                if (!isBelongsToCurrentSector(nextPoint) || mapPosition.sector->cell(mappedNextPoint).isWall())
                {
                    continue;
                }

                if (digitMatrix[mappedNextPoint.y()][mappedNextPoint.x()] == 1 && nextPoint != start)
                {
                    digitMatrix[mappedNextPoint.y()][mappedNextPoint.x()] = value;
                    temp.push_back(nextPoint);
                }

                if (nextPoint == finish)
                {
                    return digitMatrix;
                }
            }
        }

        points = temp;
        value++;
    }
}

QVector<QPoint> Bot::getPath(QPoint start, QPoint finish, QVector<QVector<int>> matrix)
{
    if (abs((start - finish).manhattanLength()) == 1)
    {
        return {finish};
    }

    QVector<QPoint> path;
    path.push_back(finish);

    QPoint left  = directions[Qt::Key_A];
    QPoint right = directions[Qt::Key_D];
    QPoint up    = directions[Qt::Key_W];
    QPoint down  = directions[Qt::Key_S];

    QVector<QPoint> dirs = {left, right, up, down};


    while (true)
    {
        int counter = 0;

        for (int i = 0; i < dirs.size(); i++)
        {
            QPoint nextPoint = path.back() + dirs[i];
            QPoint mappedNextPoint = mapToSector(nextPoint);

            if (!isBelongsToCurrentSector(nextPoint))
            {
                counter++;
                continue;
            }

            if (mapPosition.sector->cell(mappedNextPoint).isWall())
            {
                counter++;
                continue;
            }

            QPoint mappedPathBack = mapToSector(path.back());

            int currentValue = matrix[mappedPathBack.y()][mappedPathBack.x()];
            int nextValue = matrix[mappedNextPoint.y()][mappedNextPoint.x()];

            if (nextPoint == start)
            {
                return path;
            }

            if (currentValue - nextValue == 1)
            {
                path.push_back(nextPoint);
            }
        }
    }
}

void Bot::slotFindCorrectMoveDir()
{
    if (!haveMovementPermission())
    {
        return;
    }

    QPoint left  = directions[Qt::Key_A];
    QPoint right = directions[Qt::Key_D];
    QPoint up    = directions[Qt::Key_W];
    QPoint down  = directions[Qt::Key_S];

    QVector<QPoint> dirs = {left, right, up, down};

    if (state == DO_NOTHING)
    {
        QVector<QPoint> validDirs;

        for (int i = 0; i < dirs.size(); i++)
        {
            QPoint nextPos = position() + dirs[i];

            if (!insideScene(nextPos))
            {
                continue;
            }

            Sector* next = findNextSector(nextPos);
            QPoint sectorPos = mapToSector(nextPos);
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

        QPoint botPosition = position();
        QPoint targetPosition = target->position();

        QVector<QVector<int>> digitMatrix = generateFilledDigitMatrix(botPosition, targetPosition);
        QVector<QPoint> path = getPath(botPosition, targetPosition, digitMatrix);

        if (!path.empty())
        {
            move(path.back());
        }
        else
        {
            qDebug() << "Weird... Path is empty";
        }
    }
}
