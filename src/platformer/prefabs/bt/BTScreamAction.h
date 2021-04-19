#ifndef BTSCREAMACTION_H
#define BTSCREAMACTION_H

#include "engine/ai/BTAction.h"

class BTScreamAction: public BTAction
{
public:
    BTScreamAction(AIComponent* comp);

    virtual Status update(float seconds) override;

    virtual void reset() override;
};

#endif // BTSCREAMACTION_H
