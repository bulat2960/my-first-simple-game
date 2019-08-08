#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include <QHBoxLayout>

#include "globaloptions.h"

class GameDataPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect pos READ geometry WRITE setGeometry)
private:
    QPropertyAnimation* anim;
    bool visible;

    QLabel* label1;
    QLabel* label2;
    QHBoxLayout* labelLayout;
public:
    explicit GameDataPanel(QWidget *parent = nullptr);

    void setElementsGeometries();

    void animShow();
    void animHide();
    bool isVisible() const;
public slots:
    void slotReceiveDataFromGame(QByteArray data);
    void paintEvent(QPaintEvent* event) override;
};

#endif // GAMEDATA_H
