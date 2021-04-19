#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "CollisionResponseComponent.h"

CollisionComponent::CollisionComponent(GameObject* object, glm::vec3 position, float radius, float height):
    Component(object),
    m_cylinder(std::make_shared<CollisionCylinder>(position, radius, height)),
    m_state(0)
{

}

// TODO: visitor design pattern for generality
void CollisionComponent::collide(CollisionComponent* other) {
    std::shared_ptr<CollisionCylinder> cylinder = other->getCylinder();

    glm::vec3 mtv = glm::vec3(0.f);

    bool isBaseOverlapping = glm::distance2(cylinder->position, m_cylinder->position) < pow((cylinder->radius + m_cylinder->radius), 2.f);

    if (isBaseOverlapping) {
        float len = glm::length(cylinder->position - m_cylinder->position);
        float coeff = (cylinder->radius + cylinder->radius) - len;
        mtv = coeff*(cylinder->position - m_cylinder->position)/len;
    }

    bool isSideOverlapping = (cylinder->position.y < m_cylinder->position.y + cylinder->height) &&
        (m_cylinder->position.y < cylinder->position.y + cylinder->height);

    if (isSideOverlapping) {
        float aRight = (m_cylinder->position.y + cylinder->height) - m_cylinder->position.y;
        float aLeft = (cylinder->position.y + cylinder->height) - m_cylinder->position.y;

        if (aRight < aLeft) mtv = (glm::length(mtv) < aRight)? mtv: glm::vec3(0.f, aRight, 0.f);

        if (aRight > aLeft) mtv = (glm::length(mtv) < aLeft)? mtv: glm::vec3(0.f, aLeft, 0.f);
    }

    if (isBaseOverlapping && isSideOverlapping) {
        m_state = 1;


        std::shared_ptr<TransformComponent> otherTransformer = other->getGameObject()->getComponent<TransformComponent>();
        otherTransformer->setTargetPosition(otherTransformer->getTargetPosition() + 0.5f*mtv);

        std::shared_ptr<TransformComponent> transformer = m_gameObject->getComponent<TransformComponent>();
        transformer->setTargetPosition(transformer->getTargetPosition() - 0.5f*mtv);

        other->getGameObject()->getComponent<CollisionResponseComponent>()->respond();
        m_gameObject->getComponent<CollisionResponseComponent>()->respond();
        m_state = -1;

    } else {
        m_state = 0;
    }
}


int CollisionComponent::getCollisionState() const {
    return m_state;
}

void CollisionComponent::onTick(float seconds) {
    std::shared_ptr<TransformComponent> transform = m_gameObject->getComponent<TransformComponent>();
    m_cylinder->position = transform->getPosition();
}

std::shared_ptr<CollisionCylinder> CollisionComponent::getCylinder() const {
    return m_cylinder;
}




