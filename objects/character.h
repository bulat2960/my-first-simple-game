#ifndef CHARACTER_H
#define CHARACTER_H

#include <QKeyEvent>
#include <QMap>
#include <QGraphicsScene>
#include <QTimeLine>

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
        QTimeLine* respawnTimer;
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

    void startMoveAnimation(QPoint startPos, QPoint endPos);
    void resumeMoveAnimation();
    void pauseMoveAnimation();
    bool moveAnimStopped() const;

    int hitpoints() const;
    void setHitpoints(int hitpoints);

    int damage() const;
    void setDamage(int damage);

    Sector* findNextSector(QPoint nextPos);
    bool insideScene(QPoint nextPos);

    bool alive() const;
    void kill();
    void respawn();

    void setStartPosition() override;

    void start() override;
    void resume() override;
    void pause() override;

    QByteArray gameData() const;

    virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private slots:
    virtual void slotFindCorrectMoveDir() = 0;
signals:
    void signalFindPortal();
    void signalFindCharacter();
};

#endif // CHARACTER_H
