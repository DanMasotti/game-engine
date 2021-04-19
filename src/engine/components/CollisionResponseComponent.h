#ifndef COLLISIONRESPONSECOMPONENT_H
#define COLLISIONRESPONSECOMPONENT_H

#include "Component.h"
#include <functional>

class CollisionResponseComponent: public Component
{
public:
    CollisionResponseComponent(GameObject* object, std::function<void()>);

    virtual void onTick(float seconds) override;

    void respond();

private:
    std::function<void()> m_callback;
};

#endif // COLLISIONRESPONSECOMPONENT_H
