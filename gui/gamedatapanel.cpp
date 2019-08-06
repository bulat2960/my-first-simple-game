#include "gamedatapanel.h"

GameDataPanel::GameDataPanel(QWidget *parent) : QWidget(parent)
{

}

void GameDataPanel::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::red);
}
