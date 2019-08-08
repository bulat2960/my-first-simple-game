#include "buttonspanel.h"

ButtonsPanel::ButtonsPanel(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start");
    pauseLabel = new QLabel("Game paused. To continue press ESC");
    exitButton = new QPushButton("Exit");

    buttonLayout = new QVBoxLayout(this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(exitButton);

    startButton->setMinimumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    pauseLabel->setMinimumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    exitButton->setMinimumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());

    startButton->setMaximumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    pauseLabel->setMaximumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    exitButton->setMaximumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());

    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalStart);
    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::slotReplaceButton);

    connect(exitButton, &QPushButton::clicked, this, &ButtonsPanel::signalExit);

    pauseLabel->setAlignment(Qt::AlignCenter);
    pauseLabel->setStyleSheet("QLabel { background-color: blue; color: white }");
}

void ButtonsPanel::slotReplaceButton()
{
    buttonLayout->replaceWidget(startButton, pauseLabel);
    startButton->hide();
    hide();
}

void ButtonsPanel::slotResume()
{
    emit signalResume();
    hide();
}

void ButtonsPanel::slotPause()
{
    emit signalPause();
}
