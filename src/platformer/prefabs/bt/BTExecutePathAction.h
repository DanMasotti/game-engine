#ifndef BTEXECUTEPATHACTION_H
#define BTEXECUTEPATHACTION_H

#include "engine/ai/BTAction.h"

#include "QString"

class BTExecutePathAction: public BTAction
{
public:
    BTExecutePathAction(AIComponent* comp, QString target);

    virtual Status update(float seconds) override;
    virtual void reset() override;

private:
    QString m_target;

};

#endif // BTEXECUTEPATHACTION_H
