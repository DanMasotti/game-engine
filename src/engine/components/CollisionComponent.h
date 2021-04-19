#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "../util/CommonIncludes.h"
#include "Component.h"


// gets extended by cylinder
class CollisionComponent: public Component
{
public:

    CollisionComponent(GameObject* object, glm::vec3 position, float radius, float height);

    void collide(CollisionComponent* other);

    int getCollisionState() const;

    virtual void onTick(float seconds) override;

    std::shared_ptr<CollisionCylinder> getCylinder() const;

    glm::vec3 getTargetPosition() const;

    void setTargetPosition(const glm::vec3& target);

private:
    std::shared_ptr<CollisionCylinder> m_cylinder;

    glm::vec3 m_targetPosition;

    int m_state;

};

#endif // COLLISIONCOMPONENT_H
