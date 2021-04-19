#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "Component.h"

class BTNode;
class BTSelector;
class GameObject;
class TransformComponent;
class Blackboard;


class AIComponent: public Component
{
public:
    AIComponent(GameObject* object);

    virtual void onTick(float seconds) override;

    std::shared_ptr<BTNode> getTree() const;

    int getTime() const;

    void addTree(std::shared_ptr<BTNode> subtree);

    void setMoves(std::vector<glm::vec3> moves);
    void clearMoves();

    void switchAnimationSequence(QString sequenceName, bool isLoopable = true);

    std::shared_ptr<Blackboard> getBlackboard();



private:
    float m_velocityY;

    std::vector<glm::vec3> m_nextPositions;
    int m_move;

    std::shared_ptr<BTSelector> m_tree;

    std::shared_ptr<TransformComponent> m_transformer;
};

#endif // AICOMPONENT_H
