#include "gamedatapanel.h"

GameDataPanel::GameDataPanel(QWidget *parent) : QWidget(parent)
{
    anim = new QPropertyAnimation(this, "pos");
    isVisible = false;

    setGeometry(0, 0, 0, 0);
}

void GameDataPanel::startAnimation()
{
    QRect rect1 = QRect(0, parentWidget()->height(), parentWidget()->width(), 0);
    QRect rect2 = QRect(0, parentWidget()->height() - GAME_DATA_PANEL_HEIGHT, parentWidget()->width(), GAME_DATA_PANEL_HEIGHT);

    if (anim->state() == QPropertyAnimation::Running)
    {
        return;
    }

    if (!isVisible)
    {
        anim->setStartValue(rect1);
        anim->setEndValue(rect2);
        isVisible = true;
     }
    else
    {
        anim->setStartValue(rect2);
        anim->setEndValue(rect1);
        isVisible = false;
    }
    anim->start();
}

void GameDataPanel::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::red);
}
