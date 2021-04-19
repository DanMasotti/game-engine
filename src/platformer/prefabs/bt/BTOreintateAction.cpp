#include "BTOreintateAction.h"

#include "engine/components/AIComponent.h"
#include "engine/ai/Blackboard.h"
#include "engine/components/TransformComponent.h"
#include "math.h"

BTOreintateAction::BTOreintateAction(AIComponent* comp, QString target):
    BTAction("orientate_towards " + target)
{
    m_aiComp = comp;
    m_target = target;
    m_blackboard = m_aiComp->getBlackboard();
}

Status BTOreintateAction::update(float seconds) {
    m_lifetime += seconds;
    if (m_lifetime > 30.) {
        return FAIL;
    }


    /*
     * ghoul look at player vec = pos - ghoul pos
     * theta = atan2(vec.z,vec.x)
     */

    auto transformer = m_aiComp->getGameObject()->getComponent<TransformComponent>();

    const glm::vec3 target = m_blackboard->getPositionOf(m_target);
    const glm::vec3 me = transformer->getPosition();

    const glm::vec3 look = target - me;

    const float theta = atan2(look.z, look.x);
    transformer->rotate(theta, glm::vec3(0, 1, 0));

    return SUCCESS;
}

void BTOreintateAction::reset() {
    m_lifetime = 0.f;
}
