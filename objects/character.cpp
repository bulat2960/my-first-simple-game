#include "character.h"

Character::Character(Sector* sector, QColor color) : Object(sector, color)
{
    speed = 300;
    damage = 1;
    hitpoints = 10;

    respawnTimer = new QTimer(this);
    respawnTimer->setSingleShot(true);
    respawnTimer->setInterval(1000 + qrand() % 1000);
    connect(respawnTimer, &QTimer::timeout, this, &Character::respawn);

    moveAnim = new QPropertyAnimation(this, "pos");
    moveAnim->setDuration(speed);

    directions.insert(Qt::Key_A, QPoint(-1, 0));
    directions.insert(Qt::Key_W, QPoint(0, -1));
    directions.insert(Qt::Key_D, QPoint(1, 0));
    directions.insert(Qt::Key_S, QPoint(0, 1));

    connect(this, &Character::xChanged, this, &Character::signalCheckCollisions);
    connect(this, &Character::yChanged, this, &Character::signalCheckCollisions);

    connect(moveAnim, &QPropertyAnimation::finished, this, &Character::signalCheckPortal);
}

void Character::startMoveAnimation(QPoint startPos, QPoint endPos)
{
    moveAnim->setStartValue(graphicalPosition(startPos));
    moveAnim->setEndValue(graphicalPosition(endPos));
    moveAnim->start();
}

QPainterPath Character::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillPath(shape(), color());
}

Sector* Character::findNextSector(QPoint nextPos)
{
    QPoint nextScenePos = graphicalPosition(nextPos);
    QRect nextRect = QRect(nextScenePos, nextScenePos + boundingRect().bottomRight().toPoint());
    return dynamic_cast<Sector*>(scene()->items(nextRect).last());
}

bool Character::insideScene(QPoint nextPos)
{
    QRect sceneRect = scene()->sceneRect().toRect();
    QPoint scenePos = graphicalPosition(nextPos);
    bool insideHorizontal = (scenePos.x() >= 0) && (scenePos.x() < sceneRect.width());
    bool insideVertical = (scenePos.y() >= 0) && (scenePos.y() < sceneRect.height());
    return (insideVertical && insideHorizontal);
}

void Character::move(QPoint nextPos)
{
    Sector* nextSector = findNextSector(nextPos);

    startMoveAnimation(position(), nextPos);
    setPosition(nextPos);
    setSector(nextSector);
}

bool Character::alive() const
{
    return gameSettings.alive;
}

void Character::kill()
{
    isAlive = false;
    respawnTimer->start();
    if (moveAnim->state() == QPropertyAnimation::Running)
    {
        moveAnim->pause();
    }
    hide();
}

void Character::respawn()
{
    isAlive = true;
    respawnTimer->stop();
    if (moveAnim->state() == QPropertyAnimation::Paused)
    {
        moveAnim->resume();
    }
    show();
}
