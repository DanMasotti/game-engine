#include "Screen.h"
#include "GameWorld.h"
#include "Application.h"
#include "graphics/Graphics.h"
#include "graphics/Camera.h"

Screen::Screen(Application* app, std::shared_ptr<Camera> cam):
    m_app(app),
    m_camera(cam),
    m_gameState(0)
{

}

void Screen::onMousePress(QMouseEvent *event, int dx, int dy) {
    m_world->onMousePress(event, dx, dy);
}

void Screen::onMouseMove(int dx, int dy) {
    m_world->onMouseMove(dx, dy);
}

void Screen::onMouseRelease(QMouseEvent *event, int dx, int dy) {
    m_world->onMouseRelease(event, dx, dy);
}

void Screen::onMouseWheel(int dx, int dy) {
    m_world->onMouseWheel(dx, dy);
}

void Screen::onKeyPress(QKeyEvent *event) {
    m_world->onKeyPress(event);
}

void Screen::onKeyRepeat(QKeyEvent *event) {
    m_world->onKeyRepeat(event);
}

void Screen::onKeyRelease(QKeyEvent *event) {
    m_world->onKeyRelease(event);
}

void Screen::resize(const int width, const int height) {
    Graphics::getGlobalInstance()->getActiveCamera()->setScreenSize(glm::vec2(width, height));
}

std::shared_ptr<Camera> Screen::getCamera() const {
    return m_camera;
};

void Screen::tick(const float seconds) {
    if (m_gameState == 0) {
        assert(m_world.get() != nullptr);
        m_world->tick(seconds);
    } else {
        m_app->setGameState(m_gameState);
    }
}

void Screen::draw(Graphics *g) {
    m_world->draw(g); // forwards to draw system
}

void Screen::setGameState(int gameState) {
    m_gameState = gameState;
}
