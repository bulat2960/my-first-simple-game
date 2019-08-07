#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QTextEdit>
#include <QLabel>

#include "globaloptions.h"

class GameDataPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect pos READ geometry WRITE setGeometry)
private:
    QPropertyAnimation* anim;

    QByteArray receivedData;
    QTextEdit* textEdit;
public:
    explicit GameDataPanel(QWidget *parent = nullptr);

    void animShow();
    void animHide();
public slots:
    void slotReceiveDataFromGame(QByteArray data);
    void paintEvent(QPaintEvent* event) override;
};

#endif // GAMEDATA_H
