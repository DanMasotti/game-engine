#include "GameWorld.h"
#include "GameObject.h"
#include "components/DrawableComponent.h"
#include "components/TransformComponent.h"
#include "Screen.h"

#include "systems/DrawSystem.h"
#include "systems/CollisionSystem.h"
#include "systems/TickSystem.h"
#include "systems/EnvironmentSystem.h"
#include "systems/AISystem.h"
#include "systems/AnimationSystem.h"
#include "systems/UISystem.h"
#include "systems/PhysicsSystem.h"

GameWorld::GameWorld(Screen* screen, QString worldMesh, QString navMesh):
    m_worldMesh(worldMesh),
    m_navMesh(navMesh),
    m_flaggedObjects(QVector<QString>()),
    m_systems(TypeMap<std::shared_ptr<System>>()),
    m_gameState(0),
    m_screen(screen)
{

}

GameWorld::~GameWorld() {

}

void GameWorld::onKeyPress(QKeyEvent *event) {
    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
      it->second->onKeyPress(event);
    }
}

void GameWorld::onKeyRepeat(QKeyEvent *event) {
    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
      it->second->onKeyRepeat(event);
    }
}

void GameWorld::onKeyRelease(QKeyEvent *event) {
    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
      it->second->onKeyRelease(event);
    }
}

void GameWorld::onMousePress(QMouseEvent *event, int dx, int dy) {
    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
      it->second->onMousePress(event, dx, dy);
    }
}

void GameWorld::onMouseMove(int dx, int dy) {
    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
      it->second->onMouseMove(dx, dy);
    }
}

void GameWorld::onMouseRelease(QMouseEvent *event, int dx, int dy) {
    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
      it->second->onMouseRelease(event, dx, dy);
    }
}

void GameWorld::onMouseWheel(int dx, int dy) {
    for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
      it->second->onMouseWheel(dx, dy);
    }
}

void GameWorld::addGameObject(QString gameObjectID, std::shared_ptr<GameObject> gameObject) {
    m_gameObjects.insert(gameObjectID, gameObject);

    std::vector<SYSTEM_TYPE> systems = gameObject->getSystemFlags();
    for (int i = 0, sz = systems.size(); i < sz; ++i) {
        switch(systems[i]){
        case DRAW: {
            if (m_systems.find<DrawSystem>() != m_systems.end()) {
                auto it = getSystem<DrawSystem>();
                it->addGameObject(gameObjectID, gameObject);

            } else {
                addSystem<DrawSystem>(std::make_shared<DrawSystem>());
                auto it = getSystem<DrawSystem>();
                it->addGameObject(gameObjectID, gameObject);

            }
            break;
        };
        case UI: {
            if (m_systems.find<UISystem>() != m_systems.end()) {
                auto it = getSystem<UISystem>();
                it->addGameObject(gameObjectID, gameObject);
            } else {
                addSystem<UISystem>(std::make_shared<UISystem>());
                auto it = getSystem<UISystem>();
                it->addGameObject(gameObjectID, gameObject);
            }
            break;
        };
        case COLLISION: {
            if (m_systems.find<CollisionSystem>() != m_systems.end()) {
                auto it = getSystem<CollisionSystem>();
                it->addGameObject(gameObjectID, gameObject);

            } else {
                addSystem<CollisionSystem>(std::make_shared<CollisionSystem>());
                auto it = getSystem<CollisionSystem>();
                it->addGameObject(gameObjectID, gameObject);

            }
            break;
        };

        case TICK: {
            if (m_systems.find<TickSystem>() != m_systems.end()) {
                auto it = getSystem<TickSystem>();
                it->addGameObject(gameObjectID, gameObject);

            } else {
                addSystem<TickSystem>(std::make_shared<TickSystem>());
                auto it = getSystem<TickSystem>();
                it->addGameObject(gameObjectID, gameObject);

            }
            break;
       }

       case ANIMATION: {
            if (m_systems.find<AnimationSystem>() != m_systems.end()) {
                auto it = getSystem<AnimationSystem>();
                it->addGameObject(gameObjectID, gameObject);
            } else {
                addSystem<AnimationSystem>(std::make_shared<AnimationSystem>());
                auto it = getSystem<AnimationSystem>();
                it->addGameObject(gameObjectID, gameObject);
            }
            break;
        }

       case ENVIRONMENT: {
            if (m_systems.find<EnvironmentSystem>() != m_systems.end()) {
                auto it = getSystem<EnvironmentSystem>();
                it->addGameObject(gameObjectID, gameObject);
            } else {
                addSystem<EnvironmentSystem>(std::make_shared<EnvironmentSystem>(m_worldMesh, m_navMesh));
                auto it = getSystem<EnvironmentSystem>();
                it->addGameObject(gameObjectID, gameObject);
            }
            break;
        }

        case AI: {
            if (m_systems.find<AISystem>() != m_systems.end()) {
                auto it = getSystem<AISystem>();
                it->addGameObject(gameObjectID, gameObject);
            } else {
                addSystem<AISystem>(std::make_shared<AISystem>(m_navMesh, this));
                auto it = getSystem<AISystem>();
                it->addGameObject(gameObjectID, gameObject);
            }
            break;
        }

        case PHYSICS: {
            if (m_systems.find<PhysicsSystem>() != m_systems.end()) {
                auto it = getSystem<PhysicsSystem>();
                it->addGameObject(gameObjectID, gameObject);
            } else {
                addSystem<PhysicsSystem>(std::make_shared<PhysicsSystem>());
                auto it = getSystem<PhysicsSystem>();
                it->addGameObject(gameObjectID, gameObject);
            }
            break;
        }
        }
    }
};

void GameWorld::removeGameObject(QString gameObjectID) {
    m_gameObjects.remove(gameObjectID);
}

std::shared_ptr<GameObject> GameWorld::getGameObject(QString gameObjectID) const {
    return m_gameObjects[gameObjectID];
};

QMap<QString, std::shared_ptr<GameObject>> GameWorld::getGameObjects() const {
    return m_gameObjects;
}

void GameWorld::tick(float seconds) {
    //TODO: breaking
//    while (m_flaggedObjects.size() > 0) {
//        QString id = m_flaggedObjects[m_flaggedObjects.size() - 1];
//        m_flaggedObjects.pop_back();
//        removeGameObject(id);
//    }

    if (m_gameState == 0) {
        for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
            assert(it.value() != nullptr);
            it.value()->tick(seconds);
        }
        for (auto it = m_systems.begin(); it != m_systems.end(); it++) {
            assert(it->second != nullptr);
            it->second->onTick(seconds);
        }
    } else {
        m_screen->setGameState(m_gameState);
    }
};

void GameWorld::flagObject(QString gameObjectID){
    if (!m_flaggedObjects.contains(gameObjectID)) {
        m_flaggedObjects.push_back(gameObjectID);
    }
}

void GameWorld::setGameState(int gameState) {
    m_gameState = gameState;
}

void GameWorld::draw(Graphics* g) {
    getSystem<DrawSystem>()->onDraw(g);
    if (m_systems.find<UISystem>() != m_systems.end()) {
        getSystem<UISystem>()->onDraw(g);
    }
};
