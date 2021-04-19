#include "PlatformerEnvironment.h"

#include "engine/graphics/Shape.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Material.h"
#include "engine/graphics/ResourceLoader.h"
#include "engine/components/DrawableComponent.h"
#include "engine/components/TransformComponent.h"

using namespace Platformer;

Environment::Environment(GameWorld* world, QString id):
    GameObject(world, id, glm::vec3(1.f, 1.f, 1.f), 0.f, glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f))
{
    Graphics* g = Graphics::getGlobalInstance();
    Material island;

    g->addTexture("island", ":/images/level_island_grassy_indexed.png");
    island.textureName = "island";
    g->addMaterial("island", island);

    std::shared_ptr<Shape> terrain = std::make_shared<Shape>("terrain");
    ResourceLoader::readObj(":/meshes/level_island.obj", terrain);

    g->addShape("terrain", terrain);

    addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(this, "terrain", "island"));

    addSystemFlag(DRAW);
}
