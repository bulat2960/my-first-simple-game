#ifndef BUTTONSPANEL_H
#define BUTTONSPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSizePolicy>

#include "globaloptions.h"

class ButtonsPanel : public QWidget
{
    Q_OBJECT
private:
    QPushButton* startButton;
    QPushButton* resumeButton;
    QPushButton* pauseButton;
    QPushButton* exitButton;

    QVBoxLayout* buttonLayout;
public:
    ButtonsPanel(QWidget* parent = nullptr);
private slots:
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
