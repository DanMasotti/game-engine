#include "BTChaseSequence.h"

#include "BTTargetInRange.h"
#include "BTExecutePathAction.h"
#include "BTWaitAction.h"
#include "BTPlanPathAction.h"
#include "BTOreintateAction.h"


BTChaseSequence::BTChaseSequence(AIComponent* comp):
    BTSequence("chasing_sequence")
{
    std::shared_ptr<BTTargetInRangeCondition> isPlayerInSight = std::make_shared<BTTargetInRangeCondition>(comp, "player", 10.f);
    std::shared_ptr<BTWaitAction> wait = std::make_shared<BTWaitAction>(comp, 10);
    std::shared_ptr<BTPlanPathAction> planPath = std::make_shared<BTPlanPathAction>(comp, "player");
    std::shared_ptr<BTOreintateAction> rot = std::make_shared<BTOreintateAction>(comp, "player");
    std::shared_ptr<BTExecutePathAction> doPath = std::make_shared<BTExecutePathAction>(comp, "player");

    addChild(isPlayerInSight);
    addChild(wait);
    addChild(planPath);
    addChild(rot);
    addChild(doPath);
}
