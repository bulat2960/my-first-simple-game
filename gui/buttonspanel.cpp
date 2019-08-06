#include "buttonspanel.h"

ButtonsPanel::ButtonsPanel(QWidget *parent) : QWidget(parent)
{
    startButton = new QPushButton("Start");
    stopButton = new QPushButton("Stop");
    exitButton = new QPushButton("Exit");

    buttonLayout = new QHBoxLayout(this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(exitButton);

    connect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalStart);
    connect(stopButton, &QPushButton::clicked, this, &ButtonsPanel::signalStop);
    connect(exitButton, &QPushButton::clicked, this, &ButtonsPanel::signalExit);
}

void ButtonsPanel::changeStartButtonName()
{
    startButton->setText("Resume");
    disconnect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalStart);
    disconnect(startButton, &QPushButton::clicked, this, &ButtonsPanel::signalResume);
}
