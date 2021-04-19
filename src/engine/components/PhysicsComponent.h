#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"


class PhysicsComponent: public Component
{
public:
    PhysicsComponent(GameObject* object);

    virtual void onTick(float seconds) override;

private:
    float m_velocityY;

};

#endif // PHYSICSCOMPONENT_H
