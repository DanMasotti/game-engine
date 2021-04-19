#include "DrawSystem.h"
#include "../graphics/Graphics.h"
#include "../GameObject.h"
#include "../components/DrawableComponent.h"
#include "../components/TransformComponent.h"

DrawSystem::DrawSystem():
    System()
{

}

void DrawSystem::onDraw(Graphics* g) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
        it.value()->getComponent<DrawableComponent>()->draw(g);
    }
}
