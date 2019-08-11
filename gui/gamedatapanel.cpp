#include "gamedatapanel.h"

GameDataPanel::GameDataPanel(QWidget *parent) : QWidget(parent)
{
    anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(200);

    visible = false;

    playerLabel = new QLabel;
    playerLabel->setStyleSheet("QLabel { color: white; background-color: green }");

    botLabel = new QLabel;
    botLabel->setStyleSheet("QLabel { color: white; background-color: red }");

    labelLayout = new QHBoxLayout(this);
    labelLayout->addWidget(playerLabel);
    labelLayout->addWidget(botLabel);
}

void GameDataPanel::animUp()
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

void GameDataPanel::animDown()
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

void GameDataPanel::slotReceiveDataFromGame(QByteArray playerData, QByteArray botData)
{
    playerLabel->clear();
    botLabel->clear();

    QList<QByteArray> playerValues = playerData.split('|');
    QList<QByteArray> botValues = botData.split('|');

    QByteArray playerResult;
    for (int i = 0; i < playerValues.size(); i++)
    {
        playerResult.append(playerValues[i]);
        playerResult += "    ";
    }
    playerLabel->setText(playerResult);

    QByteArray botResult;
    for (int i = 0; i < botValues.size(); i++)
    {
        botResult.append(botValues[i]);
        botResult += "     ";
    }
    botLabel->setText(botResult);

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
