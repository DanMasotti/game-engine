#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "Component.h"
#include "set"

struct TargetData {
    glm::vec3 targetPos;
    int priority;
};

struct TargetDataComp {
    bool operator() (const TargetData& lhs, const TargetData& rhs) const {
        return lhs.priority < rhs.priority;
    }
};

class Graphics;

class TransformComponent: public Component
{
public:
    TransformComponent(GameObject* gameobject, glm::vec3 scale, float angle, glm::vec3 axis, glm::vec3 translate);

    virtual void onTick(float seconds) override;

    void scale(const glm::vec3& scale);
    void rotate(float angle, const glm::vec3& axis);
    void translate(const glm::vec3& translate);

    void setPosition(const glm::vec3& newPosition);
    void setTargetPosition(const glm::vec3& target, int priority = 0);

    void clearTargetPositions();

    void setIsOnGround(bool isOnGround);
    void setIsMovingLaterally(bool isMovingLaterally);

    glm::vec3 getScale() const;
    std::pair<float, glm::vec3> getRotation() const;
    glm::vec3 getPosition() const;
    glm::vec3 getTargetPosition();
    glm::vec3 getTranslation() const;

    bool isOnGround() const;
    bool isMovingLaterally() const;

private:
    std::shared_ptr<Transform> m_transform;
    glm::vec3 m_position;
    std::set<TargetData, TargetDataComp> m_targetPosition;
    bool m_isOnGround;
    bool m_isMovingLaterally;
};

#endif // TRANSFORMCOMPONENT_H
