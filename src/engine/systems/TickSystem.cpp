#include "TickSystem.h"
#include "engine/GameObject.h"

TickSystem::TickSystem():
    System()
{

}

void TickSystem::onTick(float seconds) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
      it.value()->tick(seconds);
      it.value()->incrementTimer();
    }
}
