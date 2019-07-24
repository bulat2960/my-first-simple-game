﻿#include "player.h"

Player::Player(Sector* sector, QColor color) : Character(sector, color)
{
    hitpoints = 50;
    speed = 250;
    anim->setDuration(speed);

    // Установка начальной позиции для анимации в точку (0, 0)
    setPos(0, 0);
    position = QPoint(0, 0);

    // Установка фильтра событий
    installEventFilter(this);

    // Клавиши, которыми управляет игрокА
    usedKeys.insert(Qt::Key_W, false);
    usedKeys.insert(Qt::Key_A, false);
    usedKeys.insert(Qt::Key_S, false);
    usedKeys.insert(Qt::Key_D, false);
    usedKeys.insert(Qt::Key_Shift, false);

    QTimer* timer = new QTimer(this);
    timer->setInterval(1);
    connect(timer, &QTimer::timeout, this, &Player::processKeys);
    timer->start();
}

void Player::processKeys()
{
    QList<int> dirs = directions.keys();
    for (int i = 0; i < dirs.size(); i++)
    {
        int dir = dirs[i];
        bool usedKey = usedKeys[dir];
        if (usedKey && anim->state() == QPropertyAnimation::Stopped)
        {
            move(dir);
        }
    }
}

void Player::move(int dir)
{
    bool shiftKeyPressed = (usedKeys[Qt::Key_Shift] == true);
    anim->setDuration(shiftKeyPressed ? 1 : speed);

    QPoint nextPos = position + directions[dir];

    // Проверка на выход за границы сцены
    if (!isInsideScene(nextPos))
    {
        return;
    }

    Sector* next = findNextSector(nextPos);
    QPoint sectorPos = mapToSector(nextPos, next);

    if (next->isRoadCell(sectorPos))
    {
        startAnimation(position, nextPos);
        position = nextPos;
        sector = next;
        emit signalCheckCollisions();
    }
}

bool Player::eventFilter(QObject* obj, QEvent* event)
{
    QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
    int key = keyEvent->key();

    if (event->type() == QEvent::KeyPress)
    {
        usedKeys[key] = true;
        return true;
    }
    if (event->type() == QEvent::KeyRelease)
    {
        if (keyEvent->isAutoRepeat() == false)
        {
            usedKeys[key] = false;
        }
        return true;
    }
    return QObject::eventFilter(obj, event);
}
