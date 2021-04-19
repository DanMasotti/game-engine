#ifndef BTPLANPATHACTION_H
#define BTPLANPATHACTION_H

#include "engine/ai/BTAction.h"

#include "QString"

class BTPlanPathAction: public BTAction
{
public:
    BTPlanPathAction(AIComponent* comp, QString targetName);

    virtual Status update(float seconds) override;
    virtual void reset() override;

private:
    QString m_targetName;
};


#endif // BTPLANPATHACTION_H
