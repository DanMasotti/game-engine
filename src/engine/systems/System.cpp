#include "System.h"
#include "../components/Component.h"

System::System():
    m_gameObjects(QMap<QString, std::shared_ptr<GameObject>>()),
    m_gameState(0)
{

}

void System::onKeyPress(QKeyEvent *event) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->onKeyPress(event);
    }
}

void System::onKeyRepeat(QKeyEvent *event) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->onKeyRepeat(event);
    }
}

void System::onKeyRelease(QKeyEvent *event) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->onKeyRelease(event);
    }
}

void System::onMousePress(QMouseEvent *event, int dx, int dy) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->onMousePress(event, dx, dy);
    }
}

void System::onMouseMove(int dx, int dy) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->onMouseMove(dx, dy);
    }
}

void System::onMouseRelease(QMouseEvent* event, int dx, int dy) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->onMouseRelease(event, dx, dy);
    }
}

void System::onMouseWheel(int dx, int dy) {
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it) {
        it.value()->onMouseWheel(dx, dy);
    }
}

void System::addGameObject(QString objectID, std::shared_ptr<GameObject> object) {
    m_gameObjects.insert(objectID, object);
}

void System::removeGameObject(QString objectID) {
    m_gameObjects.remove(objectID);
}

std::shared_ptr<GameObject> System::getGameObject(QString objectID) const {
    return m_gameObjects[objectID];
}

void System::onTick(float seconds) {
    if (m_gameState == 0) {
        for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
            assert(it.value() != nullptr);
            it.value()->tick(seconds);
        }
    }
}

bool System::contains(QString gameObjectId) const {
    return m_gameObjects.contains(gameObjectId);
}
