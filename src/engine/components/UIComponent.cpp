#include "UIComponent.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/components/TransformComponent.h"

UIComponent::UIComponent(GameObject* object):
    Component(object)
{

}

glm::vec3 UIComponent::convertToScreenSpace(glm::vec3 pos, glm::vec2 screenSz) const {
    // get these from your camera
    Graphics* g = Graphics::getGlobalInstance();
    glm::mat4 projection = g->getActiveCamera()->getProjection();
    glm::mat4 view = g->getActiveCamera()->getView();

    // this is necessary for the matrix multiplication
    glm::vec4 fourVec = glm::vec4(pos.x, pos.y, pos.z, 1.f);

    // project the position into clip space
    fourVec = projection * view * fourVec;

    // x and y range from -1 to 1
    glm::vec3 clipSpace = glm::vec3(fourVec.x/fourVec.w, fourVec.y/fourVec.w, fourVec.z);
    // convert x and y to pixel coordinates, leave z alone
    return glm::vec3((clipSpace.x + 1) * .5f * screenSz.x, (1 - clipSpace.y) * .5f * screenSz.y, clipSpace.z);
}

void UIComponent::draw(Graphics *g) const {
    g->clearTransform();

//    std::shared_ptr<TransformComponent> trans = m_gameObject->getComponent<TransformComponent>();

//    glm::vec3 pos = trans->getPosition();
//    pos = convertToScreenSpace(pos, g->getActiveCamera()->getScreenSize());

//    if (pos.z < 0) return;

//    std::cout << "pos: " << glm::to_string(pos) << std::endl;

//    g->translate(glm::vec3(pos.x, 0, pos.y));

//    g->scale(glm::vec3(0.1, 0.1, 0.1));

//    g->drawShape("cube");

    g->clearTransform();
}
