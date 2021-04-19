#include "BTScreamAction.h"

#include "engine/components/AIComponent.h"


#include "engine/util/RNG.h"

BTScreamAction::BTScreamAction(AIComponent* comp):
    BTAction("scream")
{
    m_blackboard = comp->getBlackboard();
    m_aiComp = comp;
}

Status BTScreamAction::update(float seconds) {

    m_lifetime += seconds;
    if (m_lifetime > 30.) {
        return FAIL;
    }

    const RNG rng = RNG();
    float coinFlip = rng.getRandomNumber();

    if (coinFlip < 0.1f) {
        m_aiComp->switchAnimationSequence("scream", false);
        return RUNNING;
    }


    return SUCCESS;
}


void BTScreamAction::reset() {
    m_lifetime = 0.;
}
