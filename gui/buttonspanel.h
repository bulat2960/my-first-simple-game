#ifndef BUTTONSPANEL_H
#define BUTTONSPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ButtonsPanel : public QWidget
{
    Q_OBJECT
private:
    QPushButton* startButton;
    QPushButton* resumeButton;
    QPushButton* pauseButton;
    QPushButton* exitButton;

    QHBoxLayout* buttonLayout;
public:
    ButtonsPanel(QWidget* parent = nullptr);
private slots:
    void slotReplaceButton();
signals:
    void signalExit();
    void signalStart();
    void signalResume();
    void signalPause();
    void signalStop();
};

#endif // BUTTONSPANEL_H
