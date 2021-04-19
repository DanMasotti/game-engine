#include "BTRandomWalk.h"

#include "BTPlanPathAction.h"
#include "BTExecutePathAction.h"


BTRandomWalk::BTRandomWalk(AIComponent* comp):
    BTSequence("random_walk")
{

    std::shared_ptr<BTPlanPathAction> planPath = std::make_shared<BTPlanPathAction>(comp, "random");
    std::shared_ptr<BTExecutePathAction> doPath = std::make_shared<BTExecutePathAction>(comp, "random");

    addChild(planPath);
    addChild(doPath);
}
