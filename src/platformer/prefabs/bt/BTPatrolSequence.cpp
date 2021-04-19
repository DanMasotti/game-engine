#include "BTPatrolSequence.h"
#include "engine/components/AIComponent.h"

#include "BTPlanPathAction.h"
#include "BTExecutePathAction.h"
#include "BTWaitAction.h"
#include "BTOreintateAction.h"


BTPatrolSequence::BTPatrolSequence(AIComponent* comp):
    BTSequence("patrol_sequence")
{
    QString me = comp->getGameObject()->getID();

    for (int i = 0; i < 2; ++i) {
        QString postName = me + QString::fromStdString("_post_" + std::to_string(i));
        // wait
        std::shared_ptr<BTWaitAction> wait = std::make_shared<BTWaitAction>(comp, 10);
        // then set the moves to get to target
        std::shared_ptr<BTPlanPathAction> planPath = std::make_shared<BTPlanPathAction>(comp, postName);
        // then check if you've reached the target, and until then set the animation to running
        std::shared_ptr<BTOreintateAction> rot = std::make_shared<BTOreintateAction>(comp, postName);
        std::shared_ptr<BTExecutePathAction> doPath = std::make_shared<BTExecutePathAction>(comp, postName);

        addChild(planPath);
        addChild(rot);
        addChild(doPath);
        addChild(wait);
    }
}
