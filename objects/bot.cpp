﻿#include "bot.h"

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
            QPoint sectorPos = mapToSector(nextPos, next);
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

        QPoint startPos = position();
        QPoint mappedStartPos = mapToSector(startPos, sector());
        QPoint finishPos = target->position();
        QPoint mappedFinishPos = mapToSector(finishPos, sector());

        // To fix bug with characters who stay very close
        if ((startPos - finishPos).manhattanLength() == 1 || (startPos - finishPos).manhattanLength() == -1)
        {
            move(finishPos);
            return;
        }

        int currentValue = 2;
        QVector<QPoint> points = {startPos};

        while (true)
        {
            QVector<QPoint> temp;

            for (int i = 0; i < points.size(); i++)
            {
                bool flag = false;

                QPoint currentPoint = points[i];

                for (int j = 0; j < dirs.size(); j++)
                {
                    QPoint nextPoint = currentPoint + (dirs[j] - position());
                    QPoint mappedNextPoint = mapToSector(nextPoint, sector());

                    int sectorTopBorder = mapPosition.sector->position().y() * mapPosition.sector->height();
                    int sectorBottomBorder = sectorTopBorder + mapPosition.sector->height();
                    int sectorLeftBorder = mapPosition.sector->position().x() * mapPosition.sector->width();
                    int sectorRightBorder = sectorLeftBorder + mapPosition.sector->width();

                    if (nextPoint.x() < sectorLeftBorder || nextPoint.y() < sectorTopBorder
                        || nextPoint.x() >= sectorRightBorder || nextPoint.y() >= sectorBottomBorder)
                    {
                        continue;
                    }

                    if (mapPosition.sector->cell(mappedNextPoint).isRoad()
                            && digitMatrix[mappedNextPoint.y()][mappedNextPoint.x()] == 1
                            && nextPoint != startPos)
                    {
                        digitMatrix[mappedNextPoint.y()][mappedNextPoint.x()] = currentValue;
                        temp.push_back(nextPoint);
                    }


                    if (nextPoint == finishPos)
                    {
                        flag = true;
                        break;
                    }
                }

                if (flag == true)
                {
                    break;
                }
            }

            if (temp.contains(finishPos))
            {
                break;
            }

            points = temp;
            currentValue++;
        }

        /*qDebug() << "--------------------------";
        for (int i = 0; i < digitMatrix.size(); i++)
        {
            QString s;
            for (int j = 0; j < digitMatrix[i].size(); j++)
            {
                if (QPoint(j, i) == mappedFinishPos)
                {
                    s += "F ";
                }
                else if (QPoint(j, i) == mappedStartPos)
                {
                    s += "S ";
                }
                else
                {
                    s += QString::number(digitMatrix[i][j]) + " ";
                }
            }
            qDebug() << s;
        }
        qDebug() << "--------------------------";*/

        QVector<QPoint> way;

        if (digitMatrix[mappedFinishPos.y()][mappedFinishPos.x()] != 1)
        {
            way.push_back(finishPos);

            while (true)
            {
                for (int i = 0; i < dirs.size(); i++)
                {
                    QPoint currentPoint = way.back();
                    QPoint mappedCurrentPoint = mapToSector(currentPoint, sector());
                    QPoint nextPoint = currentPoint + (position() - dirs[i]);
                    QPoint mappedNextPoint = mapToSector(nextPoint, sector());

                    // Ошибка в mapped!!! Необходимо смотреть ячейки только в текущем секторе
                    // Еще проверить генерацию digitMatrix

                    if (mappedNextPoint.x() < 0 || mappedNextPoint.y() < 0
                        || mappedNextPoint.x() >= mapPosition.sector->width()
                        || mappedNextPoint.y() >= mapPosition.sector->height())
                    {
                        continue;
                    }

                    qDebug() << "--------------------------";
                    for (int i = 0; i < digitMatrix.size(); i++)
                    {
                        QString s;
                        for (int j = 0; j < digitMatrix[i].size(); j++)
                        {
                            if (QPoint(j, i) == mappedFinishPos)
                            {
                                s += "f ";
                            }
                            else if (QPoint(j, i) == mappedStartPos)
                            {
                                s += "s ";
                            }
                            else
                            {
                                s += QString::number(digitMatrix[i][j]) + " ";
                            }
                        }
                        qDebug() << s;
                    }
                    qDebug() << "--------------------------";

                    if (digitMatrix[mappedCurrentPoint.y()][mappedCurrentPoint.x()] ==
                           digitMatrix[mappedNextPoint.y()][mappedNextPoint.x()] + 1
                        && digitMatrix[mappedNextPoint.y()][mappedNextPoint.x()] != 0
                        && mapPosition.sector->cell(mappedNextPoint).isRoad())
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
