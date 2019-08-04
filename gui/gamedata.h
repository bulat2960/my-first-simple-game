#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include <QPushButton>

class GameData : public QWidget
{
    Q_OBJECT
public:
    explicit GameData(QWidget *parent = nullptr);
public slots:
    void paintEvent(QPaintEvent* event) override;
};

#endif // GAMEDATA_H
