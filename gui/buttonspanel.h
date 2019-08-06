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
    QPushButton* stopButton;
    QPushButton* exitButton;

    QHBoxLayout* buttonLayout;
public:
    ButtonsPanel(QWidget* parent = nullptr);
public slots:
    void changeStartButtonName();
signals:
    void signalExit();
    void signalStart();
    void signalResume();
    void signalPause();
    void signalStop();
};

#endif // BUTTONSPANEL_H
