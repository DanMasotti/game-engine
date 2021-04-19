#include "PlatformerPlayer.h"

#include "../../engine/graphics/Graphics.h"
#include "../../engine/graphics/Camera.h"
#include "engine/graphics/ResourceLoader.h"
#include "engine/graphics/Shape.h"

#include "../../engine/components/PlayerControlComponent.h"
#include "../../engine/components/TransformComponent.h"
#include "../../engine/components/DrawableComponent.h"
#include "../../engine/components/CollisionComponent.h"
#include "../../engine/components/CollisionResponseComponent.h"
#include "../../engine/components/HealthComponent.h"
#include "../../engine/components/EnvironmentCollisionComponent.h"
#include "../../engine/components/UIComponent.h"

#include "../../engine/GameWorld.h"

#include "engine/components/AnimationComponent.h"

#include "QApplication"

/*
 * debug mode: get rid of collider, change controls for flying
 */

/*
 * punch the ghoul but the ghoul cant punch you from a certain distance
 * check if you face the ghoul or the ghoul is facing you, query the
 * collision component? collision system is different from this, combat system
 * uses the collision cylinder component
 */

/*
 * title screen
 */

extern bool IS_DEBUG_MODE;


using namespace Platformer;

Player::Player(GameWorld* world):
    GameObject(world, "player", glm::vec3(1.f, 1.f, 1.f), 0.f, glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 0.7f, -0.f))
{

    QMap<int, bool> keysPressed = QMap<int, bool>();

    keysPressed[Qt::Key_W] = false;
    keysPressed[Qt::Key_S] = false;
    keysPressed[Qt::Key_A] = false;
    keysPressed[Qt::Key_D] = false;
    keysPressed[Qt::Key_Space] = false;
    keysPressed[Qt::Key_F5] = false;
    keysPressed[Qt::Key_Up] = false;
    keysPressed[Qt::Key_Down] = false;
    keysPressed[Qt::Key_Left] = false;
    keysPressed[Qt::Key_Right] = false;

    QMap<int, bool> mouseButtonsPressed = QMap<int, bool>();
    mouseButtonsPressed[Qt::LeftButton] = false;
    mouseButtonsPressed[Qt::RightButton] = false;
    mouseButtonsPressed[Qt::MiddleButton] = false;

    const glm::vec2 mousePosition = glm::vec2(0.f, 0.f);

    const glm::vec3 dimensions = glm::vec3(0.25f, 1.1f, 0.25f);

    QMap<QString, QVector<QString>> playerFrameName2Sequence = {};

    QVector<QString> runningFrameNames = {};
    for (int i = 0; i < 20; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        runningFrameNames.push_back(QString::fromStdString("run_" + num));
    }

    QVector<QString> strafeRightFrameNames = {};
    for (int i = 0; i < 21; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        strafeRightFrameNames.push_back(QString::fromStdString("strafe_right_" + num));
    }

    QVector<QString> strafeLeftFrameNames = {};
    for (int i = 0; i < 21; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        strafeLeftFrameNames.push_back(QString::fromStdString("strafe_left_" + num));
    }

    QVector<QString> idleFrameNames = {};
    for (int i = 0; i < 60; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        idleFrameNames.push_back(QString::fromStdString("idle_" + num));
    }

    QVector<QString> jumpFrameNames = {};
    for (int i = 16; i < 46; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        jumpFrameNames.push_back(QString::fromStdString("jump_" + num));
    }

    QVector<QString> punchRightFrameNames = {};
    for (int i = 0; i < 31; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        punchRightFrameNames.push_back(QString::fromStdString("punch_right_" + num));
    }

    QVector<QString> punchLeftFrameNames = {};
    for (int i = 0; i < 31; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        punchLeftFrameNames.push_back(QString::fromStdString("punch_left_" + num));
    }

    QVector<QString> kickFrameNames = {};
    for (int i = 0; i < 46; ++i) {
        std::string num = std::to_string(i + 1); // 10 | 3
        kickFrameNames.push_back(QString::fromStdString("kick_" + num));
    }


    QVector<QString> hitFrameNames = {};
    for (int i = 0; i < 43; ++i) {
        std::string num = std::to_string(i + 1);
        hitFrameNames.push_back(QString::fromStdString("hit_" + num));
    }

    playerFrameName2Sequence["run"] = runningFrameNames;
    playerFrameName2Sequence["strafe_right"] = strafeRightFrameNames;
    playerFrameName2Sequence["strafe_left"] = strafeLeftFrameNames;
    playerFrameName2Sequence["idle"] = idleFrameNames;
    playerFrameName2Sequence["jump"] = jumpFrameNames;
    playerFrameName2Sequence["punch_left"] = punchLeftFrameNames;
    playerFrameName2Sequence["punch_right"] = punchRightFrameNames;
    playerFrameName2Sequence["kick"] = kickFrameNames;
    playerFrameName2Sequence["hit"] = hitFrameNames;


    if (IS_DEBUG_MODE) { // spectator mode basically
        addComponent<PlayerControlComponent>(std::make_shared<PlayerControlComponent>(this, keysPressed, mouseButtonsPressed, mousePosition));
        addSystemFlag(TICK);
    } else {

        addComponent<AnimationComponent>(std::make_shared<AnimationComponent>(playerFrameName2Sequence, this));
        addComponent<PlayerControlComponent>(std::make_shared<PlayerControlComponent>(this, keysPressed, mouseButtonsPressed, mousePosition));
        addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(this, "idle_32", "player"));
        addComponent<CollisionComponent>(std::make_shared<CollisionComponent>(this, glm::vec3(0.f, 0.5f, 0.f), 0.25, 1.));

        addComponent<CollisionResponseComponent>(std::make_shared<CollisionResponseComponent>(this, [this]() {
             this->getComponent<AnimationComponent>()->switchSequence("hit");
        }));

        addComponent<EnvironmentCollisionComponent>(std::make_shared<EnvironmentCollisionComponent>(this, dimensions));

        addComponent<HealthComponent>(std::make_shared<HealthComponent>(this, 100));
        addComponent<UIComponent>(std::make_shared<UIComponent>(this));

        addSystemFlag(UI);
        addSystemFlag(DRAW);
        addSystemFlag(COLLISION);
        addSystemFlag(TICK);
        addSystemFlag(ANIMATION);
        addSystemFlag(ENVIRONMENT);
    }
}
