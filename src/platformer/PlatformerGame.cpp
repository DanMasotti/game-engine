#include "PlatformerGame.h"

#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"
#include "./PlatformerGameScreen.h"
#include "./PlatformerMenuScreen.h"

using namespace Platformer;

PlatformerGame::PlatformerGame():
    Application()
{

    m_currentScreenID = "menu";

    Graphics* g = Graphics::getGlobalInstance();

    std::shared_ptr<Camera> gameCamera = std::make_shared<Camera>();
    gameCamera->setEye(glm::vec3(0.f, 1.f, 0.f));
    std::shared_ptr<GameScreen> gameScreen = std::make_shared<GameScreen>(this, gameCamera);

    std::shared_ptr<Camera> menuCamera = std::make_shared<Camera>();
    menuCamera->setUI(true);
    g->setCamera(menuCamera);
    std::shared_ptr<MenuScreen> menuScreen = std::make_shared<MenuScreen>(this, menuCamera);

    addScreen("game", gameScreen);
    addScreen("menu", menuScreen);
}

void PlatformerGame::reset(int gameState) {

}
