#include "BTExecutePathAction.h"
#include "engine/ai/Blackboard.h"
#include "engine/components/AIComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/GameWorld.h"
#include "engine/systems/AISystem.h"

BTExecutePathAction::BTExecutePathAction(AIComponent* comp, QString target):
    BTAction("path_to_" + target),
    m_target(target)
{
    m_blackboard = comp->getBlackboard();
    m_aiComp = comp;
}

// TODO: this should be a sequence that queries the environment for mud, etc.
Status BTExecutePathAction::update(float seconds) {
    m_aiComp->switchAnimationSequence("run");
    Status state = RUNNING;
    m_lifetime += seconds;
    if ( m_lifetime > 30.) {
        state = FAIL;
    }

    QString me = m_aiComp->getGameObject()->getID();
    float dist = glm::l2Norm(m_blackboard->getPositionOf(me) - m_blackboard->getPositionOf(m_target));
    if (dist < 1.f) {
        m_aiComp->switchAnimationSequence("idle");
        state = SUCCESS;
    }

    return state;
}

void BTExecutePathAction::reset() {
    m_lifetime = 0.;
}

