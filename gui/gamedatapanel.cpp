#include "gamedatapanel.h"

GameDataPanel::GameDataPanel(QWidget *parent) : QWidget(parent)
{
    anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(200);

    textEdit = new QTextEdit(this);
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

void GameDataPanel::slotReceiveDataFromGame(QByteArray data)
{
    textEdit->setGeometry(0, 0, width(), height()); // Transfer to other place
    textEdit->clear();
    this->receivedData = data;
    QList<QByteArray> keys = data.split('|');
    for (int i = 0; i < keys.size(); i++)
    {
        textEdit->append(keys[i]);
    }
    repaint();
}

void GameDataPanel::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
}
