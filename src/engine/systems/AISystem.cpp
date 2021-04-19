#include "AISystem.h"

#include "../components/AIComponent.h"
#include "../components/TransformComponent.h"
#include "../GameWorld.h"
#include "set"
#include "../ai/Blackboard.h"


AISystem::AISystem(QString filepath, GameWorld* world):
    System(),
    m_world(world),
    m_blackboard(std::make_shared<Blackboard>(filepath, world))
{

}

std::shared_ptr<Blackboard> AISystem::getBlackboard() const {
    return m_blackboard;
}

// run AI before collisions, env collisions last
void AISystem::onTick(float seconds) {
    m_blackboard->update();

    // Tick components
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        std::shared_ptr<AIComponent> aiComp = it.value()->getComponent<AIComponent>();
        aiComp->onTick(seconds);
    }
}
