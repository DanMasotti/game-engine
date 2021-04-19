#include "HealthComponent.h"

#include "engine/GameObject.h"

HealthComponent::HealthComponent(GameObject *object, int healthPoints):
    Component(object),
    m_health(healthPoints)
{

}

void HealthComponent::gainHealth(int healthPoints) {
    m_health += healthPoints;
}

void HealthComponent::drainHealth(int healthPoints) {
    m_health -= healthPoints;
    if (m_health < 0) {
        m_gameObject->setGameState(-1);
    }
}

int HealthComponent::getHealthValue() const {
    return m_health;
}
