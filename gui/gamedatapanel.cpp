#include "gamedatapanel.h"

GameDataPanel::GameDataPanel(QWidget *parent) : QWidget(parent)
{
    anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(200);

    visible = false;

    label1 = new QLabel;
    label1->setStyleSheet("QLabel { color: white; background-color: green }");

    label2 = new QLabel;
    label2->setStyleSheet("QLabel { color: white; background-color: red }");

    labelLayout = new QHBoxLayout(this);
    labelLayout->addWidget(label1);
    labelLayout->addWidget(label2);
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
    visible = true;
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
    visible = false;
}

void GameDataPanel::slotReceiveDataFromGame(QByteArray data)
{
    label1->clear();
    QList<QByteArray> keys = data.split('|');

    QByteArray result;
    for (int i = 0; i < keys.size(); i++)
    {
        result.append(keys[i]);
        result += " ";
    }
    label1->setText(result);
    repaint();
}

bool GameDataPanel::isVisible() const
{
    return visible;
}

void GameDataPanel::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), GAME_DATA_PANEL_HEIGHT, Qt::blue);
}
