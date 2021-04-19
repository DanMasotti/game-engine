#ifndef BTRANDOMWALK_H
#define BTRANDOMWALK_H

#include "engine/ai/BTSequence.h"

class AIComponent;

class BTRandomWalk: public BTSequence
{
public:
    BTRandomWalk(AIComponent* comp);
};

#endif // BTRANDOMWALK_H
