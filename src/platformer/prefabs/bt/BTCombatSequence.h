#ifndef BTCOMBATSEQUENCE_H
#define BTCOMBATSEQUENCE_H

#include "engine/ai/BTSequence.h"

class AIComponent;


class BTCombatSequence: public BTSequence
{
public:
    BTCombatSequence(AIComponent* comp);
};

#endif // BTCOMBATSEQUENCE_H
