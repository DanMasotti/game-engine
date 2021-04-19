#include "Rat.h"

#include "../../engine/components/PlayerControlComponent.h"
#include "../../engine/components/TransformComponent.h"
#include "../../engine/components/DrawableComponent.h"
#include "../../engine/components/CollisionComponent.h"
#include "../../engine/components/CollisionResponseComponent.h"
#include "../../engine/components/HealthComponent.h"
#include "../../engine/components/EnvironmentCollisionComponent.h"
#include "../../engine/components/AIComponent.h"
#include "../../engine/components/AnimationComponent.h"

#include "bt/BTRat.h"


using namespace Platformer;

Rat::Rat(GameWorld* world, QString id, glm::vec3 position):
    GameObject(world, id, glm::vec3(1.f, 1.f, 1.f), 0.f, glm::vec3(1.f, 1.f, 1.f), position)
{
    QVector<QString> idleFrameNames = {"rat_idle_1"};

    QVector<QString> runningFrameNames = {};
    for (int i = 0; i < 10; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        runningFrameNames.push_back(QString::fromStdString("rat_run_" + num));
    }

    QMap<QString, QVector<QString>> ratFrameName2Sequence = {};
    ratFrameName2Sequence["run"] = runningFrameNames;
    ratFrameName2Sequence["idle"] = idleFrameNames;

    addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(this, "rat_idle_1", "ratMat"));
    addComponent<AnimationComponent>(std::make_shared<AnimationComponent>(ratFrameName2Sequence, this));

    addComponent<EnvironmentCollisionComponent>(std::make_shared<EnvironmentCollisionComponent>(this, glm::vec3(0.2f, 0.1f, 0.25f)));

    std::shared_ptr<AIComponent> aiComp = std::make_shared<AIComponent>(this);

    std::shared_ptr<BTRat> ratBT = std::make_shared<BTRat>(aiComp.get());

    aiComp->addTree(ratBT);

    addComponent<AIComponent>(std::move(aiComp));

    addSystemFlag(DRAW);
    addSystemFlag(TICK);
    addSystemFlag(AI);
    addSystemFlag(ENVIRONMENT);
    addSystemFlag(ANIMATION);
}
