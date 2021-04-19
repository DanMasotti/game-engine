#ifndef BTRAT_H
#define BTRAT_H


#include "engine/ai/BTSelector.h"
#include "engine/ai/BTSequence.h"

class AIComponent;

class BTRat: public BTSelector
{
public:
    BTRat(AIComponent* comp);
};

#endif // BTRAT_H
