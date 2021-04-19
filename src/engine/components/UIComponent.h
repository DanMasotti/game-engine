#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "Component.h"

class UIComponent: public Component
{
public:
    UIComponent(GameObject* object);

    glm::vec3 convertToScreenSpace(glm::vec3 position, glm::vec2 screemSz) const;

    void draw(Graphics *g) const;

};

#endif // UICOMPONENT_H
