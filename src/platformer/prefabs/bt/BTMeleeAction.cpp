#include "BTMeleeAction.h"

#include "engine/util/RNG.h"
#include "engine/components/AIComponent.h"
#include "engine/systems/AISystem.h"

BTMeleeAction::BTMeleeAction(AIComponent* aiComp):
    BTAction("punching")
{
    m_blackboard = aiComp->getBlackboard();
    m_aiComp = aiComp;
}

Status BTMeleeAction::update(float seconds) {

    m_lifetime += seconds;
    if (m_lifetime > 60.) {
        return FAIL;
    }

    const RNG rng = RNG();
    float coinFlip = rng.getRandomNumber();

    if (coinFlip < 1.f) {
        m_aiComp->switchAnimationSequence("punch_right");
    } else {
        m_aiComp->switchAnimationSequence("punch_left"); // TODO: weird glitch happening
    }

    return SUCCESS;
}


void BTMeleeAction::reset() {
    m_lifetime = 0.f;
}
