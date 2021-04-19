#ifndef BTCHASESEQUENCE_H
#define BTCHASESEQUENCE_H

#include "engine/ai/BTSequence.h"

class AIComponent;

class BTChaseSequence: public BTSequence
{
public:
    BTChaseSequence(AIComponent* comp);
};

#endif // BTCHASESEQUENCE_H
