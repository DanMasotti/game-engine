#ifndef TICKSYSTEM_H
#define TICKSYSTEM_H

#include "System.h"

class TickSystem: public System
{
public:
    TickSystem();

    virtual void onTick(float seconds) override;
};

#endif // TICKSYSTEM_H
