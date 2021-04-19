#include "BTPlanPathAction.h"

#include "engine/ai/Blackboard.h"
#include "engine/components/AIComponent.h"
#include "engine/components/TransformComponent.h"
#include "engine/systems/AISystem.h"

BTPlanPathAction::BTPlanPathAction(AIComponent* comp, QString targetName):
    BTAction("planning_path_to_" + targetName),
    m_targetName(targetName)
{
    m_blackboard = comp->getBlackboard();
    m_aiComp = comp;
}

Status BTPlanPathAction::update(float seconds) {
    m_lifetime += seconds;
    if (m_lifetime > 30.) {
        return FAIL;
    }

    const glm::vec3 target = m_blackboard->getPositionOf(m_targetName);
    const auto targetNode = m_blackboard->point2Node(target);
    const glm::vec3 currentPos = m_aiComp->getGameObject()->getComponent<TransformComponent>()->getPosition();
    const auto currentNode = m_blackboard->point2Node(currentPos);
    const std::vector<glm::vec3> positions = m_blackboard->getPath(targetNode, currentNode, target);
    m_aiComp->setMoves(positions);

    return SUCCESS;
}

void BTPlanPathAction::reset() {
    m_lifetime = 0.;
}
