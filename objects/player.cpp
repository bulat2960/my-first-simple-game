#include "player.h"

Player::Player(Sector* sector, QColor color) : Character(sector, color)
{
    hitpoints = 50;
    speed = 100;

    // Установка начальной позиции для анимации в точку (0, 0)
    setPos(0, 0);

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
        if (usedKeys[dir] == true)
        {
            move(dir);
        }
    }
}

Sector* Player::findNextSector(int key)
{
    QPoint next = (position + directions[key]) * SIZE;
    Sector* nextSector = dynamic_cast<Sector*>(scene()->items(next)[0]);
    return nextSector;
}

void Player::move(int dir)
{
    bool shiftKeyPressed = (usedKeys[Qt::Key_Shift] == true);
    anim->setDuration(shiftKeyPressed ? speed / 3 : speed);

    if (anim->state() != QPropertyAnimation::Stopped)
    {
        return;
    }

    QPoint nextPos = position + directions[dir];

    // Проверка на выход за границы сцены
    QRect sceneRect = scene()->sceneRect().toRect();
    QPoint scenePos = nextPos * SIZE;
    bool insideHorizontal = (scenePos.x() >= 0) && (scenePos.x() < sceneRect.width());
    bool insideVertical = (scenePos.y() >= 0) && (scenePos.y() < sceneRect.height());
    bool inside = (insideVertical && insideHorizontal);
    if (!inside)
    {
        return;
    }

    // Поиск следующего сектора, перевод из мировых координат в секторные
    Sector* next = findNextSector(dir);
    QPoint sectorPos = QPoint(nextPos.x() % next->width(), nextPos.y() % next->height());

    // Проверка на возможность перемещения, перемешение с анимацией, смена сектора
    if (next->cell(sectorPos.x(), sectorPos.y()).isRoad())
    {
        startAnimation(position, nextPos); // Запускаем анимацию
        position = nextPos;
        sector = next; // Изменяем местоположение игрока
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
