#include "CollisionResponseComponent.h"

CollisionResponseComponent::CollisionResponseComponent(GameObject* object, std::function<void()> callback):
    Component(object),
    m_callback(callback)
{

}

void CollisionResponseComponent::onTick(float seconds) {

}

void CollisionResponseComponent::respond() {
    m_callback();
}
