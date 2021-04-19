#ifndef BTACTION_H
#define BTACTION_H

#include "BTNode.h"
#include <memory>

class Blackboard;
class AIComponent;

class BTAction: public BTNode {
public:
    BTAction(QString id) {m_id = id; m_lifetime = 0;};
    virtual ~BTAction() {};

protected:
    std::shared_ptr<Blackboard> m_blackboard;
    AIComponent* m_aiComp;

    double m_lifetime;
};

#endif // BTACTION_H
