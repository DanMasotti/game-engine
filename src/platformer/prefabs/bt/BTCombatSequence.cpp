#include "BTCombatSequence.h"

#include "BTTargetInRange.h"
#include "BTMeleeAction.h"
#include "BTScreamAction.h"
#include "BTOreintateAction.h"

BTCombatSequence::BTCombatSequence(AIComponent* comp):
    BTSequence("combat_sequence")
{
    std::shared_ptr<BTTargetInRangeCondition> isInCombatRange = std::make_shared<BTTargetInRangeCondition>(comp, "player", 1.f);
//    std::shared_ptr<BTScreamAction> scream = std::make_shared<BTScreamAction>(comp);

    std::shared_ptr<BTOreintateAction> rot = std::make_shared<BTOreintateAction>(comp, "player");
    std::shared_ptr<BTMeleeAction> punching = std::make_shared<BTMeleeAction>(comp);

    addChild(isInCombatRange);
//    addChild(scream);
    addChild(rot);
    addChild(punching);
}
