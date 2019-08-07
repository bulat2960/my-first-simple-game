#include "buttonspanel.h"

ButtonsPanel::ButtonsPanel(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start");
    resumeButton = new QPushButton("Resume");
    pauseButton = new QPushButton("Pause");
    exitButton = new QPushButton("Exit");

    buttonLayout = new QVBoxLayout(this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(exitButton);

    startButton->setMinimumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    resumeButton->setMinimumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    pauseButton->setMinimumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    exitButton->setMinimumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());

    startButton->setMaximumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    resumeButton->setMaximumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    pauseButton->setMaximumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());
    exitButton->setMaximumHeight(MENU_PANEL_HEIGHT / buttonLayout->count());

    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalStart);
    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::slotReplaceButton);

    connect(resumeButton, &QPushButton::clicked, this, &ButtonsPanel::slotResume);
    connect(pauseButton, &QPushButton::clicked, this, &ButtonsPanel::slotPause);

    connect(exitButton, &QPushButton::clicked, this, &ButtonsPanel::signalExit);

    pauseButton->setEnabled(false);
}

void ButtonsPanel::slotReplaceButton()
{
    buttonLayout->replaceWidget(startButton, resumeButton);
    resumeButton->setEnabled(false);
    pauseButton->setEnabled(true);
}

void ButtonsPanel::slotResume()
{
    resumeButton->setEnabled(false);
    pauseButton->setEnabled(true);
    emit signalResume();
}

void ButtonsPanel::slotPause()
{
    pauseButton->setEnabled(false);
    resumeButton->setEnabled(true);
    emit signalPause();
}
