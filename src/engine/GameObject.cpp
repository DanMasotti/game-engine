#include "GameObject.h"
#include "components/Component.h"
#include "systems/System.h"
#include "systems/CollisionSystem.h"
#include "components/TransformComponent.h"

#include "systems/AISystem.h"
#include "systems/EnvironmentSystem.h"

#include "GameWorld.h"


GameObject::GameObject(GameWorld* world, QString id, glm::vec3 scale, float angle, glm::vec3 axis, glm::vec3 translate):
    m_world(world),
    m_id(id),
    m_gameState(0),
    m_systemFlags({}),
    m_timer(0)
{
    // every Game Object needs a transform component
    addComponent<TransformComponent>(std::make_shared<TransformComponent>(this,
                                                                          scale,
                                                                          angle,
                                                                          axis,
                                                                          translate));

}

void GameObject::addSystemFlag(SYSTEM_TYPE type) {
    m_systemFlags.push_back(type);
}

void GameObject::messageSystem(SYSTEM_TYPE system, const glm::vec3& data) {
//    switch (system) {
//    case COLLISION: {
//        m_world->getSystem<CollisionSystem>()->handleMessage(getID(), data);
//    };

//    }

}

QString GameObject::getID() const {
    return m_id;
}

std::vector<SYSTEM_TYPE> GameObject::getSystemFlags() const {
    return m_systemFlags;
}

GameWorld* GameObject::getWorld() const {
    return m_world;
}


void GameObject::onKeyPress(QKeyEvent *event) {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->onKeyPress(event);
    }
}

void GameObject::onKeyRepeat(QKeyEvent *event) {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->onKeyRepeat(event);
    }
}

void GameObject::onKeyRelease(QKeyEvent *event) {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->onKeyRelease(event);
    }
}

void GameObject::onMousePress(QMouseEvent *event, int dx, int dy) {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->onMousePress(event, dx, dy);
    }
}

void GameObject::onMouseMove(int dx, int dy) {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->onMouseMove(dx, dy);
    }
}

void GameObject::onMouseRelease(QMouseEvent* event, int dx, int dy) {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->onMouseRelease(event, dx, dy);
    }
}

void GameObject::onMouseWheel(int dx, int dy) {
    for (auto it = m_components.begin(); it != m_components.end(); ++it) {
        it->second->onMouseWheel(dx, dy);
    }
}

void GameObject::setGameState(int gameState) {
    m_gameState = gameState;
}

void GameObject::tick(float seconds) {
    if (m_gameState == 0) {
        for (auto it = m_components.begin(); it != m_components.end(); it++) {
          it->second->onTick(seconds);
        }
    } else {
        m_world->setGameState(m_gameState);
    }
}

void GameObject::deleteSelf() {
    m_world->flagObject(m_id);
}


int GameObject::getTime() const {
    return m_timer;
}

void GameObject::incrementTimer() {
    ++m_timer;

    if (m_timer == 60) {
        m_timer = 0;
    }
}



