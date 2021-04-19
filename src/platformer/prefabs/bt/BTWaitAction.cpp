#include "BTWaitAction.h"

#include "engine/components/AIComponent.h"
#include "engine/systems/AISystem.h"

BTWaitAction::BTWaitAction(AIComponent* comp, int interval):
    BTAction("wating_for_" + QString::fromStdString(std::to_string(interval))),
    m_interval(interval)
{
    m_blackboard = comp->getBlackboard();
    m_aiComp = comp;
}

// returns success every ticks
Status BTWaitAction::update(float seconds) {
    m_lifetime += seconds;
    if (m_lifetime > 30.) {
        return FAIL;
    }

    if (m_timer == m_interval) {
        m_timer = -1;
    }

    m_timer++;
    if (m_timer == 0) {
        return SUCCESS;
    }

    m_aiComp->switchAnimationSequence("idle");
    return RUNNING;
}

void BTWaitAction::reset() {
    m_lifetime = 0.f;
}
