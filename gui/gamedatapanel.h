#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QPropertyAnimation>

#include "globaloptions.h"

class GameDataPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect pos READ geometry WRITE setGeometry)
private:
    QPropertyAnimation* anim;
public:
    explicit GameDataPanel(QWidget *parent = nullptr);

    void animShow();
    void animHide();
public slots:
    void paintEvent(QPaintEvent* event) override;
};

#endif // GAMEDATA_H
