#include "buttonspanel.h"

ButtonsPanel::ButtonsPanel(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start");
    resumeButton = new QPushButton("Resume");
    pauseButton = new QPushButton("Pause");
    exitButton = new QPushButton("Exit");

    buttonLayout = new QHBoxLayout(this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(exitButton);

    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalStart);
    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::slotReplaceButton);
    connect(resumeButton, &QPushButton::clicked, this, &ButtonsPanel::signalResume);
    connect(pauseButton, &QPushButton::clicked, this, &ButtonsPanel::signalPause);
    connect(exitButton, &QPushButton::clicked, this, &ButtonsPanel::signalExit);
}

void ButtonsPanel::slotReplaceButton()
{
    buttonLayout->replaceWidget(startButton, resumeButton);
}
