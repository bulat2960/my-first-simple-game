#include "player.h"

Player::Player(Sector* sector) : Character(sector)
{
    gameSettings.hitpoints = 300;

    installEventFilter(this);

    usedKeys.insert(Qt::Key_W, false);
    usedKeys.insert(Qt::Key_A, false);
    usedKeys.insert(Qt::Key_S, false);
    usedKeys.insert(Qt::Key_D, false);

    QTimer* timer = new QTimer(this);
    timer->setInterval(1);
    connect(timer, &QTimer::timeout, this, &Player::slotFindCorrectMoveDir);
    connect(timer, &QTimer::timeout, this, &Player::signalSendData);
    timer->start();

    setMovementPermission(false);
}

void Player::clearUsedKeys()
{
    foreach (int key, usedKeys.keys())
    {
        usedKeys[key] = false;
    }
}

void Player::pause()
{
    Character::pause();
    clearUsedKeys();
}

void Player::slotFindCorrectMoveDir()
{
    if (!moveAnimStopped() || !haveMovementPermission())
    {
        return;
    }

    QVector<QPoint> possibleDirs;

    QList<int> dirKeys = directions.keys();
    for (int i = 0; i < dirKeys.size(); i++)
    {
        int key = dirKeys[i];
        bool usedKey = usedKeys[key];
        QPoint nextPos = position() + directions[key];

        if (!insideScene(nextPos))
        {
            continue;
        }

        Sector* nextSector = findNextSector(nextPos);
        QPoint nextSectorPos = mapToSector(nextPos, nextSector);
        if (usedKey && nextSector->isRoad(nextSectorPos))
        {
            possibleDirs.push_back(nextPos);
        }
    }

    if (possibleDirs.size() > 0)
    {
        QPoint nextPos = possibleDirs[qrand() % possibleDirs.size()];
        move(nextPos);
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
