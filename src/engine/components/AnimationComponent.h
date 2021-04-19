#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Component.h"

#include "QMap"
#include "QVector"

class GameObject;

class AnimationComponent: public Component
{
public:
    AnimationComponent(QMap<QString, QVector<QString>> sequence2Frames, GameObject* object);

    void switchSequence(QString sequenceName, bool isLoopable = true);

    void animate();

private:

    QMap<QString, QVector<QString>> m_sequence2Frames;
    QString m_currentSequence;
    int m_currentFrame;
    bool m_isLoopable;
};

#endif // ANIMATIONCOMPONENT_H
