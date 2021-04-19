#ifndef BTGHOUL_H
#define BTGHOUL_H

#include "engine/ai/BTSelector.h"
#include "engine/ai/BTSequence.h"

class AIComponent;

class BTGhoul: public BTSelector
{
public:
    BTGhoul(AIComponent* comp);
};

#endif // BTGHOUL_H
