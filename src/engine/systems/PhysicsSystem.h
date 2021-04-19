#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "System.h"

class PhysicsSystem: public System
{
public:
    PhysicsSystem();

    virtual void onTick(float seconds) override;
};

#endif // PHYSICSSYSTEM_H
