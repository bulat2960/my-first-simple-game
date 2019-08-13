#include "character.h"

Character::Character(Sector* sector) : Object(sector)
{
    gameSettings.speed = 300;
    gameSettings.damage = 5 + qrand() % 5;
    gameSettings.hitpoints = 50 + qrand() % 50;
    gameSettings.alive = true;
    gameSettings.respawnTimer = new QTimeLine(2000, this);
    connect(gameSettings.respawnTimer, &QTimeLine::finished, this, &Character::respawn);

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

    setMovementPermission(false);
}

int Character::hitpoints() const
{
    return gameSettings.hitpoints;
}

void Character::setHitpoints(int hitpoints)
{
    gameSettings.hitpoints = hitpoints;
}

int Character::damage() const
{
    return gameSettings.damage;
}

void Character::setDamage(int damage)
{
    gameSettings.damage = damage;
}

void Character::startMoveAnimation(QPoint startPos, QPoint endPos)
{
    animations.moveAnim->setStartValue(graphicalPosition(startPos));
    animations.moveAnim->setEndValue(graphicalPosition(endPos));
    animations.moveAnim->start();
}

void Character::resumeMoveAnimation()
{
    if (animations.moveAnim->state() == QPropertyAnimation::Paused)
    {
        animations.moveAnim->resume();
    }
}

void Character::pauseMoveAnimation()
{
    if (animations.moveAnim->state() != QPropertyAnimation::Stopped)
    {
        animations.moveAnim->pause();
    }
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

QRectF Character::boundingRect() const
{
    return QRectF(0, 0, drawingSettings.image.width(), drawingSettings.image.height());
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

    startMoveAnimation(pos().toPoint() / SIZE, nextPos);
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
    setMovementPermission(false);
    gameSettings.alive = false;
    if (gameSettings.hitpoints > 0)
    {
        gameSettings.respawnTimer->start();
    }
    pauseMoveAnimation();
    hide();
}

void Character::respawn()
{
    setMovementPermission(true);
    gameSettings.alive = true;
    gameSettings.respawnTimer->stop();
    resumeMoveAnimation();
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
    resumeMoveAnimation();
    if (gameSettings.respawnTimer->state() == QTimeLine::Paused)
    {
        gameSettings.respawnTimer->setPaused(false);
    }
}

void Character::pause()
{
    setMovementPermission(false);
    pauseMoveAnimation();
    if (gameSettings.respawnTimer->state() == QTimeLine::Running)
    {
        gameSettings.respawnTimer->setPaused(true);
    }
}

QByteArray Character::gameData() const
{
    QByteArray s;
    s += "Speed: " + QByteArray::number(gameSettings.speed) + "|";
    s += "Damage: " + QByteArray::number(gameSettings.damage) + "|";
    s += "Hitpoints: " + QByteArray::number(gameSettings.hitpoints) + "|";
    s += "Is alive: " + (gameSettings.alive ? QByteArray("true") : QByteArray("false")) + "|";

    if (gameSettings.alive == false)
    {
        int duration = gameSettings.respawnTimer->duration();
        int currentTime = gameSettings.respawnTimer->currentTime();
        double secondFormat = (duration - currentTime) / 1000.0;
        s += "Respawn timer: " + QByteArray::number(secondFormat, 'f', 1);
    }
    return s;
}
