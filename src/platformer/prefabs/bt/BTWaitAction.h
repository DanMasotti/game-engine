#ifndef BTWAITACTION_H
#define BTWAITACTION_H

#include "engine/ai/BTAction.h"

class BTWaitAction: public BTAction
{
public:
    BTWaitAction(AIComponent* comp, int interval = 60);

    virtual Status update(float seconds) override;
    virtual void reset() override;

private:
    int m_interval;
    int m_timer;

};

#endif // BTWAITACTION_H
