#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QScrollBar>
#include <QKeyEvent>

#include "scene.h"

class View : public QGraphicsView
{
    Q_OBJECT
private:
    QPropertyAnimation* anim;

    Scene* scene;
public:
    View(Scene* scene);
    Scene* getScene() const;

    void animUp();
    void animDown();
public slots:
    bool eventFilter(QObject* object, QEvent* event) override;

};

#endif // VIEW_H
