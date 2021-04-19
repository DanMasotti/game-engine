#include "BTTargetInRange.h"
#include "engine/ai/Blackboard.h"
#include "engine/components/AIComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/systems/AISystem.h"


BTTargetInRangeCondition::BTTargetInRangeCondition(AIComponent* comp, QString target, float radius):
    BTCondition("checking_if_"+target+"_is_in_range"),
    m_radius(radius),
    m_target(target)
{
    m_blackboard = comp->getBlackboard();
    m_aiComp = comp;
}


Status BTTargetInRangeCondition::update(float seconds) {
    const glm::vec3 target = m_blackboard->getPositionOf(m_target);
    const glm::vec3 currentPos = m_aiComp->getGameObject()->getComponent<TransformComponent>()->getPosition();
    if (glm::l2Norm(target - currentPos) < m_radius) {
        return SUCCESS;
    } else {
        return FAIL;
    }
}

void BTTargetInRangeCondition::reset() {

}
