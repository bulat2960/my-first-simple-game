#ifndef BUTTONSPANEL_H
#define BUTTONSPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

#include "globaloptions.h"

class ButtonsPanel : public QWidget
{
    Q_OBJECT
private:
    QPushButton* startButton;
    QLabel* pauseLabel;
    QPushButton* exitButton;

    QVBoxLayout* buttonLayout;
public:
    ButtonsPanel(QWidget* parent = nullptr);
public slots:
    void slotReplaceButton();
    void slotResume();
    void slotPause();
signals:
    void signalExit();
    void signalStart();
    void signalResume();
    void signalPause();
    void signalStop();
};

#endif // BUTTONSPANEL_H
