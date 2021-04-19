#include "AnimationSystem.h"
#include "engine/components/AnimationComponent.h"
#include "engine/GameObject.h"


AnimationSystem::AnimationSystem():
    System()
{

}

void AnimationSystem::onTick(float seconds) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->getComponent<AnimationComponent>()->animate();
    }
}
