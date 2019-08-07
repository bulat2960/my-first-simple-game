#ifndef FIXEDOBJECT_H
#define FIXEDOBJECT_H

#include "object.h"

class FixedObject : public Object
{
    Q_OBJECT
    Q_PROPERTY(qreal rot READ rot WRITE setRot)
protected:
    struct Animations
    {
        QPropertyAnimation* rotateAnim;
    };
    Animations animations;
public:
    FixedObject(Sector* sector);

    qreal rot() const;
    void setRot(qreal angle);

    void setStartPosition() override;

    void start() override;
    void resume() override;
    void pause() override;
};

#endif // FIXEDOBJECT_H
