﻿#ifndef PLAYER_H
#define PLAYER_H

#include <QKeyEvent>
#include <QMap>
#include <QTimer>

#include "character.h"

class Player : public Character
{
private:
    QMap<int, bool> usedKeys;
public:
    Player(Sector* sector);
private slots:
    void slotFindCorrectMoveDir() override;
public slots:
    virtual bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // PLAYER_H
