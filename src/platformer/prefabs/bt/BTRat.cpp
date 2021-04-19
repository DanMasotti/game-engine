#include "BTRat.h"
#include "BTRandomWalk.h"
#include "BTTargetInRange.h"
#include "BTWaitAction.h"

BTRat::BTRat(AIComponent* comp):
    BTSelector("rat_tree")
{
    std::shared_ptr<BTSequence> seq = std::make_shared<BTSequence>("rat_seq");

    std::shared_ptr<BTTargetInRangeCondition> playerNear = std::make_shared<BTTargetInRangeCondition>(comp, "player", 3.f);
    std::shared_ptr<BTRandomWalk> randWalk = std::make_shared<BTRandomWalk>(comp);
    std::shared_ptr<BTWaitAction> wait = std::make_shared<BTWaitAction>(comp, 10);
    seq->addChild(playerNear);
    seq->addChild(randWalk);
    seq->addChild(wait);

    addChild(seq);
}
