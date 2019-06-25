#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QMap>
#include <QTimer>

#include "character.h"

class Player : public Character
{
private:
    QMap<int, bool> usedKeys;
private:
    void move(int dir);
public:
    Player(Sector* sector, QColor color);

    Sector* findNextSector(int key);
public slots:
    virtual bool eventFilter(QObject* obj, QEvent* event) override;
    void processKeys();
};

#endif // PLAYER_H
