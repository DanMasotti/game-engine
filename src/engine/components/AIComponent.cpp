#include "AIComponent.h"
#include "../GameObject.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "../ai/BTSelector.h"
#include "engine/components/AnimationComponent.h"
#include "../ai/Blackboard.h"
#include "engine/systems/AISystem.h"


AIComponent::AIComponent(GameObject* object):
    Component(object),
    m_nextPositions(std::vector<glm::vec3>()),
    m_move(-1),
    m_tree(std::make_shared<BTSelector>("root")) // root node
{
    m_transformer = m_gameObject->getComponent<TransformComponent>();
}

std::shared_ptr<BTNode> AIComponent::getTree() const {
    return m_tree;
}

void AIComponent::addTree(std::shared_ptr<BTNode> subtree) {
    m_tree->addChild(subtree);
}

void AIComponent::onTick(float seconds) {
    m_tree->update(seconds);

    glm::vec3 currPos = m_transformer->getPosition();
    m_transformer->setIsMovingLaterally(false);

    currPos.y += m_velocityY;
    if (m_transformer->isOnGround()) {
        if (m_velocityY < 0.f) {
            m_velocityY = 0.f;
        }
    }

    m_velocityY -= 0.1f*seconds;

    if (!m_nextPositions.empty() && m_move > -1) {

        std::shared_ptr<AnimationComponent> animator = m_gameObject->getComponent<AnimationComponent>();

        m_transformer->setIsMovingLaterally(true);
        glm::vec3 nextPos = m_nextPositions[m_move];

        const glm::vec3 dir = glm::normalize(nextPos - currPos);
        const float speed = 0.1f;

        bool isForward = glm::dot(dir, glm::vec3(0.f, 0.f, -1.f));

        float headingAngle = glm::acos(glm::dot((isForward)? dir: -dir, glm::vec3(0, 0, -1))/(glm::l2Norm(dir))) + M_PI/2.f;

        m_transformer->rotate(headingAngle, glm::vec3(0.f, 1.f, 0.f));

        currPos += speed*dir;

        if (glm::distance(m_transformer->getPosition(), m_nextPositions[m_move]) < 0.01f) {
            m_move--;
        }
    }

    m_transformer->setTargetPosition(currPos, 1);
}

int AIComponent::getTime() const {
    return m_gameObject->getTime();
}

void AIComponent::switchAnimationSequence(QString sequenceName, bool isLoopable) {
    std::shared_ptr<AnimationComponent> animator = m_gameObject->getComponent<AnimationComponent>();
    animator->switchSequence(sequenceName, isLoopable);
}


std::shared_ptr<Blackboard> AIComponent::getBlackboard() {
    std::shared_ptr<AISystem> sys = m_gameObject->getSystem<AISystem>();
    return sys->getBlackboard();
}


void AIComponent::setMoves(std::vector<glm::vec3> moves) {
    m_nextPositions = moves;
    m_move = moves.size() - 1;
}

void AIComponent::clearMoves() {
    m_transformer->clearTargetPositions();
}

