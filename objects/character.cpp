﻿#include "character.h"

Character::Character(Sector* sector) : Object(sector)
{
    gameSettings.speed = 200;
    gameSettings.damage = 1;
    gameSettings.hitpoints = 10;
    gameSettings.alive = true;
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

    connect(this, &Character::xChanged, this, &Character::signalFindCharacter);
    connect(this, &Character::yChanged, this, &Character::signalFindCharacter);

    connect(animations.moveAnim, &QPropertyAnimation::finished, this, &Character::signalFindPortal);

    setStartPosition();
}

void Character::startMoveAnimation(QPoint startPos, QPoint endPos)
{
    animations.moveAnim->setStartValue(graphicalPosition(startPos));
    animations.moveAnim->setEndValue(graphicalPosition(endPos));
    animations.moveAnim->start();
}

bool Character::moveAnimStopped() const
{
    return animations.moveAnim->state() == QPropertyAnimation::Stopped;
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

void Character::setMovementPermission(bool value)
{
    setAcceptTouchEvents(value);
}

bool Character::haveMovementPermission() const
{
    return acceptTouchEvents();
}

bool Character::alive() const
{
    return gameSettings.alive;
}

void Character::kill()
{
    gameSettings.alive = false;
    gameSettings.respawnTimer->start();
    pause();
    hide();
}

void Character::respawn()
{
    gameSettings.alive = true;
    gameSettings.respawnTimer->stop();
    resume();
    show();
}

void Character::setStartPosition()
{
    while (true)
    {
        int x = qrand() % sector()->width();
        int y = qrand() % sector()->height();

        bool atVerticalBorders = (x == 0) || (x == mapPosition.sector->width() - 1);
        bool atHorizontalBorders = (y == 0) || (y == mapPosition.sector->height() - 1);
        bool notAtBorders = !(atVerticalBorders || atHorizontalBorders);
        if (mapPosition.sector->cell(x, y).isRoad() && notAtBorders)
        {
            x += mapPosition.sector->position().x() * mapPosition.sector->width();
            y += mapPosition.sector->position().y() * mapPosition.sector->height();
            setPosition(x, y);
            setGraphicalPosition(x, y);
            break;
        }
    }
}

void Character::start()
{
    setMovementPermission(true);
    slotFindCorrectMoveDir();
}

void Character::resume()
{
    setMovementPermission(true);
    if (animations.moveAnim->state() == QPropertyAnimation::Paused)
    {
        animations.moveAnim->resume();
    }
}

void Character::pause()
{
    setMovementPermission(false);
    if (animations.moveAnim->state() != QPropertyAnimation::Stopped)
    {
        animations.moveAnim->pause();
    }
}

QByteArray Character::gameData() const
{
    QByteArray s;
    s += "Speed: " + QByteArray::number(gameSettings.speed) + "|";
    s += "Damage: " + QByteArray::number(gameSettings.damage) + "|";
    s += "Hitpoints: " + QByteArray::number(gameSettings.hitpoints) + "|";
    s += "Is alive: " + (gameSettings.alive ? QByteArray("true") : QByteArray("false")) + "|";
    s += "Respawn timer: " + (gameSettings.respawnTimer->remainingTime() > 0 ?
                              QByteArray::number(gameSettings.respawnTimer->remainingTime() / 1000.0, 'f', 1) : "0");
    return s;
}
