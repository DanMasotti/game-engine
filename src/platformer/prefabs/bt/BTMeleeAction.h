#ifndef BTMELEEACTION_H
#define BTMELEEACTION_H

#include "engine/ai/BTAction.h"

class BTMeleeAction: public BTAction
{
public:
    BTMeleeAction(AIComponent* comp);

    virtual Status update(float seconds) override;

    virtual void reset() override;

};

#endif // BTMELEEACTION_H
