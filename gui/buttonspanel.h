#ifndef BUTTONSPANEL_H
#define BUTTONSPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class ButtonsPanel : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* buttonLayout;
public:
    ButtonsPanel(QWidget* parent = nullptr);
signals:
    void signalExit();
    void signalStart();
    void signalResume();
    void signalPause();
    void signalStop();
};

#endif // BUTTONSPANEL_H
