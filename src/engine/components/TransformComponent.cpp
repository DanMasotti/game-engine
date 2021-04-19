#include "TransformComponent.h"

#include "engine/graphics/Graphics.h"

TransformComponent::TransformComponent(GameObject* object, glm::vec3 scale, float angle, glm::vec3 axis, glm::vec3 position):
    Component(object),
    m_transform(std::make_shared<Transform>(Transform(scale, angle, axis, position))),
    m_position(position),
    m_targetPosition(std::set<TargetData, TargetDataComp>()),
    m_isOnGround(false),
    m_isMovingLaterally(false)
{

}

void TransformComponent::onTick(float seconds) {
    if (m_position.y < -1.f) {
        m_gameObject->deleteSelf();
    }
}

void TransformComponent::scale(const glm::vec3& scale) {
    m_transform->scale = scale;
}

void TransformComponent::rotate(float angle, const glm::vec3& axis) {
    m_transform->angle = angle;
    m_transform->axis = axis;
}

void TransformComponent::translate(const glm::vec3& translate) {
    m_transform->translate = translate;
    m_position += translate;
}

void TransformComponent::setPosition(const glm::vec3& newPosition) { // easier to do this at places
    glm::vec3 translationNeeded = newPosition - m_position;
    translate(translationNeeded);
}

void TransformComponent::setTargetPosition(const glm::vec3 &targetPos, int priority) {

//    std::cout << "target positions sz: " << m_targetPosition.size() << std::endl;

    if (m_targetPosition.size() < 6) {
        TargetData target;
        target.targetPos = targetPos;
        target.priority = priority;
        m_targetPosition.insert(target);
    }

}

void TransformComponent::clearTargetPositions() {
    m_targetPosition.clear();
    TargetData target;
    target.targetPos = m_position;
    target.priority = 0;
    m_targetPosition.insert(target);
}

void TransformComponent::setIsOnGround(bool isOnGround) {
    m_isOnGround = isOnGround;
}

void TransformComponent::setIsMovingLaterally(bool isMovingLaterally) {
    m_isMovingLaterally = isMovingLaterally;
}

glm::vec3 TransformComponent::getScale() const {
    return m_transform->scale;
}

std::pair<float, glm::vec3> TransformComponent::getRotation() const {
    return std::pair<float, glm::vec3>(m_transform->angle, m_transform->axis);
}

glm::vec3 TransformComponent::getPosition() const {
    return m_position;
}

glm::vec3 TransformComponent::getTargetPosition() {
    if (m_targetPosition.size() == 0) {
        return m_position;
    }

    auto it = m_targetPosition.begin();
    glm::vec3 target = it->targetPos;
    if (m_targetPosition.size() > 1) {
        auto jt = std::next(m_targetPosition.begin());
        TargetData j;
        j.targetPos = jt->targetPos;
        j.priority = jt->priority - 1;
        m_targetPosition.erase(jt);
        m_targetPosition.insert(j);
    }

    m_targetPosition.erase(it);
    return target;
}

glm::vec3 TransformComponent::getTranslation() const {
    return m_transform->translate;
}

bool TransformComponent::isOnGround() const {
    return m_isOnGround;
}

bool TransformComponent::isMovingLaterally() const {
    return m_isMovingLaterally;
}
