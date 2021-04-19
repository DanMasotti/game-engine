#include "Barrel.h"

#include "engine/components/DrawableComponent.h"
#include "engine/components/CollisionComponent.h"
#include "engine/components/CollisionResponseComponent.h"
#include "engine/components/EnvironmentCollisionComponent.h"
#include "engine/components/PhysicsComponent.h"


using namespace Platformer;

Barrel::Barrel(GameWorld* world, QString id, glm::vec3 position):
    GameObject(world, id, glm::vec3(0.5f, 0.5f, 0.5f), 0.f, glm::vec3(1.f, 1.f, 1.f), position)
{
    addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(this, "cylinder", "rust"));
    addComponent<CollisionComponent>(std::make_shared<CollisionComponent>(this, glm::vec3(0.f, 0.5f, 0.f), 0.5, 1.));

    addComponent<CollisionResponseComponent>(std::make_shared<CollisionResponseComponent>(this, []() {

    }));

    addComponent<EnvironmentCollisionComponent>(std::make_shared<EnvironmentCollisionComponent>(this, glm::vec3(0.5f, 1.1f, 0.5f)));

    addComponent<PhysicsComponent>(std::make_shared<PhysicsComponent>(this));

    addSystemFlag(DRAW);
    addSystemFlag(TICK);
    addSystemFlag(COLLISION);
    addSystemFlag(ENVIRONMENT);
    addSystemFlag(PHYSICS);
}
