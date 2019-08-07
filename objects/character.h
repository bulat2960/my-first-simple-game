#ifndef CHARACTER_H
#define CHARACTER_H

#include <QKeyEvent>
#include <QMap>
#include <QGraphicsScene>

#include "object.h"
#include "maze/sector.h"

class Character : public Object
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
protected:
    struct GameSettings
    {
        int speed;
        int damage;
        int hitpoints;

        bool alive;
        QTimer* respawnTimer;
    };
    GameSettings gameSettings;

    struct Animations
    {
        QPropertyAnimation* moveAnim;
    };
    Animations animations;

    QMap<int, QPoint> directions;
protected:
    void move(QPoint nextPos);

    void setMovementPermission(bool value);
    bool haveMovementPermission() const;
public:
    Character(Sector* sector);

    virtual QPainterPath shape() const override;

    void startMoveAnimation(QPoint startPos, QPoint endPos);
    bool moveAnimStopped() const;

    Sector* findNextSector(QPoint nextPos);
    bool insideScene(QPoint nextPos);

    bool alive() const;
    void kill();
    void respawn();

    void setStartPosition() override;

    void start() override;
    void resume() override;
    void pause() override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private slots:
    virtual void slotFindCorrectMoveDir() = 0;
signals:
    void signalFindPortal();
    void signalFindCharacter();
};

#endif // CHARACTER_H
