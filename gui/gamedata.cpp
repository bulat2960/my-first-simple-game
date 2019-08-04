#include "gamedata.h"

GameData::GameData(QWidget *parent) : QWidget(parent)
{

}

void GameData::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QPen pen(Qt::red);
    painter.setPen(pen);
    painter.drawLine(20, 20, 100, 100);
    painter.drawLine(100, 100, 30, 40);
    painter.drawLine(30, 40, 20, 20);
}
