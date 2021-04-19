#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H


#include "System.h"

class AnimationSystem: public System
{
public:
    AnimationSystem();

    virtual void onTick(float seconds) override;


};

#endif // ANIMATIONSYSTEM_H
