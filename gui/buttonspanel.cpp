#include "buttonspanel.h"

ButtonsPanel::ButtonsPanel(QWidget *parent) : QWidget(parent)
{
    QPushButton* startButton = new QPushButton("Start");
    QPushButton* stopButton = new QPushButton("Stop");
    QPushButton* exitButton = new QPushButton("Exit");

    buttonLayout = new QHBoxLayout(this);

    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(exitButton);

    connect(exitButton, &QPushButton::clicked, this, &ButtonsPanel::signalExit);
}
