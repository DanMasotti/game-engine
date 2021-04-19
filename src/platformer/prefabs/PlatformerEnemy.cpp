#include "PlatformerEnemy.h"

#include "../../engine/components/PlayerControlComponent.h"
#include "../../engine/components/TransformComponent.h"
#include "../../engine/components/DrawableComponent.h"
#include "../../engine/components/CollisionComponent.h"
#include "../../engine/components/CollisionResponseComponent.h"
#include "../../engine/components/HealthComponent.h"
#include "../../engine/components/EnvironmentCollisionComponent.h"
#include "../../engine/components/AIComponent.h"
#include "../../engine/components/AnimationComponent.h"


#include "engine/systems/AISystem.h"
#include "engine/ai/Blackboard.h"
#include "bt/BTGhoul.h"


using namespace Platformer;

//glm::vec3 scale, float angle, glm::vec3 axis, glm::vec3 position
Enemy::Enemy(GameWorld* world, QString id, glm::vec3 position):
    GameObject(world, id, glm::vec3(1.f, 1.f, 1.f), 0.f, glm::vec3(1.f, 1.f, 1.f), position)
{

    QVector<QString> runningFrameNames = {};
    for (int i = 0; i < 25; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        runningFrameNames.push_back(QString::fromStdString("ghoul_run_" + num));
    }

    QVector<QString> idleFrameNames = {};
    for (int i = 0; i < 6; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        idleFrameNames.push_back(QString::fromStdString("ghoul_idle_" + num));
    }

    QVector<QString> punchRightFrameNames = {};
    for (int i = 0; i < 80; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        punchRightFrameNames.push_back(QString::fromStdString("ghoul_punch_right_" + num));
    }

    QVector<QString> punchLeftFrameNames = {};
    for (int i = 0; i < 80; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        punchLeftFrameNames.push_back(QString::fromStdString("ghoul_punch_left_" + num));
    }

    QVector<QString> hitFrameNames = {};
    for (int i = 0; i < 61; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        punchLeftFrameNames.push_back(QString::fromStdString("ghoul_hit_" + num));
    }

    QVector<QString> screamFrameNames = {};
    for (int i = 0; i < 85; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        screamFrameNames.push_back(QString::fromStdString("ghoul_scream_" + num));
    }

    QMap<QString, QVector<QString>> ghoulFrameName2Sequence = {};
    ghoulFrameName2Sequence["run"] = runningFrameNames;
    ghoulFrameName2Sequence["idle"] = idleFrameNames;
    ghoulFrameName2Sequence["punch_left"] = punchLeftFrameNames;
    ghoulFrameName2Sequence["punch_right"] = punchRightFrameNames;
    ghoulFrameName2Sequence["hit"] = hitFrameNames;
    ghoulFrameName2Sequence["scream"] = screamFrameNames;


    addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(this, "ghoul_run_19", "ghoulMat"));
    addComponent<AnimationComponent>(std::make_shared<AnimationComponent>(ghoulFrameName2Sequence, this));
    addComponent<CollisionComponent>(std::make_shared<CollisionComponent>(this, position, 0.25, 1.));
    addComponent<CollisionResponseComponent>(std::make_shared<CollisionResponseComponent>(this, []() {

    }));

    addComponent<EnvironmentCollisionComponent>(std::make_shared<EnvironmentCollisionComponent>(this, glm::vec3(0.25f, 1.5f, 0.25f)));

    std::shared_ptr<AIComponent> aiComp = std::make_shared<AIComponent>(this);

    std::shared_ptr<BTGhoul> ghoulBT = std::make_shared<BTGhoul>(aiComp.get());

    aiComp->addTree(ghoulBT);

    addComponent<AIComponent>(std::move(aiComp));

    addSystemFlag(DRAW);
    addSystemFlag(COLLISION);
    addSystemFlag(TICK);
    addSystemFlag(AI);
    addSystemFlag(ENVIRONMENT);
    addSystemFlag(ANIMATION);
}
