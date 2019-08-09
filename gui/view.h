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
    Scene* scene;
public:
    View(Scene* scene);
    Scene* getScene() const;
public slots:
    bool eventFilter(QObject* object, QEvent* event) override;

};

#endif // VIEW_H
