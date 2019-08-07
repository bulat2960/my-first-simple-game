#include "buttonspanel.h"

ButtonsPanel::ButtonsPanel(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    stopButton = new QPushButton("Stop");
    exitButton = new QPushButton("Exit");

    buttonLayout = new QHBoxLayout(this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(exitButton);

    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalStart);
    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::slotChangeStartButtonName);
    connect(pauseButton, &QPushButton::clicked, this, &ButtonsPanel::signalPause);
    connect(stopButton, &QPushButton::clicked, this, &ButtonsPanel::signalStop);
    connect(exitButton, &QPushButton::clicked, this, &ButtonsPanel::signalExit);
}

void ButtonsPanel::slotChangeStartButtonName()
{
    startButton->setText("Resume");
    disconnect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalStart);
    disconnect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalResume);
}
