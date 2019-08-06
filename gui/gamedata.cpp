#include "gamedata.h"

GameData::GameData(QWidget *parent) : QWidget(parent)
{

}

void GameData::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::red);
}
