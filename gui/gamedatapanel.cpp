#include "gamedatapanel.h"

GameDataPanel::GameDataPanel(QWidget *parent) : QWidget(parent)
{
    anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(500);
    isVisible = false;
}

void GameDataPanel::animShow()
{
    if (anim->state() != QPropertyAnimation::Stopped)
    {
        anim->stop();
    }
    anim->setStartValue(geometry());
    anim->setEndValue(QRect(0, parentWidget()->height() - GAME_DATA_PANEL_HEIGHT, parentWidget()->width(), GAME_DATA_PANEL_HEIGHT));
    anim->start();
}

void GameDataPanel::animHide()
{
    if (anim->state() != QPropertyAnimation::Stopped)
    {
        anim->stop();
    }
    anim->setStartValue(geometry());
    anim->setEndValue(QRect(0, parentWidget()->height(), parentWidget()->width(), 0));
    anim->start();
}

void GameDataPanel::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::red);
}
