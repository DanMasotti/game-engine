#include "PhysicsComponent.h"

#include "TransformComponent.h"

PhysicsComponent::PhysicsComponent(GameObject* object):
    Component(object)
{

}


void PhysicsComponent::onTick(float seconds) {
    std::shared_ptr<TransformComponent> transformer = m_gameObject->getComponent<TransformComponent>();
    glm::vec3 currPos = transformer->getPosition();

    currPos.y += m_velocityY;
    if (transformer->isOnGround()) {
        if (m_velocityY < 0.f) {
            m_velocityY = 0.f;
        }
    }

    m_velocityY -= 0.25f*seconds;

    transformer->setTargetPosition(currPos, 1);
}
