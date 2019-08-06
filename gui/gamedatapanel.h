#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include <QPushButton>

class GameDataPanel : public QWidget
{
    Q_OBJECT
public:
    explicit GameDataPanel(QWidget *parent = nullptr);
public slots:
    void paintEvent(QPaintEvent* event) override;
};

#endif // GAMEDATA_H
