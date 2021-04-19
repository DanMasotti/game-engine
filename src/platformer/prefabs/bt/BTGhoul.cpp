#include "BTGhoul.h"

#include "BTChaseSequence.h"
#include "BTCombatSequence.h"
#include "BTPatrolSequence.h"

BTGhoul::BTGhoul(AIComponent* comp):
    BTSelector("ghoul_tree")
{
    // try combat x < 5m
    std::shared_ptr<BTCombatSequence> combatSeq = std::make_shared<BTCombatSequence>(comp);
    // then try chasing x < 10m
    std::shared_ptr<BTChaseSequence> chaseSeq = std::make_shared<BTChaseSequence>(comp);
    // if neither, just patrol
    std::shared_ptr<BTPatrolSequence> patrolSeq = std::make_shared<BTPatrolSequence>(comp);

    addChild(combatSeq);
    addChild(chaseSeq);
    addChild(patrolSeq);
}
