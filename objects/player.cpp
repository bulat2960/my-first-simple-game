#include "player.h"

Player::Player(Sector* sector, QColor color) : Character(sector, color)
{
    hitpoints = 50;
    speed = 250;
    anim->setDuration(speed);

    // Установка начальной позиции для анимации в стартовую точку
    setPos(graphicalPosition(position()));

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
    connect(timer, &QTimer::timeout, this, &Player::slotProcessKeys);
    timer->start();
}

void Player::slotProcessKeys()
{
    bool shiftKeyPressed = usedKeys[Qt::Key_Shift];
    anim->setDuration(shiftKeyPressed ? 1 : speed);

    QList<int> dirs = directions.keys();
    for (int i = 0; i < dirs.size(); i++)
    {
        int dir = dirs[i];
        bool usedKey = usedKeys[dir];
        if (usedKey && animStopped() && alive())
        {
            move(dir);
        }
    }
}

void Player::move(int dir)
{
    QPoint playerNextPos = position() + directions[dir];

    // Проверка на выход за границы сцены
    if (!insideScene(playerNextPos))
    {
        return;
    }

    Sector* nextSector = findNextSector(playerNextPos);
    QPoint nextSectorPos = mapToSector(playerNextPos, nextSector);

    if (nextSector->isRoad(nextSectorPos))
    {
        startAnimation(position(), playerNextPos);
        setPosition(playerNextPos);
        setSector(nextSector);
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
