#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"

class GameObject;

class HealthComponent: public Component
{
public:
    HealthComponent(GameObject* object, int healthPoints);

    void gainHealth(int healthPoints);
    void drainHealth(int healthPoints);
    int getHealthValue() const;

private:
    int m_health;

};

#endif // HEALTHCOMPONENT_H
