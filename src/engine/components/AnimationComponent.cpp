#include "AnimationComponent.h"

#include "engine/GameObject.h"
#include "DrawableComponent.h"
#include "TransformComponent.h"

AnimationComponent::AnimationComponent(QMap<QString, QVector<QString>> sequence2Frames, GameObject* object):
    Component(object),
    m_sequence2Frames(sequence2Frames),
    m_currentSequence("idle"),
    m_currentFrame(0),
    m_isLoopable(false)
{

}

void AnimationComponent::switchSequence(QString sequenceName, bool isLoopable) {
    if (!m_isLoopable){
        std::shared_ptr<TransformComponent> transformer = m_gameObject->getComponent<TransformComponent>();
        QVector<QString> currentSequence = m_sequence2Frames[m_currentSequence];
        int totalFrames = currentSequence.size();

        if (m_currentFrame < totalFrames - 1) {
            return;
        }
    }

    if (m_sequence2Frames.find(sequenceName) != m_sequence2Frames.end()) {
        m_currentSequence = sequenceName;
        m_isLoopable = isLoopable;
        m_currentFrame = 0;
    } else {
        std::cerr << "couldn't find seq" << std::endl;
        assert(false);
    }
}

void AnimationComponent::animate() {
    std::shared_ptr<TransformComponent> transformer = m_gameObject->getComponent<TransformComponent>();
    QVector<QString> currentSequence = m_sequence2Frames[m_currentSequence];
    int timer = m_gameObject->getTime();
    int totalFrames = currentSequence.size();
    int lastFrame = m_currentFrame;
    m_currentFrame = static_cast<int>((timer/60.f)*totalFrames);

    bool isIdle = !transformer->isMovingLaterally() && transformer->isOnGround();
    isIdle = isIdle || (!m_isLoopable && m_currentFrame < lastFrame);

    // idle is the default sequence
    if (isIdle) {
        if (m_currentSequence != "idle") {
            if (m_sequence2Frames.find("idle") != m_sequence2Frames.end()) {
                switchSequence("idle");
            }
        }
    }

    std::shared_ptr<DrawableComponent> draw = m_gameObject->getComponent<DrawableComponent>();
    QString currentShape = currentSequence[m_currentFrame];

    draw->setShape(currentShape);
}
