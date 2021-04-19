#include "PhysicsSystem.h"

#include "engine/GameObject.h"
#include "engine/components/PhysicsComponent.h"

PhysicsSystem::PhysicsSystem()
{

}


void PhysicsSystem::onTick(float seconds) {

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->getComponent<PhysicsComponent>()->onTick(seconds);
    }


}
