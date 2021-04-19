#include "PlatformerMenuScreen.h"
#include "engine/GameWorld.h"
#include "engine/GameObject.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "engine/graphics/ResourceLoader.h"
#include "engine/graphics/Shape.h"

#include "engine/components/DrawableComponent.h"

using namespace Platformer;

MenuScreen::MenuScreen(Application* app, std::shared_ptr<Camera> cam):
    Screen(app, cam)
{

    Graphics* g = Graphics::getGlobalInstance();

    std::shared_ptr<Shape> shape = std::make_shared<Shape>("screen");
    ResourceLoader::readObj(":/meshes/screen.obj", shape);
    g->addShape("screen", shape);

    Material screenMat;
    g->addTexture("screenMat", ":/images/menu_screen.png");
    screenMat.textureName = "screenMat";
    g->addMaterial("screenMat", screenMat);

    m_world = std::make_shared<GameWorld>(this);

    glm::vec2 sz = cam->getScreenSize();

    std::shared_ptr<GameObject> screen = std::make_shared<GameObject>(m_world.get(),
                                                                       "screen",
                                                                       glm::vec3(sz.x, sz.y, 0),
                                                                       0.f,
                                                                       glm::vec3(0, 1, 0),
                                                                       glm::vec3(0, 0, 0.85f));

    screen->addComponent<DrawableComponent>(std::make_shared<DrawableComponent>(screen.get(), "screen", "screenMat"));

    screen->addSystemFlag(DRAW);
    m_world->addGameObject("screen", screen);
}
