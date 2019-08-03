#include "character.h"

Character::Character(Sector* sector) : Object(sector)
{
    gameSettings.speed = 50;
    gameSettings.damage = 1;
    gameSettings.hitpoints = 10;

    gameSettings.respawnTimer = new QTimer(this);
    gameSettings.respawnTimer->setSingleShot(true);
    gameSettings.respawnTimer->setInterval(1000 + qrand() % 1000);
    connect(gameSettings.respawnTimer, &QTimer::timeout, this, &Character::respawn);

    animations.moveAnim = new QPropertyAnimation(this, "pos");
    animations.moveAnim->setDuration(gameSettings.speed);

    directions.insert(Qt::Key_A, QPoint(-1, 0));
    directions.insert(Qt::Key_W, QPoint(0, -1));
    directions.insert(Qt::Key_D, QPoint(1, 0));
    directions.insert(Qt::Key_S, QPoint(0, 1));

    drawingSettings.image.load(":/images/images/character.png");

    connect(this, &Character::xChanged, this, &Character::signalCheckCollisions);
    connect(this, &Character::yChanged, this, &Character::signalCheckCollisions);

    connect(animations.moveAnim, &QPropertyAnimation::finished, this, &Character::signalCheckPortal);
}

void Character::startMoveAnimation(QPoint startPos, QPoint endPos)
{
    animations.moveAnim->setStartValue(graphicalPosition(startPos));
    animations.moveAnim->setEndValue(graphicalPosition(endPos));
    animations.moveAnim->start();
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

    painter->drawImage(boundingRect(), drawingSettings.image);
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
    gameSettings.alive = false;
    gameSettings.respawnTimer->start();
    if (animations.moveAnim->state() == QPropertyAnimation::Running)
    {
        animations.moveAnim->pause();
    }
    hide();
}

void Character::respawn()
{
    gameSettings.alive = true;
    gameSettings.respawnTimer->stop();
    if (animations.moveAnim->state() == QPropertyAnimation::Paused)
    {
        animations.moveAnim->resume();
    }
    show();
}
