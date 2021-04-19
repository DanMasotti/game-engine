#ifndef BTCONDITION_H
#define BTCONDITION_H

#include "BTNode.h"
#include <memory>

class Blackboard;
class AIComponent;

class BTCondition: public BTNode {
public:
    BTCondition(QString id) {m_id = id;};
    virtual ~BTCondition() {};

protected:
    std::shared_ptr<Blackboard> m_blackboard;
    AIComponent* m_aiComp;
};


#endif // BTCONDITION_H
