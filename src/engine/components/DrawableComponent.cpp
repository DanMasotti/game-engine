#include "DrawableComponent.h"
#include "TransformComponent.h"
#include "../graphics/Graphics.h"
#include "../graphics/Material.h"
#include "../graphics/Shape.h"
#include "../graphics/Camera.h"


DrawableComponent::DrawableComponent(GameObject* object, QString shape, QString mat, bool isText):
    Component(object),
    m_shape(shape),
    m_material(mat),
    m_isText(isText)
{

}

void DrawableComponent::setShape(QString shape) {
    m_shape = shape;
}

void DrawableComponent::onTick(float seconds) {

}

void DrawableComponent::draw(Graphics* g) const {
    g->clearTransform();
    g->getActiveCamera()->setUI(false);

    std::shared_ptr<TransformComponent> transformer = m_gameObject->getComponent<TransformComponent>();

    std::pair<float, glm::vec3> rot = transformer->getRotation();

    // check the rotation, why are collisions not rotated correctly
    g->translate(transformer->getPosition());
    g->rotate(rot.first, glm::vec3(0, 1., 0));
    g->setMaterial(m_material.toStdString());
    g->scale(transformer->getScale());

    if (m_isText) {
        g->drawText(m_shape.toStdString(), 80);
    } else {
        g->drawShape(m_shape.toStdString());
    }

    g->clearTransform();
}
