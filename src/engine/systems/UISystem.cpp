#include "UISystem.h"
#include "engine/graphics/Graphics.h"
#include "engine/GameObject.h"
#include "engine/components/UIComponent.h"

UISystem::UISystem()
{

}

void UISystem::onDraw(Graphics* g) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
        it.value()->getComponent<UIComponent>()->draw(g);
    }
}
