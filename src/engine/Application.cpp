#include "Application.h"
#include "Screen.h"
#include "engine/graphics/Graphics.h"
#include "engine/graphics/Camera.h"

#include "QApplication"

Application::Application():
    m_screens(QMap<QString, std::shared_ptr<Screen>>()),
    m_currentScreenID(""),
    m_gameState(0)
{

}

void Application::tick(float seconds) {
    if (m_gameState == 0) {
//        std::cout << " ticking " << m_currentScreenID.toStdString() << std::endl;
        m_screens[m_currentScreenID]->tick(seconds);
    } else {
        reset(m_gameState);
    }
};

void Application::draw(Graphics* g) {
    m_screens[m_currentScreenID]->draw(g);
};

// input events
void Application::onMousePress(QMouseEvent *event, int dx, int dy) {
    m_screens[m_currentScreenID]->onMousePress(event, dx, dy);
};

void Application::onMouseMove(int dx, int dy) {
    m_screens[m_currentScreenID]->onMouseMove(dx, dy);
};

void Application::onMouseRelease(QMouseEvent* event, int dx, int dy) {
    m_screens[m_currentScreenID]->onMouseRelease(event, dx, dy);
};

void Application::onMouseWheel(int dx, int dy) {
    m_screens[m_currentScreenID]->onMouseWheel(dx, dy);
}

// TODO: questionable design
void Application::onKeyPress(QKeyEvent *event) {
    if (m_screens.size() > 1) {
        if (event->key() == Qt::Key_Tab) {
            if (m_currentScreenID == "game") {
                switchScreen("menu");
            } else if (m_currentScreenID == "menu") {
                switchScreen("game");
            }
        }
    }
    m_screens[m_currentScreenID]->onKeyPress(event);
};

void Application::onKeyRepeat(QKeyEvent *event) {
    m_screens[m_currentScreenID]->onKeyRepeat(event);
}

void Application::onKeyRelease(QKeyEvent *event) {
    m_screens[m_currentScreenID]->onKeyRelease(event);
}

void Application::resize(int width, int height) {
    m_screens[m_currentScreenID]->resize(width, height);
}

void Application::removeScreen(QString screenID) {
    if (screenID == m_currentScreenID) {
        m_currentScreenID = m_screens.firstKey();
    }
    m_screens.remove(m_currentScreenID);
}

void Application::addScreen(QString screenID, std::shared_ptr<Screen> screen) {
    m_screens.insert(screenID, screen);
}

void Application::switchScreen(QString switchScreenID) {

    if (m_screens.find(switchScreenID) != m_screens.end()) {
        Graphics* g = Graphics::getGlobalInstance();

        glm::vec2 lastSz = g->getActiveCamera()->getScreenSize();

//        std::cout << "curr screen " << m_currentScreenID.toStdString() << std::endl;
        std::shared_ptr<Screen> screen = m_screens[switchScreenID];

        std::shared_ptr<Camera> newCamera = screen->getCamera();

        screen->resize(lastSz.x, lastSz.y);
        newCamera->setScreenSize(lastSz);

//        std::cout << "cam: " << newCamera << std::endl;

        g->setCamera(newCamera);

        m_currentScreenID = switchScreenID;

//        std::cout << "new screen " << m_currentScreenID.toStdString() << std::endl;
    } else {
        std::cerr << "no screen named " << switchScreenID.toStdString() << std::endl;
    }
}

void Application::setGameState(int gameState) {
    m_gameState = gameState;
}
